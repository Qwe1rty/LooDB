#include "../api/PageCodec.h"
#include "../api/PageType.h"
#include "../../page/api/Cell.h"
#include "../../page/api/CellBP.h"
#include "../../page/api/BPTreeInternalPage.h"
#include "../../page/api/BPTreeHeaderPage.h"
#include "../../../../util/ByteWriter.h"

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

  // BTreeHeaderPage offsets

  // BTreeNodePage offsets

  // EntryPage offsets

};


namespace {

  using Object = PageCodec::Object;
  using Serial = PageCodec::Serial;

  using EncodeWriter = std::function<void(const ByteWriter&, const Object&)>;
  using DecodeReader = std::function<Object(const Serial&)>;


  std::map<PageType, EncodeWriter> encode_functions
  {
    {
      BP_TREE_HEADER_PAGE,
      [](const ByteWriter& writer, const Object& obj) -> Serial {

        const auto page = dynamic_cast<BPTreeHeaderPage*>(obj.get());

        writer.write(Offset::BPTH_ROOT_OFFSET, page->root_);
      }
    },
    {
      BP_TREE_INTERNAL_PAGE,
      [](const ByteWriter& writer, const Object& obj) -> Serial {

        const auto page = dynamic_cast<BPTreeInternalPage*>(obj.get());

        writer.write(Offset::BPTI_ORDER_OFFSET, BPTreeInternalPage::ORDER);
        writer.write(Offset::BPTI_CELL_NUM_OFFSET, page->node_.size());

        for (uint32_t i = 0; i < page->node_.size(); ++i) {

          const auto& cell = page->node_.at(i);
          writer.write(
            BPTI_CELL_DATA_OFFSET + (i * CELL_OFFSET),
            cell.key_
          );
          writer.write(
            BPTI_CELL_DATA_OFFSET + (i * CELL_OFFSET) + sizeof(cell.key_),
            cell.value_
          );
          writer.write(
            BPTI_CELL_DATA_OFFSET + (i * CELL_OFFSET) + sizeof(cell.key_) + sizeof(cell.value_),
            cell.left_
          );
        }
        writer.write(
          BPTI_CELL_DATA_OFFSET + (page->node_.size() * CELL_OFFSET),
          page->right_
        );
      }
    },
    {
      BP_TREE_LEAF_PAGE,
      [](const ByteWriter& writer, const Object& obj) -> Serial {

      }
    },
    {
      B_TREE_HEADER_PAGE,
      [](const ByteWriter& writer, const Object& obj) -> Serial {

      }
    },
    {
      B_TREE_NODE_PAGE,
      [](const ByteWriter& writer, const Object& obj) -> Serial {

      }
    },
    {
      ENTRY_PAGE,
      [](const ByteWriter& writer, const Object& obj) -> Serial {

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
  writer.write(PAGE_HEADER_OFFSET, static_cast<uint32_t>(page->type()));
  encode_functions.at(page->type())(writer, page);

  return bytes;
}

Object PageCodec::decode(const Serial& bytes) const {

  // Read in the page header, and decode
//  auto type = static_cast<PageType>(bytes[PAGE_HEADER_OFFSET]);
//  return decode_functions.at(type)(bytes);
}