#ifndef LOODB_SQLDROP_H
#define LOODB_SQLDROP_H

#include "Statement.h"

class SQLDrop : public SQLStatement {
 
  std::unique_ptr<Command> query() override;

 public:
  
  SQLDrop(std::string);
  ~ SQLDrop();
  std::unique_ptr<Command> generateQuery();

};

#endif
