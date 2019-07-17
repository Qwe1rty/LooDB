#include "../../api/Column/Column.h"


bool Column::valid(const Entry& entry) const {
  return valid_(entry);
}

void Column::write(uint32_t entry_index, uint32_t row_index) {
  write_(entry_index, row_index);
}

uint32_t Column::read(const Entry& entry) {
  return read_(entry);
}


// None of these operators should actually ever be accessed directly

uint32_t Column::Iterator::operator*() {
  return 0;
}

Column::Iterator& Column::Iterator::operator++() {
  return *this;
}

bool Column::Iterator::operator!=(const Column::Iterator& src) {
  return !(*this == src);
}

bool Column::Iterator::operator==(const Column::Iterator&) {
  return true;
}
