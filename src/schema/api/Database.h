#ifndef LOODB_DATABASE_H
#define LOODB_DATABASE_H

#include "Table.h"
#include "Entry/Entry.h"
#include <memory>
#include <string>
#include <map>
#include "../../interpreter/statements/api/Statement.h"

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
    void create_table(std::unique_ptr<SQLStatement>);

    // Drop a table in database
    void drop_table(std::unique_ptr<SQLStatement> );

    // Select rows from a table
    // Prints resulting object
    void select(std::unique_ptr<SQLStatement> );

    // Insert a row into a database table
    void insert(std::unique_ptr<SQLStatement>);

};

#endif // LOODB_DATABASE_H
