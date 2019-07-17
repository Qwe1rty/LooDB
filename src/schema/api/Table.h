#ifndef LOODB_TABLE_H
#define LOODB_TABLE_H

//#include "Column/Column.h"
//#include "Column/BaseColumn.h"
#include "Cursor.h"
#include "Entry/Entry.h"
#include "Entry/EntryType.h"
#include <memory>
#include <string>
#include <map>
#include <vector>

class Table {
  // Private members of Table
  struct TableImpl {
    // paths and file extensions
    std::string path_ = "./loo/";
    const std::string data_ext_ = ".data";
    const std::string col_ext_ = ".col";
    const std::string row_ext_ = ".row";
    // our private variables
    std::string name_;
    std::map<std::string, int> columns_; // replace int with column class
    std::string pkey_column_;
    std::string data_file_ = ".";
    std::string row_file_ = ".";
    TableImpl(std::string);
    //populate table with existing ones in the directory
    void populateTable();
    // build table from command (create table ...)
    void buildTable();
  };

  // pImpl for Table
  std::unique_ptr<TableImpl> impl_;

 public:

  // Constructor
  Table(std::string);

  void createColumns(std::vector<std::tuple<std::string, EntryType, std::string>>);
  bool checkCreateValid(std::vector<std::tuple<std::string, EntryType, std::string>> c);

  void insertColumns(std::vector<std::unique_ptr<Entry>> e);
  bool checkInsertValid(std::vector<std::unique_ptr<Entry>> e);
  
  // Return a Cursor to row at Entry in table column
  //Cursor find(std::string, Entry);

  // Return a Cursor to the beginning of table
  //Cursor begin();

  // Return a Cursor to the end of table
  //Cursor end();

};

#endif // LOODB_TABLE_H
