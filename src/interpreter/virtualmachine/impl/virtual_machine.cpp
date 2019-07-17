#include "../api/virtual_machine.h"
#include "../../../schema/api/Database.h"
using namespace std;

void VM::execute(unique_ptr<SQLStatement> s, Database & db) {
  switch (s->type_) {
    case stmtCreate: db.create_table(move(s));
                     break;
    case stmtInsert: db.insert(move(s));
                     break;
    case stmtDrop: db.drop_table(move(s));
                   break;
    case stmtSelect: db.select(move(s));
                     break;
    default: break;
  }
}
