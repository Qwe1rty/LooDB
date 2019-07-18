#include "../../api/Column/NotNullRestriction.h"
using namespace std;

NotNullRestriction::NotNullRestriction(unique_ptr<Column> s) : 
    ColumnRestriction(move(s)) {}

// Validate an Entry before writing to Column
bool NotNullRestriction::valid(const Entry& entry) const {
  return valid_(entry);
}

// Retrieve the page index for the primary key associated with the entry
uint32_t NotNullRestriction::read(const Entry& entry) {
  return read_(entry);
}

// Write to Column
void NotNullRestriction::write(uint32_t entry_index, uint32_t row_index) {
  return write_(entry_index, row_index);
}

// Validate an Entry before writing to Column
bool NotNullRestriction::valid_(const Entry& entry) const {
    // perform not null check
  return impl_->base_->valid(entry);
}

// Retrieve the page index for the primary key associated with the entry
uint32_t NotNullRestriction::read_(const Entry& entry) {
  return impl_->base_->read(entry);
}

// Write to Column
void NotNullRestriction::write_(uint32_t entry_index, uint32_t row_index) {
  return impl_->base_->write(entry_index, row_index);
}

// NVI for empty_()
bool NotNullRestriction::empty() const {
  return empty_();
}

//NVI for begin_()
std::unique_ptr<Column::Iterator> NotNullRestriction::begin() {
  return begin_();
}

// NVI for end_()
std::unique_ptr<Column::Iterator> NotNullRestriction::end() {
  return end_();
}

// NVI for find_()
std::unique_ptr<Column::Iterator> NotNullRestriction::find(const Entry& e) {
  return find_(e);
}

bool NotNullRestriction::empty_() const {
  return impl_->base_->empty();
}

std::unique_ptr<Column::Iterator> NotNullRestriction::begin_() {
  return impl_->base_->begin();
}

std::unique_ptr<Column::Iterator> NotNullRestriction::end_() {
  return impl_->base_->end();
}

std::unique_ptr<Column::Iterator> NotNullRestriction::find_(const Entry& e) {
  return impl_->base_->find(e);
}