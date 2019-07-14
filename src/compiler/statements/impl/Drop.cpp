#include "../api/Drop.h"
using namespace std;

SQLDrop::SQLDrop(string table_name) : SQLStatement(table_name, stmtDrop) {}

