#include "../api/Create.h"
using namespace std;

class SQLCreate::Impl{
  // columns_: vector of column names, their repective type and modifications
  std::vector<std::tuple<std::string, std::string, std::string>> columns_;
 public:
  Impl(std::vector<std::tuple<std::string, std::string, std::string>> c) : columns_(c) {}
};

SQLCreate::SQLCreate(std::string t, std::vector<std::tuple<std::string, std::string, std::string>> c) : 
  SQLStatement(t, stmtCreate), impl_{make_unique<Impl>(c)} {}
