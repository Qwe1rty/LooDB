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
#include "../../page/api/PropertiesPage.h"

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

  /*
   * NOTE: When encoding the ::size_t field of a vector or something, you have to
   * cast it to something (like uint32_t) and read it back with the same type for
   * it to work since the ::size_t will cast to something else in the ByteWriter
   *
   * eg.
   * - Writing: static_cast<uint32_t>(vector.size());
   * - Reading: uint32_t size; reader >> size;
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
        writer << static_cast<uint32_t>(page->node_.size());

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
        writer << static_cast<uint32_t>(page->node_.size());

        for (const auto& cell : page->node_) {
          
          writer << cell.key_;
          writer << static_cast<uint32_t>(cell.values_.size());

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
        writer << static_cast<uint32_t>(page->node_.size());

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
        writer << static_cast<uint32_t>(page->value_.size());

        for (uint32_t i = 0; i < page->value_.size() && writer; ++i) {

          writer << page->value_.at(i);
        }
      },
    },
    {
      PROPERTIES_PAGE,
      [](ByteWriter<Serial>& writer, const Object& obj) {

        const auto page = static_cast<PropertiesPage*>(obj.get());

        writer << static_cast<uint32_t>(page->type_);

        writer << static_cast<uint32_t>(page->column_.size());
        for (uint32_t i = 0; i < page->column_.size() && writer; ++i) {
          writer << page->column_[i];
        }

        writer << static_cast<uint32_t>(page->restrictions_.size());
        for (uint32_t i = 0; i < page->restrictions_.size() && writer; ++i) {
          writer << page->restrictions_[i];
        }
      }
    }
  };

  const std::map<PageType, DecodeReader> decode_functions
  {
    {
      BP_TREE_HEADER_PAGE,
      [](ByteReader<const Serial>& reader) -> Object {
        
        uint64_t root;
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

        uint32_t size;
        reader >> size;
        std::vector<Cell> cells;
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

        uint32_t cells_size;
        reader >> cells_size;
        std::vector<CellBP> cells;
        cells.reserve(cells_size);

        for (int i = 0; i < cells_size; ++i) {

          uint64_t key;
          reader >> key;

          uint32_t values_size;
          reader >> values_size;
          std::vector<uint64_t> values;
          values.reserve(values_size);

          for (int j = 0; j < values_size; ++j) {

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

        uint64_t root;
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

        uint32_t size;
        reader >> size;
        std::vector<Cell> cells;
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

        uint32_t size;
        reader >> size;
        std::vector<char> bytes;
        bytes.reserve(size);

        for (int i = 0; i < size; ++i) {

          char b;
          reader >> b;
          bytes.emplace_back(b);
        }

        return std::make_unique<EntryPage>(std::move(bytes), overflow);
      }
    },
    {
      PROPERTIES_PAGE,
      [](ByteReader<const Serial>& reader) -> Object {

        uint32_t type;
        reader >> type;

        uint32_t column_size;
        reader >> column_size;
        std::string column;
        column.reserve(column_size);

        for (uint32_t i = 0; i < column_size; ++i) {

          char b;
          reader >> b;
          column += b;
        }

        uint32_t restrictions_size;
        reader >> restrictions_size;
        std::string restrictions;
        column.reserve(restrictions_size);

        for (int i = 0; i < restrictions_size; ++i) {

          char b;
          reader >> b;
          restrictions += b;
        }

        return std::make_unique<PropertiesPage>(
          static_cast<EntryType>(type),
          std::move(column),
          std::move(restrictions)
        );
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