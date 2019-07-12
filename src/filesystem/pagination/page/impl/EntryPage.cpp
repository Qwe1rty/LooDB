#include "../api/EntryPage.h"


EntryPage::EntryPage(std::unique_ptr<char[]> value, uint64_t overflow) :
  Page(PageType::ENTRY_PAGE),
  value_{std::move(value)},
  overflow_{overflow}
{}