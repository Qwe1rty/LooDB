#include "../api/BTreeNodePage.h"


BTreeNodePage::BTreeNodePage(uint64_t right, std::vector<Cell> node) :
  right_{right},
  node_{std::move(node)}
{}
