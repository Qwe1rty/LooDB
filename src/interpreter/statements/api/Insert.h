#ifndef LOODB_SQLINSERT_H
#define LOODB_SQLINSERT_H

#include "Statement.h"
#include <vector>
#include <memory>
#include "../../../schema/api/Entry/Entry.h"

class SQLInsert : public SQLStatement {

    // Private pImpl for SQLInsert
    // Declare class so compiler knows Impl's size
    class Impl{
        // entries_: each row being a vector of entries
        std::vector<std::unique_ptr<Entry>> entries_;
      public:
        Impl(std::vector<std::unique_ptr<Entry>> e);
        std::vector<std::unique_ptr<Entry>>& entryGetter();
    };

    std::unique_ptr<Impl> impl_;

  public:

    SQLInsert(std::string table_name, std::vector<std::unique_ptr<Entry>>);

    std::vector<std::unique_ptr<Entry>>& getEntries() const;

};

#endif
