#include "../../api/Column/NotNullRestriction.h"


NotNullRestriction::NotNullRestriction(std::unique_ptr<Column> base) : 
  ColumnRestriction{std::move(base)}
{}

// Validate an Entry before writing to Column
bool NotNullRestriction::valid_(const Entry& entry) const {

  return entry.getType() != EntryType::NULL_ &&
         base.valid(entry);
}

// Retrieve the page index for the primary key associated with the entry
uint32_t NotNullRestriction::read_(const Entry& entry) {
  return base.read(entry);
}

// Write to Column
void NotNullRestriction::write_(uint32_t entry_index, uint32_t row_index) {
  base.write(entry_index, row_index);
}

bool NotNullRestriction::empty_() const {
  return base.empty();
}

std::unique_ptr<Column::Iterator> NotNullRestriction::begin_() {
  return base.begin();
}

std::unique_ptr<Column::Iterator> NotNullRestriction::end_() {
  return base.end();
}

std::unique_ptr<Column::Iterator> NotNullRestriction::find_(const Entry& e) {
  return base.find(e);
}