#include <iostream>
#include "../../api/Column/UniqueRestriction.h"


UniqueRestriction::UniqueRestriction(std::unique_ptr<Column> base) :
  ColumnRestriction{std::move(base)}
{}

// Validate an Entry before writing to Column
bool UniqueRestriction::valid_(const Entry& entry) const {

  return *base.find(entry) == *base.end() &&
         base.valid(entry);
}

// Retrieve the page index for the primary key associated with the entry
uint32_t UniqueRestriction::read_(const Entry& entry) {
  return base.read(entry);
}

// Write to Column
void UniqueRestriction::write_(uint32_t entry_index, uint32_t row_index) {
  base.write(entry_index, row_index);
}

// Check if Column is empty
bool UniqueRestriction::empty_() const {
  return base.empty();
}

std::unique_ptr<Column::Iterator> UniqueRestriction::begin_() {
  return base.begin();
}

std::unique_ptr<Column::Iterator> UniqueRestriction::end_() {
  return base.end();
}

std::unique_ptr<Column::Iterator> UniqueRestriction::find_(const Entry& e) {
  return base.find(e);
}