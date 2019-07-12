#include "../api/BPTreeInternalPage.h"
#include "../api/Cell.h"

#include <vector>


BPTreeInternalPage::BPTreeInternalPage(uint64_t right, std::vector<Cell> node) :
  right_{right},
  node_{std::move(node)}
{}