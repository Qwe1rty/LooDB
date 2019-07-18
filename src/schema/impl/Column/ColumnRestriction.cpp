#include "../../api/Column/ColumnRestriction.h"
using namespace std;

ColumnRestriction::ColumnRestriction(unique_ptr<Column> c) : 
    impl_{make_unique<ColumnRestrictionImpl>(move(c))} {}
  
ColumnRestriction::ColumnRestrictionImpl::ColumnRestrictionImpl(unique_ptr<Column> c) :
  base_{move(c)} {}

// Validate an Entry before writing to Column
bool ColumnRestriction::valid(const Entry& entry) const {
  valid_(entry);
}

// Retrieve the page index for the primary key associated with the entry
uint32_t ColumnRestriction::read(const Entry& entry) {
  read_(entry);
}

// Write to Column
void ColumnRestriction::write(uint32_t entry_index, uint32_t row_index) {
  write_(entry_index, row_index);
}

// Validate an Entry before writing to Column
bool ColumnRestriction::valid_(const Entry& entry) const {
  return impl_->base_->valid(entry);
}

// Retrieve the page index for the primary key associated with the entry
uint32_t ColumnRestriction::read_(const Entry& entry) {
  return impl_->base_->read(entry);
}

// Write to Column
void ColumnRestriction::write_(uint32_t entry_index, uint32_t row_index) {
  impl_->base_->write(entry_index,row_index);
}

// NVI for empty_()
bool ColumnRestriction::empty_() const {
  return impl_->base_->empty();
}

//NVI for begin_()
std::unique_ptr<Column::Iterator> ColumnRestriction::begin_() {
  return impl_->base_->begin();
}

// NVI for end_()
std::unique_ptr<Column::Iterator> ColumnRestriction::end_()  {
  return impl_->base_->end();
}

// NVI for find_()
std::unique_ptr<Column::Iterator> ColumnRestriction::find_(const Entry& e) {
  return impl_->base_->find(e);
}

// NVI for empty_()
bool ColumnRestriction::empty() const {
  return empty_();
}

//NVI for begin_()
std::unique_ptr<Column::Iterator> ColumnRestriction::begin() {
  return begin_();
}

// NVI for end_()
std::unique_ptr<Column::Iterator> ColumnRestriction::end() {
  return end_();
}

// NVI for find_()
std::unique_ptr<Column::Iterator> ColumnRestriction::find(const Entry& e) {
  return find_(e);
}