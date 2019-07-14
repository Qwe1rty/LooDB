#include "../api/Select.h"
using namespace std;

class SQLSelect::Impl{
  // columns_: vector of column names
  // whereClause__: a vector of columns names and their respective entries
  // whereOps_: vector of operations acting on whereClause_
  // where_: a boolean flag to determine the existence of a where clause
  std::vector<std::string> columns_;
  std::vector<std::string, Entry> whereClause_;
  std::vector<std::string> whereOps_;
  bool where_;
 public:
  Impl(std::vector<std::string> c, std::vector<std::string, Entry> wC,
   std::vector<std::string> wO, bool w)
   : columns_(c), whereClause_(wC), whereOps_(wO), where_(w) {}
};

SQLSelect::SQLSelect(string table_name, std::vector<std::string> c, 
  std::vector<std::string, Entry> wC, std::vector<std::string> wO, bool w) : 
  SQLStatement(table_name, stmtSelect), impl_{make_unique<Impl>(c, wC, wO, w)} {}
