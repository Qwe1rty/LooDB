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

  // Allocate array, and write in the page header
  Serial bytes{new char[Page::PAGE_SIZE]};
  bytes[PAGE_HEADER_OFFSET] = static_cast<char>(page->type());

  // Encode the rest of the page's data depending on its type
  ByteWriter writer{bytes};
  encode_functions.at(page->type())(writer, page);

  return bytes;
}

Object PageCodec::decode(const Serial& bytes) const {

  // Read in the page header, and decode
//  auto type = static_cast<PageType>(bytes[PAGE_HEADER_OFFSET]);
//  return decode_functions.at(type)(bytes);
}