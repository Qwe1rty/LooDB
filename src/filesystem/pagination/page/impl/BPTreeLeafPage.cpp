#include "../api/BPTreeLeafPage.h"


const uint32_t BPTreeLeafPage::ORDER = 4;

BPTreeLeafPage::BPTreeLeafPage(uint64_t right, std::vector<CellBP> node) :
  Page(PageType::BP_TREE_LEAF_PAGE),
  right_{right},
  node_{std::move(node)}
{}