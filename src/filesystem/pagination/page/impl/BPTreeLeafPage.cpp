#include "../api/BPTreeLeafPage.h"
#include "../api/CellBP.h"

#include <vector>


BPTreeLeafPage::BPTreeLeafPage(uint64_t right, std::vector<CellBP> node) :
  right_{right},
  node_{std::move(node)}
{}