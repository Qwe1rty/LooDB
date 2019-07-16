#include "../api/BPTreeHeaderPage.h"


BPTreeHeaderPage::BPTreeHeaderPage(uint64_t root, bool empty) :
  Page(PageType::BP_TREE_HEADER_PAGE),
  root_{root},
  empty_{empty}
{}