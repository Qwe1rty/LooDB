#include "../api/BPTreeInternalPage.h"


const uint32_t BPTreeInternalPage::ORDER = 4;

BPTreeInternalPage::BPTreeInternalPage(uint64_t right, std::vector<Cell> node) :
  Page(PageType::BP_TREE_INTERNAL_PAGE),
  right_{right},
  node_{std::move(node)}
{}