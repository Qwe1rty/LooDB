#include "../api/Insert.h"
#include "../api/StatementType.h"
#include <vector>
#include <string>
#include <memory>
#include <utility>

SQLInsert::Impl::Impl(std::vector<std::unique_ptr<Entry>> e) : entries_(std::move(e)) {}

SQLInsert::SQLInsert(std::string table_name, std::vector<std::unique_ptr<Entry>> e) : 
  SQLStatement(table_name, StatementType::stmtInsert), impl_{std::make_unique<Impl>(std::move(e))} {}

std::vector<std::unique_ptr<Entry>> SQLInsert::getEntries() const {
  return impl_->entryGetter();
}

std::vector<std::unique_ptr<Entry>> SQLInsert::Impl::entryGetter() const {
  return entries_;
}
