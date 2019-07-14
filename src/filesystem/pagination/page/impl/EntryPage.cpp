#include "../api/EntryPage.h"


EntryPage::EntryPage(std::vector<char> value, uint64_t overflow) :
  Page(PageType::ENTRY_PAGE),
  value_{std::move(value)},
  overflow_{overflow}
{
  if (value_.size() > CAPACITY) {
    throw std::invalid_argument("Size of the entry exceeds maximum limit: value size is " +
                                std::to_string(value.size()) +
                                ", but cannot exceed " +
                                std::to_string(CAPACITY));
  }
}