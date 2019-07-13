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
  using DecodeReader = std::function<Object(ByteReader<Serial>&)>;

  /*
   * Implementation of the PageCodec class is similar to a more traditional
   * visitor pattern, but makes use of the PageType enum to differentiate the
   * dynamic page type.
   *
   * TODO expand on this note
   */

  std::map<PageType, EncodeWriter> encode_functions
  {
    {
      BP_TREE_HEADER_PAGE,
      [](ByteWriter<Serial>& writer, const Object& obj) {

        const auto page = dynamic_cast<BPTreeHeaderPage*>(obj.get());

        writer << page->root_;
      }
    },
    {
      BP_TREE_INTERNAL_PAGE,
      [](ByteWriter<Serial>& writer, const Object& obj) {

        const auto page = dynamic_cast<BPTreeInternalPage*>(obj.get());

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

        const auto page = dynamic_cast<BPTreeLeafPage*>(obj.get());

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

        const auto page = dynamic_cast<BTreeHeaderPage*>(obj.get());

        writer << page->root_;
      }
    },
    {
      B_TREE_NODE_PAGE,
      [](ByteWriter<Serial>& writer, const Object& obj) {

        const auto page = dynamic_cast<BTreeNodePage*>(obj.get());

        writer << BTreeNodePage::ORDER;
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

        const auto page = dynamic_cast<EntryPage*>(obj.get());

        writer << page->overflow_;
        writer << page->value_.size();

        for (uint32_t i = 0; i < page->value_.size() && writer; ++i) {

          writer << page->value_.at(i);
        }
      }
    }
  };

  std::map<PageType, DecodeReader> decode_functions
  {
    {
      BP_TREE_HEADER_PAGE,
      [](ByteReader<Serial>& reader) -> Object {
        
        uint32_t root;
        reader >> root;
        
        return std::make_unique<BPTreeHeaderPage>(root);
      }
    },
    {
      BP_TREE_INTERNAL_PAGE,
      [](ByteReader<Serial>& reader) -> Object {

      }
    },
    {
      BP_TREE_LEAF_PAGE,
      [](ByteReader<Serial>& reader) -> Object {

      }
    },
    {
      B_TREE_HEADER_PAGE,
      [](ByteReader<Serial>& reader) -> Object {

        uint32_t root;
        reader >> root;

        return std::make_unique<BTreeHeaderPage>(root);
      }
    },
    {
      B_TREE_NODE_PAGE,
      [](ByteReader<Serial>& reader) -> Object {

      }
    },
    {
      ENTRY_PAGE,
      [](ByteReader<Serial>& reader) -> Object {

      }
    }
  };

}


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
  ByteReader<Serial> reader{bytes, sizeof(bytes)};

  // Determine what the type of the page the data is, then decode accordingly
  uint32_t type;
  reader >> type;
  return decode_functions.at(static_cast<PageType>(type))(reader);
}