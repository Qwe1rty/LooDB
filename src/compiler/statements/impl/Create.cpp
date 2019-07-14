#include "../api/Create.h"
#include "../../commands/api/Create.h"
using namespace std;

class SQLCreate::Impl{
  // columns_: vector of column names, their repective type and modifications
  std::vector<std::tuple<std::string, std::string, std::string>> columns_;
 public:
  Impl(std::vector<std::tuple<std::string, std::string, std::string>> c) : columns_(c) {}
  ~ Impl();
};

SQLCreate::SQLCreate(std::string t, std::vector<std::tuple<std::string, std::string, std::string>> c) : 
  SQLStatement(t, stmtCreate), impl_{make_unique<Impl>(c)} {}

SQLCreate::~ SQLCreate() = default;

SQLCreate::Impl::~Impl() = default;

unique_ptr<Command> SQLCreate::generateQuery() {
  return query();
}

std::unique_ptr<Command> SQLCreate::query() {
  return make_unique<COMCreate>(table_name_);
}