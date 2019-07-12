#include "../api/Cell.h"


Cell::Cell(uint64_t key, uint64_t value, uint64_t left) :
  key_{key},
  value_{value},
  left_{left}
{}