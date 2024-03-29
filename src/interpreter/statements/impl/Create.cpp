#include "../api/Create.h"
#include "../../../schema/api/Entry/EntryType.h"

SQLCreate::Impl::Impl(std::vector<std::tuple<std::string, EntryType, std::string>> c) : columns_(c) {}

SQLCreate::SQLCreate(std::string t, std::vector<std::tuple<std::string, EntryType, std::string>> c) : 
  SQLStatement(t, stmtCreate), impl_{std::make_unique<Impl>(c)} {}

std::vector<std::tuple<std::string, EntryType, std::string>>& SQLCreate::Impl::columnGetter()  {
  return columns_;
}

std::vector<std::tuple<std::string, EntryType, std::string>>& SQLCreate::getColumns() const {
  return impl_->columnGetter();
}