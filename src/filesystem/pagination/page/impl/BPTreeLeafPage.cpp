#include "../api/BPTreeLeafPage.h"


BPTreeLeafPage::BPTreeLeafPage(uint64_t right, std::vector<CellBP> node) :
  right_{right},
  node_{std::move(node)}
{}