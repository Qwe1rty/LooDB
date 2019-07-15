#include "../api/Statement.h"
using namespace std;

SQLStatement::SQLStatement(string t, StatementType type) : table_name_{t}, type_{type} {}