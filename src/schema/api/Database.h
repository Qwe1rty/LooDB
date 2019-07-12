#ifndef LOODB_DATABASE_H
#define LOODB_DATABASE_H

#include "Table.h"
#include "Entry.h"
#include <memory>
#include <string>
#include <map>
#include <vector>

// Private members of Database
struct DatabaseImpl {
  std::string name_;
  std::map<std::string, Table> tables_;
};

class Database {

    // pImpl for Database
    std::unique_ptr<DatabaseImpl> impl_;

  public:

    // Constructor
    Database( /* params */ );

    // Create a table in database
    void create_table( /* params */ );

    // Drop a table in database
    void drop_table( /* params */ );

    // Select rows from a table
    // Returns a Result object
    // Result select( /* params */ );

    // Insert a row into a database table
    void insert(std::string, std::vector<Entry>);

};

#endif // LOODB_DATABASE_H
