#include "../../api/Column/UniqueRestriction.h"
using namespace std;

UniqueRestriction::UniqueRestriction(unique_ptr<Column> c) : 
    ColumnRestriction{move(c)} {}

// Validate an Entry before writing to Column
bool UniqueRestriction::valid(const Entry& entry) const {
  return valid_(entry);
}

// Retrieve the page index for the primary key associated with the entry
uint32_t UniqueRestriction::read(const Entry& entry) {
  return read_(entry);
}

// Write to Column
void UniqueRestriction::write(uint32_t entry_index, uint32_t row_index) {
  write_(entry_index, row_index);
}

// Validate an Entry before writing to Column
bool UniqueRestriction::valid_(const Entry& entry) const {
    // check uniqueness
  return impl_->base_->valid(entry);
}

// Retrieve the page index for the primary key associated with the entry
uint32_t UniqueRestriction::read_(const Entry& entry) {
  return impl_->base_->read(entry);
}

// Write to Column
void UniqueRestriction::write_(uint32_t entry_index, uint32_t row_index) {
  impl_->base_->write(entry_index, row_index);
}

// Check if Column is empty
bool UniqueRestriction::empty_() const {
  return impl_->base_->empty();
}

std::unique_ptr<Column::Iterator> UniqueRestriction::begin_() {
  return impl_->base_->begin();
}

std::unique_ptr<Column::Iterator> UniqueRestriction::end_() {
  return impl_->base_->end();
}

std::unique_ptr<Column::Iterator> UniqueRestriction::find_(const Entry& e) {
  return impl_->base_->find(e);
}