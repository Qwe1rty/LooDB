#ifndef LOODB_TABLE_H
#define LOODB_TABLE_H

#include "Column/Column.h"
#include "Column/BaseColumn.h"
#include "Column/ColumnRestriction.h"
#include "Column/NotNullRestriction.h"
#include "Column/UniqueRestriction.h"
#include "Cursor.h"
#include "Column/Column.h"
#include "Entry/Entry.h"
#include "Entry/EntryType.h"
#include "../../interpreter/statements/api/Select.h"
#include "../../filesystem/pagination/page/api/PropertiesPage.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <set>

class Table {
  // Private members of Table
  struct TableImpl {
      // Paths and file extensions
      std::string path_ = "./loo/";
      const std::string data_ext_ = ".data";
      const std::string col_ext_ = ".col";
      const std::string row_ext_ = ".row";
      const std::string prop_ext_ = ".prop";

      // Private variables
      std::string name_;
      std::unordered_map<std::string, std::unique_ptr<Column>> columns_;
      std::unordered_map<std::string, EntryType> columnsTypes_;
      std::unordered_map<std::string, int> columnsIndices_;
      std::unordered_map<int, std::string> indexToColumn_;
      std::string pkey_column_;
      std::string data_file_ = ".";
      std::string row_file_ = ".";
      std::string prop_file_ = ".";
      std::unique_ptr<Pager> data_pager_;

      // Constructor
      TableImpl(std::string);

      // Populate table with existing ones in the directory
      void populateTable();
      void populateHelper(std::vector<std::string> &);
      // Build table from command (create table ...)
      void buildTable();
      // Print tables given select criteria
      void printColumns_(std::vector<string>& columns, bool where,
                         unique_ptr<SQLSelect::WhereTree>& whereTree);

      // Select helper for where clause
      // Given a where tree, returns a ordered set of B+ page indices
      // Page indices are in order so that rows print in same order as tablename.data
      std::set<uint32_t> where(std::unique_ptr<SQLSelect::WhereTree>& root);

      // Begin and end for Cursor
      Cursor begin();
      Cursor end();
      Cursor find(uint32_t pageIndex);

    private:

      // Helper functions for where()
      std::set<uint32_t> whereHelper(std::unique_ptr<SQLSelect::WhereTree>& root);
      std::set<uint32_t> setUnion(std::set<uint32_t>& set1, std::set<uint32_t>& set2);
      std::set<uint32_t> setIntersection(std::set<uint32_t>& set1, std::set<uint32_t>& set2);

      // Helper function for printColumns_()
      void printRow(std::vector<std::unique_ptr<Entry>>& row,
                    std::vector<string>& columns, bool star);
  };

  // pImpl for Table
  std::unique_ptr<TableImpl> impl_;

 public:

  // Constructor
  Table(std::string);

  // Create Column
  void createColumns(std::vector<std::tuple<std::string, EntryType, std::string>>&);

  // Insert row into Columns
  void insertColumns(std::vector<std::unique_ptr<Entry>>& e);

  // Check if inserting row is valid
  void checkInsertValid(std::vector<std::unique_ptr<Entry>>& e);

  // Print rows given select statement criteria
  // Prints nothing if table is empty
  // Prints error if where clauses don't match column type
  void printColumns(std::vector<string>& columns, bool where,
                    unique_ptr<SQLSelect::WhereTree>& whereTree);

};

#endif // LOODB_TABLE_H
