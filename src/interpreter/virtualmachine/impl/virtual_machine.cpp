#include "../api/virtual_machine.h"
#include "../../statements/api/Create.h"
#include "../../statements/api/Drop.h"
#include "../../statements/api/Select.h"
#include "../../statements/api/Insert.h"
#include "../../../schema/api/Database.h"
#include <iostream>
using namespace std;

void VM::execute(unique_ptr<SQLStatement> s, Database & db) {
  if(s->type_ == stmtCreate) {
    const SQLCreate& p = static_cast<SQLCreate&>(*s);
    db.create_table(p);
  } else if(s->type_ == stmtInsert) {
    const SQLInsert& p = static_cast<SQLInsert&>(*s);
    db.insert(p);
  } else if(s->type_ == stmtDrop) {
    const SQLDrop& p = static_cast<SQLDrop&>(*s);
    db.drop_table(p);
  } else if(s->type_ == stmtSelect) {
    const SQLSelect& p = static_cast<SQLSelect&>(*s);
    db.select(p);
  } else {
    cout << "No commands to execute" << endl;
  }

}