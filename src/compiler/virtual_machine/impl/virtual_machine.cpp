#include "../api/virtual_machine.h"
#include "../../../schema/api/Database.h"
using namespace std;

void VM::execute(unique_ptr<SQLStatement> s, Database & db) {
  switch (s->type_) {
    case stmtCreate: db.create_table();
                     break;
    case stmtInsert: db.drop_table();
                     break;
    case stmtDrop: db.drop_table();
                   break;
    case stmtSelect:
                     break;
    default: break;
  }
}
