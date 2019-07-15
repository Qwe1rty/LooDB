#ifndef LOODB_SQLSELECT_H
#define LOODB_SQLSELECT_H

#include "Statement.h"
#include "../../../schema/api/Entry/Entry.h"
#include <memory>
#include <tuple>
#include <vector>


class SQLSelect : public SQLStatement {
  // columns_: vector of column names
  // whereClause__: a vector of columns names and their respective entries
  // whereOps_: vector of operations acting on whereClause_
  // where_: a boolean flag to determine the existence of a where clause
  class Impl;
  std::unique_ptr<Impl> impl_;
  
 public:
  
  SQLSelect(std::string, std::vector<std::string>, 
            std::vector<std::tuple< std::string, std::unique_ptr<Entry>> >, 
            std::vector<std::string>, 
            bool);
  bool isWhere();
};

#endif
