#ifndef LOODB_SQLSELECT_H
#define LOODB_SQLSELECT_H

#include "Statement.h"
#include "../../../schema/api/Entry/Entry.h"
#include <vector>


class SQLSelect : public SQLStatement {
  // columns_: vector of column names
  // whereClause__: a vector of columns names and their respective entries
  // whereOps_: vector of operations acting on whereClause_
  // isWhere_: a boolean flag to determine the existence of a where clause
  class Impl;
  std::unique_ptr<Impl> impl_;
  std::unique_ptr<Command> query() override;
 public:
  
  SQLSelect(std::string, std::vector<std::string>, std::vector<std::string, Entry>, std::vector<std::string>);
  ~ SQLSelect();
  bool isWhere();
  std::unique_ptr<Command> generateQuery();

};

#endif
