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

std::unique_ptr<Column::Iterator> Column::begin() {
  return begin_();
}

std::unique_ptr<Column::Iterator> Column::end() {
  return end_();
}

std::unique_ptr<Column::Iterator> Column::find(const Entry& entry) {
  return find_(entry);
}