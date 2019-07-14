#include "../api/Drop.h"
#include "../../commands/api/Drop.h"
using namespace std;

SQLDrop::SQLDrop(string table_name) : SQLStatement(table_name, stmtDrop) {}

SQLDrop::~ SQLDrop() = default;

unique_ptr<Command> SQLDrop::generateQuery() {
  return query();
}

std::unique_ptr<Command> SQLDrop::query() {
  return make_unique<COMDrop>(table_name_);
}
