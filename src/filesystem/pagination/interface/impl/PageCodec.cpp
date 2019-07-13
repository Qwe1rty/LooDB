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

#include <functional>
#include <map>


enum Offset {

  PAGE_HEADER_OFFSET = 0,
  CELL_OFFSET = sizeof(Cell),

  // BPTreeHeaderPage offsets
  BPTH_ROOT_OFFSET = PAGE_HEADER_OFFSET + 4,

  // BPTreeInternalPage offsets
  BPTI_ORDER_OFFSET = PAGE_HEADER_OFFSET + 4,
  BPTI_CELL_NUM_OFFSET = BPTI_ORDER_OFFSET + sizeof(BPTreeInternalPage::ORDER),
  BPTI_CELL_DATA_OFFSET = BPTI_CELL_NUM_OFFSET + sizeof(std::vector<Cell>::size_type),

  // BPTreeLeafPage offsets
  BPTL_ORDER_OFFSET = PAGE_HEADER_OFFSET + 4,
  BPTL_CELL_NUM_OFFSET = BPTL_ORDER_OFFSET + sizeof(BPTreeLeafPage::ORDER),
  BPTL_CELL_DATA_OFFSET = BPTL_CELL_NUM_OFFSET + sizeof(std::vector<CellBP>::size_type),

  // BTreeHeaderPage offsets

  // BTreeNodePage offsets

  // EntryPage offsets

};


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

  // Read in the page header, and decode
//  auto type = static_cast<PageType>(bytes[PAGE_HEADER_OFFSET]);
//  return decode_functions.at(type)(bytes);
}