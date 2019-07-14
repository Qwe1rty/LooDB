#include "../api/Insert.h"
#include <utility>
using namespace std;

class SQLInsert::Impl{
  // entries_: vector of rows to be entred; each row being a vector of entries
  vector<vector<unique_ptr<Entry>>> entries_;
 public:
  Impl(vector<vector<unique_ptr<Entry>>> e) : entries_(move(e)) {}
};

SQLInsert::SQLInsert(string table_name, std::vector<std::vector<unique_ptr<Entry>>> e) : 
  SQLStatement(table_name, stmtInsert), impl_{make_unique<Impl>(move(e))} {}
