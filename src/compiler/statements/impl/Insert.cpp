#include "../api/Insert.h"
#include <string>
#include "../../../schema/api/Entry/Entry.h"
using namespace std;

class SQLInsert::Impl{
  // entries_: vector of rows to be entred; each row being a vector of entries
  vector<vector<Entry>> entries_;
 public:
  Impl(vector<vector<Entry>> e) : entries_(e) {}
  ~ Impl();
};

SQLInsert::SQLInsert(string table_name, std::vector<std::vector<Entry>> e) : 
  SQLStatement(table_name, stmtInsert), impl_{make_unique<Impl>(e)} {}

SQLInsert::~ SQLInsert() = default;

SQLInsert::unique_ptr<Command> generateQuery() const {
  return make_unique();
}