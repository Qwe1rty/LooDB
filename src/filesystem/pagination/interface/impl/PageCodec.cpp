#include "../api/PageCodec.h"
#include "../api/PageType.h"
#include "../../page/api/Cell.h"
#include "../../page/api/CellBP.h"
#include "../../page/api/BTreeHeaderPage.h"
#include "../../page/api/BPTreeInternalPage.h"
#include "../../page/api/BPTreeHeaderPage.h"
#include "../../page/api/BPTreeLeafPage.h"
#include "../../../../util/ByteWriter.h"
#include "../../page/api/BTreeNodePage.h"
#include "../../page/api/EntryPage.h"

#include <functional>
#include <map>


namespace {

  using Object = PageCodec::Object;
  using Serial = PageCodec::Serial;

  using EncodeWriter = std::function<void(ByteWriter&, const Object&)>;
  using DecodeReader = std::function<Object(const Serial&)>;

  /*
   * Implementation of the PageCodec class is similar to a more traditional
   * visitor pattern, but makes use of the PageType enum to differentiate the
   * dynamic page type.
   */

  std::map<PageType, EncodeWriter> encode_functions
  {
    {
      BP_TREE_HEADER_PAGE,

      [](ByteWriter& writer, const Object& obj) {

        const auto page = dynamic_cast<BPTreeHeaderPage*>(obj.get());

        writer << page->root_;
      }
    },
    {
      BP_TREE_INTERNAL_PAGE,
      [](ByteWriter& writer, const Object& obj) {

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
      [](ByteWriter& writer, const Object& obj) {

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
      [](ByteWriter& writer, const Object& obj) {

        const auto page = dynamic_cast<BTreeHeaderPage*>(obj.get());

        writer << page->root_;
      }
    },
    {
      B_TREE_NODE_PAGE,
      [](ByteWriter& writer, const Object& obj) {

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
      [](ByteWriter& writer, const Object& obj) {

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
      [](const Serial& bytes) -> Object {

      }
    },
    {
      BP_TREE_INTERNAL_PAGE,
      [](const Serial& bytes) -> Object {

      }
    },
    {
      BP_TREE_LEAF_PAGE,
      [](const Serial& bytes) -> Object {

      }
    },
    {
      B_TREE_HEADER_PAGE,
      [](const Serial& bytes) -> Object {

      }
    },
    {
      B_TREE_NODE_PAGE,
      [](const Serial& bytes) -> Object {

      }
    },
    {
      ENTRY_PAGE,
      [](const Serial& bytes) -> Object {

      }
    }
  };

}


Serial PageCodec::encode(const Object& page) const {

  // Allocate array, writer wrapper, and write in the page header
  Serial bytes{new char[Page::PAGE_SIZE]};
  ByteWriter writer{bytes};

  // Encode the page data, starting with the header and then the
  // rest depending on the underlying page type
  writer << static_cast<uint32_t>(page->type());
  encode_functions.at(page->type())(writer, page);

  return bytes;
}

Object PageCodec::decode(const Serial& bytes) const {

  // TODO
}