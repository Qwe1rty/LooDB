#include "../api/Cursor.h"
#include "../api/Table.h"
#include "../api/Entry/Entry.h"
#include "../api/Entry/EntryCodec.h"
#include "../../filesystem/pagination/page/api/Page.h"
#include "../../filesystem/pagination/interface/api/Pager.h"
#include "../../filesystem/pagination/page/api/BPTreeLeafPage.h"
#include "../../filesystem/pagination/page/api/CellBP.h"
#include "../../filesystem/pagination/page/api/EntryPage.h"
#include <memory>
#include <string>
#include <vector>

// Constructor
// Takes in path to B+tree and bool loc
// loc == false -> start, loc == true -> end
Cursor::Impl::Impl(Pager& bptree, Pager& data, bool loc) : bptree_(bptree), data_(data),
  page_index_(loc == 0 ? 0 : bptree_.size()) {}

// Constructor
// Takes in path to B+tree and bool loc
// loc == false -> start, loc == true -> end
Cursor::Cursor(Pager& bptree, Pager& data, bool loc) : impl_(std::make_unique<Impl>(bptree, data, loc)) {}

// Check that bptree_ paths aren't not equal or page_index_ aren't equal
// TODO: Add check for bptree_ paths when available
bool Cursor::operator!=(const Cursor& other) const {
  return (this->impl_->page_index_ != other.impl_->page_index_);
}

// Increment page_index_
Cursor& Cursor::operator++() {
  ++this->impl_->page_index_;
  return *this;
}

// Dereference page and return the row as a vector of Entries
std::vector<std::unique_ptr<Entry>> Cursor::operator*() const {
  // Get B+ leaf page
  std::unique_ptr<BPTreeLeafPage> page = std::move(this->impl_->bptree_.fetch<BPTreeLeafPage>(this->impl_->page_index_));

  // B+ Leaf nodes only have 1 CellBP
  std::vector<uint64_t> entry_indices = page->node_[0].values_;

  // Declare our return vector
  std::vector<std::unique_ptr<Entry>> entries;

  // Declare EntryCodec
  EntryCodec CODEC;

  for (int i = 0; i < entry_indices.size(); ++i) {
    // Get Entry page
    std::unique_ptr<EntryPage> entryPage = std::move(this->impl_->data_.fetch<EntryPage>(entry_indices[i]));

    // Push decoded entry into entries
    entries.emplace_back(std::move(CODEC.decode(entryPage->value_)));
  }

  return entries;
}