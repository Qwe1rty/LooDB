#include "../api/BTreeHeaderPage.h"


BTreeHeaderPage::BTreeHeaderPage(uint64_t root) :
  Page(PageType::B_TREE_HEADER_PAGE),
  root_{root}
{}
