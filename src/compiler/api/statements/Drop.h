#ifndef LOODB_SQLDROP_H
#define LOODB_SQLDROP_H

#include "Statement.h"
#include <vector>


class SQLSelect : public SQLStatement {
 
  std::unique_ptr<Command> query() const override;

 public:
  
  std::unique_ptr<Command> generateQuery() const;

};

#endif
