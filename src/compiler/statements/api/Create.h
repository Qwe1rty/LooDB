#ifndef LOODB_SQLCREATE_H
#define LOODB_SQLCREATE_H

#include "Statement.h"
#include <vector>
#include <tuple>

class SQLCreate : public SQLStatement {
  // columns_: vector of column names and their repective type
  // modifications_: a vector of columns names and modifications to their type
  class Impl;
  std::unique_ptr<Impl> impl_;
  std::unique_ptr<Command> query() override;
 public:
  
  SQLCreate(std::string, std::vector<std::tuple<std::string, std::string, std::string>>);
  ~ SQLCreate();  
  std::unique_ptr<Command> generateQuery();

};

#endif
