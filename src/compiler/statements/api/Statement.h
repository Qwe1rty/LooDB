#ifndef LOODB_SQLSTMT_H
#define LOODB_SQLSTMT_H

#include <memory>
#include "StatementType.h"
#include <string>

/** This is the ABC for out sequel statements*/
class SQLStatement {
  
 protected:

  SQLStatement(std::string, StatementType);  
  std::string table_name_;
  StatementType type_;
  
};


#endif
