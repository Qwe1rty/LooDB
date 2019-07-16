#include "../api/PageCodec.h"
#include "../api/PageType.h"
#include "../../page/api/Cell.h"
#include "../../page/api/CellBP.h"
#include "../../page/api/BTreeHeaderPage.h"
#include "../../page/api/BPTreeInternalPage.h"
#include "../../page/api/BPTreeHeaderPage.h"
#include "../../page/api/BPTreeLeafPage.h"
#include "../../page/api/BTreeNodePage.h"
#include "../../page/api/EntryPage.h"
#include "../../../../util/api/ByteReader.h"
#include "../../../../util/api/ByteWriter.h"

#include <functional>
#include <map>


namespace {

  using Object = PageCodec::Object;
  using Serial = PageCodec::Serial;

  using EncodeWriter = std::function<void(ByteWriter<Serial>&, const Object&)>;
  using DecodeReader = std::function<Object(ByteReader<const Serial>&)>;

  /*
   * Implementation of the PageCodec class is similar to a more traditional
   * visitor pattern, but makes use of the PageType enum to differentiate the
   * dynamic page type.
   *
   * static_cast<...> is guaranteed due to the association between the page's
   * enum type and the class type
   *
   * TODO expand on this note
   */

  const std::map<PageType, EncodeWriter> encode_functions
  {
    {
      BP_TREE_HEADER_PAGE,
      [](ByteWriter<Serial>& writer, const Object& obj) {

        const auto page = static_cast<BPTreeHeaderPage*>(obj.get());

        writer << page->root_;
        writer << page->empty_;
      }
    },
    {
      BP_TREE_INTERNAL_PAGE,
      [](ByteWriter<Serial>& writer, const Object& obj) {

        const auto page = static_cast<BPTreeInternalPage*>(obj.get());

        writer << BPTreeInternalPage::ORDER;
        writer << page->node_.size();

        for (const auto& cell : page->node_) {
          
          writer << cell.key_;
          writer << cell.value_;
          writer << cell.left_;          
        }

        writer << page->right_;
      }
    },
    {
      BP_TREE_LEAF_PAGE,
      [](ByteWriter<Serial>& writer, const Object& obj) {

        const auto page = static_cast<BPTreeLeafPage*>(obj.get());

        writer << BPTreeLeafPage::ORDER;
        writer << page->node_.size();

        for (const auto& cell : page->node_) {
          
          writer << cell.key_;
          writer << cell.values_.size();

          for (const auto& value : cell.values_) {
            
            writer << value;
          }
        }

        writer << page->right_;
      }
    },
    {
      B_TREE_HEADER_PAGE,
      [](ByteWriter<Serial>& writer, const Object& obj) {

        const auto page = static_cast<BTreeHeaderPage*>(obj.get());

        writer << page->root_;
        writer << page->empty_;
      }
    },
    {
      B_TREE_NODE_PAGE,
      [](ByteWriter<Serial>& writer, const Object& obj) {

        const auto page = static_cast<BTreeNodePage*>(obj.get());

        writer << BTreeNodePage::ORDER;
        writer << page->leaf_;
        writer << page->node_.size();

        for (const auto& cell : page->node_) {

          writer << cell.key_;
          writer << cell.value_;
          writer << cell.left_;
        }

        writer << page->right_;
      }
    },
    {
      ENTRY_PAGE,
      [](ByteWriter<Serial>& writer, const Object& obj) {

        const auto page = static_cast<EntryPage*>(obj.get());

        writer << page->overflow_;
        writer << page->value_.size();

        for (uint32_t i = 0; i < page->value_.size() && writer; ++i) {

          writer << page->value_.at(i);
        }
      }
    }
  };

  const std::map<PageType, DecodeReader> decode_functions
  {
    {
      BP_TREE_HEADER_PAGE,
      [](ByteReader<const Serial>& reader) -> Object {
        
        uint32_t root;
        reader >> root;

        bool empty;
        reader >> empty;
        
        return std::make_unique<BPTreeHeaderPage>(root, empty);
      }
    },
    {
      BP_TREE_INTERNAL_PAGE,
      [](ByteReader<const Serial>& reader) -> Object {

        reader.skip(sizeof(BPTreeInternalPage::ORDER));

        std::vector<Cell>::size_type size;
        std::vector<Cell> cells;
        reader >> size;
        cells.reserve(size);

        for (int i = 0; i < size; ++i) {

          uint64_t key, value, left;
          reader >> key >> value >> left;
          cells.emplace_back(key, value, left);
        }

        uint64_t right;
        reader >> right;

        return std::make_unique<BPTreeInternalPage>(right, std::move(cells));
      }
    },
    {
      BP_TREE_LEAF_PAGE,
      [](ByteReader<const Serial>& reader) -> Object {

        reader.skip(sizeof(BPTreeLeafPage::ORDER));

        std::vector<CellBP>::size_type cells_size;
        std::vector<CellBP> cells;
        reader >> cells_size;
        cells.reserve(cells_size);

        for (int i = 0; i < cells_size; ++i) {

          uint64_t key;
          reader >> key;

          std::vector<uint64_t>::size_type values_size;
          std::vector<uint64_t> values;
          reader >> values_size;
          values.reserve(values_size);

          for (int j = 0; i < values_size; ++j) {

            uint64_t value;
            reader >> value;

            values.emplace_back(value);
          }

          cells.emplace_back(key, std::move(values));
        }

        uint64_t right;
        reader >> right;

        return std::make_unique<BPTreeLeafPage>(right, std::move(cells));
      }
    },
    {
      B_TREE_HEADER_PAGE,
      [](ByteReader<const Serial>& reader) -> Object {

        uint32_t root;
        reader >> root;

        bool empty;
        reader >> empty;

        return std::make_unique<BTreeHeaderPage>(root, empty);
      }
    },
    {
      B_TREE_NODE_PAGE,
      [](ByteReader<const Serial>& reader) -> Object {

        reader.skip(sizeof(BTreeNodePage::ORDER));

        bool leaf;
        reader >> leaf;

        std::vector<Cell>::size_type size;
        std::vector<Cell> cells;
        reader >> size;
        cells.reserve(size);

        for (int i = 0; i < size; ++i) {

          uint64_t key, value, left;
          reader >> key >> value >> left;
          cells.emplace_back(key, value, left);
        }

        uint64_t right;
        reader >> right;

        return std::make_unique<BTreeNodePage>(leaf, right, std::move(cells));
      }
    },
    {
      ENTRY_PAGE,
      [](ByteReader<const Serial>& reader) -> Object {

        uint64_t overflow;
        reader >> overflow;

        std::vector<char>::size_type size;
        std::vector<char> bytes;
        reader >> size;
        bytes.reserve(size);

        for (int i = 0; i < size; ++i) {

          reader >> bytes[i];
        }

        return std::make_unique<EntryPage>(std::move(bytes), overflow);
      }
    }
  };

}


const PageCodec PageCodec::CODEC{};

Serial PageCodec::encode(const Object& page) const {

  // Allocate array, writer wrapper, and write in the page header
  Serial bytes{};
  ByteWriter<Serial> writer{bytes, sizeof(bytes)};

  // Encode the page data, starting with the header and then the
  // rest depending on the underlying page type
  writer << static_cast<uint32_t>(page->type());
  encode_functions.at(page->type())(writer, page);

  return bytes;
}

Object PageCodec::decode(const Serial& bytes) const {

  // Establish reader wrapper
  ByteReader<const Serial> reader{bytes, sizeof(bytes)};

  // Determine what the type of the page the data is, then decode accordingly
  uint32_t type;
  reader >> type;
  return decode_functions.at(static_cast<PageType>(type))(reader);
}