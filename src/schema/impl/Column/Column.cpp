#include "../../api/Column/Column.h"


void Column::write(uint32_t entry_index, uint32_t row_index) {
  write_(entry_index, row_index);
}