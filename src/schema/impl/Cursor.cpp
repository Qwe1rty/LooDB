#include "../api/Cursor.h"
#include "../api/Entry/Entry.h"
#include "../api/Entry/EntryCodec.h"
#include "../../filesystem/pagination/page/api/Page.h"
#include "../../filesystem/pagination/interface/api/Pager.h"
#include "../../filesystem/pagination/page/api/BPTreeLeafPage.h"
#include "../../filesystem/pagination/page/api/CellBP.h"
#include "../../filesystem/pagination/page/api/EntryPage.h"
#include <iostream>
#include <memory>
#include <vector>

// Constructor
// Takes in path to row and bool loc
// loc == false -> start, loc == true -> end
Cursor::Impl::Impl(std::string rowPath, std::string dataPath, int pageIndex) :
  rowPath_(rowPath), dataPath_(dataPath),
  row_(std::make_unique<Pager>(rowPath)),
  data_(std::make_unique<Pager>(dataPath)),
  page_index_(pageIndex == 0 ? 0 : (pageIndex < 0 ? row_->size() : static_cast<uint32_t>(pageIndex))) {}

// Constructor
// Takes in path to row and bool loc
// loc == false -> start, loc == true -> end
Cursor::Cursor(std::string rowPath, std::string dataPath, int pageIndex) :
  impl_(std::make_unique<Impl>(rowPath, dataPath, pageIndex)) {}

// Check that row paths aren't not equal or page_index_ aren't equal
bool Cursor::operator!=(const Cursor& other) const {
  // std::cerr << "compare row paths : ";
  // std::cerr << (this->impl_->rowPath_ != other.impl_->rowPath_) << std::endl;
  // std::cerr << "compare page indices : ";
  // std::cerr << (this->impl_->page_index_ != other.impl_->page_index_) << std::endl;

  return (
    (this->impl_->rowPath_ != other.impl_->rowPath_) ||
    (this->impl_->page_index_ != other.impl_->page_index_)
  );
}

// Increment page_index_
Cursor& Cursor::operator++() {
  ++(this->impl_->page_index_);
  return *this;
}

// Dereference page and return the row as a vector of Entries
std::vector<std::unique_ptr<Entry>> Cursor::operator*() const {
  // Get B+ leaf page
  // std::cerr << "page index: " << this->impl_->page_index_;
  // std::cerr << "row size: " << this->impl_->row_->size();
  std::unique_ptr<BPTreeLeafPage> page = std::move(this->impl_->row_->fetch<BPTreeLeafPage>(this->impl_->page_index_));
  // std::cerr << "we made it" << std::endl;

  // B+ Leaf nodes only have 1 CellBP
  std::vector<uint64_t> entry_indices = page->node_[0].values_;

  // Declare our return vector
  std::vector<std::unique_ptr<Entry>> entries;

  // Declare EntryCodec
  EntryCodec CODEC;

  for (int i = 0; i < entry_indices.size(); ++i) {
    // Get Entry page
    std::unique_ptr<EntryPage> entryPage = std::move(this->impl_->data_->fetch<EntryPage>(entry_indices[i]));

    // Push decoded entry into entries
    entries.emplace_back(std::move(CODEC.decode(entryPage->value_)));
  }

  return entries;
}
