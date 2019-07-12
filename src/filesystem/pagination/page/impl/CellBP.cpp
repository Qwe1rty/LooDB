#include "../api/CellBP.h"

#include <vector>


CellBP::CellBP(uint64_t key, std::vector<uint64_t> values) :
  key_{key},
  values_{std::move(values)}
{}