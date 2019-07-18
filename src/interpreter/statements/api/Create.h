#ifndef LOODB_SQLCREATE_H
#define LOODB_SQLCREATE_H

#include "Statement.h"
#include "../../../schema/api/Entry/EntryType.h"
#include <vector>
#include <tuple>
#include <memory>

class SQLCreate : public SQLStatement {
  
  // Private members of SQLCreate
  class Impl{
    // columns_: vector of column names, their repective type and modifications
    std::vector<std::tuple<std::string, EntryType, std::string>> columns_;
  public:
    Impl(std::vector<std::tuple<std::string, EntryType, std::string>> c);
    std::vector<std::tuple<std::string, EntryType, std::string>>& columnGetter();
  };

  // pImpl for SQLCreate
  std::unique_ptr<Impl> impl_;

 public:
  
  // Constructor
  SQLCreate(std::string, std::vector<std::tuple<std::string, EntryType, std::string>>);

  std::vector<std::tuple<std::string, EntryType, std::string>>& getColumns() const;

};

#endif
