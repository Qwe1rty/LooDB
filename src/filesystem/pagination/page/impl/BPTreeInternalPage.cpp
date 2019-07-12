#include "../api/BPTreeInternalPage.h"


BPTreeInternalPage::BPTreeInternalPage(uint64_t right, std::vector<Cell> node) :
  Page(PageType::BP_TREE_INTERNAL_PAGE),
  right_{right},
  node_{std::move(node)}
{}