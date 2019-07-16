#include "Parser.h"
#include "../statements/api/Select.h"
#include "../statements/api/StatementType.h"
#include <iostream>
#include <memory>

int main () {
  Parser p;
  p.parse ("hello");
  
  if (p.result) {
    std::cout << "Received statement of type (";
    std::cout << p.result->type_;
    std::cout << ") on table ";
    std::cout << p.result->table_name_;
    std::cout << std::endl;

    if (p.result->type_ == StatementType::stmtSelect) {
      if (static_cast<SQLSelect*>(p.result.get())->hasWhere()) {
        static_cast<SQLSelect*>(p.result.get())->printWhere();
      }
    }
  }

  return 0;
}