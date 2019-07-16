#ifndef LOODB_SQLINSERT_H
#define LOODB_SQLINSERT_H

#include "Statement.h"
#include <vector>
#include <memory>
#include "../../../schema/api/Entry/Entry.h"

class SQLInsert : public SQLStatement {
  // entries_: each row being a vector of entries
  class Impl;
  std::unique_ptr<Impl> impl_;

 public:

  SQLInsert(std::string table_name, std::vector<std::unique_ptr<Entry>>);
};

#endif
