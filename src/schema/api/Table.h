#ifndef LOODB_TABLE_H
#define LOODB_TABLE_H

//#include "Column/Column.h"
//#include "Cursor.h"
#include "Entry/Entry.h"
#include <memory>
#include <string>
#include <map>

class Table {

    // Private members of Table
    struct TableImpl {
      std::string name_;
      std::map<std::string, int> columns_; // replace int with columns
      std::string pkey_column_;
      TableImpl(std::string);
    };

    // pImpl for Table
    std::unique_ptr<TableImpl> impl_;

  public:

    // Constructor
    Table(std::string);

    // Return a Cursor to row at Entry in table column
    //Cursor find(std::string, Entry);

    // Return a Cursor to the beginning of table
    //Cursor begin();

    // Return a Cursor to the end of table
    //Cursor end();

};

#endif // LOODB_TABLE_H
