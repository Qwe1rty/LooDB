#ifndef LOODB_SQLCREATE_H
#define LOODB_SQLCREATE_H

#include "Statement.h"
#include <vector>
#include <tuple>
#include <memory>

class SQLCreate : public SQLStatement {
  // columns_: vector of column names and their repective type
  // modifications_: a vector of columns names and modifications to their type
  class Impl;
  std::unique_ptr<Impl> impl_;
 public:
  
  SQLCreate(std::string, std::vector<std::tuple<std::string, std::string, std::string>>);

};

#endif
