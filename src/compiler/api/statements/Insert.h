#ifndef LOODB_SQLINSERT_H
#define LOODB_SQLINSERT_H

#include "Statement.h"
#include <vector>
#include "../../../schema/api/Entry/Entry.h"

class SQLInsert : public SQLStatement {
  // entries_: vector of rows to be entred; each row being a vector of entries
  class Impl;
  std::unique_ptr<Impl> impl_;
  std::unique_ptr<Command> query() const override;

 public:

  SQLInsert(std::string table_name, std::vector<std::vector<Entry>>);
  std::unique_ptr<Command> generateQuery() const;
};

#endif
