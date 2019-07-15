#include "../api/Select.h"
#include <utility>
using namespace std;

class SQLSelect::Impl{
  // columns_: vector of column names
  // whereClause__: a vector of columns names and their respective entries
  // whereOps_: vector of operations acting on whereClause_
  // where_: a boolean flag to determine the existence of a where clause
  vector<string> columns_;
  vector<tuple<string, unique_ptr<Entry>> > whereClause_;
  vector<string> whereOps_;
  bool where_;
 public:
  Impl(vector<string> c, vector<tuple<string, unique_ptr<Entry>> > wC,
   vector<string> wO, bool w)
   : columns_(c), whereClause_(move(wC)), whereOps_(wO), where_(w) {}

  bool getWhere();
};

SQLSelect::SQLSelect(string table_name, vector<string> c, 
  vector<tuple<string, unique_ptr<Entry>>> wC, vector<string> wO, bool w) : 
  SQLStatement(table_name, stmtSelect), impl_{make_unique<Impl>(c, move(wC), wO, w)} {}

bool SQLSelect::Impl::getWhere() { return where_; }

bool SQLSelect::isWhere() {
  return impl_->getWhere();
}
