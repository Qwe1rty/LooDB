#include "../api/BPTreeInternalPage.h"


BPTreeInternalPage::BPTreeInternalPage(uint64_t right, std::vector<Cell> node) :
  right_{right},
  node_{std::move(node)}
{}