#ifndef LOODB_DATABASE_H
#define LOODB_DATABASE_H

#include "Table.h"
#include "Entry/Entry.h"
#include <memory>
#include <string>
#include <map>
#include "../../interpreter/statements/api/Statement.h"
#include "../../interpreter/statements/api/Create.h"
#include "../../interpreter/statements/api/Insert.h"
#include "../../interpreter/statements/api/Select.h"
#include "../../interpreter/statements/api/Drop.h"

class Database {

    // Private members of Database
    struct DatabaseImpl {
      std::string name_ = "loo";
      std::map<std::string, Table> tables_;
      DatabaseImpl();
      void helper();
    };
      
    // pImpl for Database
    std::unique_ptr<DatabaseImpl> impl_;

  public:
   
    Database();

    // Create a table in database
    void create_table(const SQLCreate&);
    bool checkCreateValid(std::vector<std::tuple<std::string, EntryType, std::string>>& c);

    // Drop a table in database
    void drop_table(const SQLDrop& s);

    // Select rows from a table
    // Prints resulting object
    void select(const SQLSelect& s);

    // Insert a row into a database table
    void insert(const SQLInsert& s);

};

#endif // LOODB_DATABASE_H
