#ifndef LOODB_SQLSTMT_H
#define LOODB_SQLSTMT_H

#include <memory>
#include "../../commands/api/Command.h"
#include "StatementType.h"

/** This is the ABC for out sequel statements*/
class SQLStatement {

  std::string table_name_;
  StatementType type_;
    /// evaluate the complete expression tree and return the subsequent command
  virtual std::unique_ptr<Command> query() const = 0;

 protected:
  SQLStatement(std::string, StatementType);  
 public:

  virtual ~SQLStatement();
};


#endif