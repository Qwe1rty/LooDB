#include "../api/BTreeNodePage.h"


const uint32_t BTreeNodePage::ORDER = 4;

BTreeNodePage::BTreeNodePage(uint64_t right, std::vector<Cell> node) :
  Page(PageType::B_TREE_NODE_PAGE),
  right_{right},
  node_{std::move(node)}
{}
