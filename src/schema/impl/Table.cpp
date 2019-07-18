#include "../api/Table.h"
#include "../api/Cursor.h"
#include "../api/Column/Column.h"
#include "../api/Entry/Entry.h"
#include "../api/Entry/IntEntry.h"
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <exception>
#include <algorithm>
#include <iterator>
#include <set>
#include <tuple>

//#include "../../filesystem/pagination/interface/api/Pager.h"
using namespace std;

Table::TableImpl::TableImpl(string s) : name_(s)  {
  struct stat sb;
  path_.append(name_);  // creates path ./loo/{table_name}
  if (stat(path_.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
    // read in colums
    populateTable();
  }
}

Table::Table(string s) : impl_{make_unique<TableImpl>(s)} {}

void Table::TableImpl::populateTable(){
  cerr << "Found table: " << name_ << endl;

  DIR *pDIR;
  struct dirent *entry;
  struct stat sb;
  // this will assume that only table folders are stored in here
  if( pDIR = opendir(path_.c_str()) ){
    while(entry = readdir(pDIR)){
      string input = string(entry->d_name);
      if( strcmp(entry->d_name, ".")  != 0 && strcmp(entry->d_name, "..") != 0 ) {
        if ((input.find(data_ext_) != string::npos) 
        && strcmp(input.substr(0, (input.length()-data_ext_.length())).c_str(), name_.c_str()) == 0) {
          data_file_ = input;
          cerr << "- 0 - found file: " << data_file_<< endl;
        } else if ((input.find(row_ext_) != string::npos)
          && strcmp(input.substr(0, (input.length()-row_ext_.length())).c_str(), name_.c_str()) == 0) {
          row_file_ = input;
          cerr << "- 1 - found file: " << row_file_ << endl;
        } else if (input.find(col_ext_) != string::npos) {
          // add columns based on this
          cerr << "- 2 - found file: " << entry->d_name << endl;
        }
      }
    }
    if(strcmp(data_file_.c_str(), ".") == 0 || strcmp(row_file_.c_str(),".") == 0 ) {
      throw domain_error("Invalid State with Default Files in Table " + name_);
    }
    closedir(pDIR);
  }
}

void Table::TableImpl::buildTable(){
  // to be used by create table command
}

std::set<uint32_t> Table::TableImpl::setUnion(std::set<uint32_t>& set1, std::set<uint32_t>& set2) {
  // Declare union set
  std::set<uint32_t> union_;

  // Get union of set1 and set2
  std::set_union(set1.begin(), set1.end(),
                 set2.begin(), set2.end(),
                 std::inserter(union_, union_.begin()));

  return union_;
}

std::set<uint32_t> Table::TableImpl::setIntersection(std::set<uint32_t>& set1, std::set<uint32_t>& set2) {
  // Declare intersection set
  std::set<uint32_t> intersection_;

  // Get union of set1 and set2
  std::set_union(set1.begin(), set1.end(),
                 set2.begin(), set2.end(),
                 std::inserter(intersection_, intersection_.begin()));

  return intersection_;
}

// Select helper for where clause
// Given a where tree, returns a ordered set of B+ page indices
// Page indices are in order so that rows print in same order as tablename.data
std::set<uint32_t> Table::TableImpl::whereHelper(std::unique_ptr<SQLSelect::WhereTree>& root) {
  // Declare indices set
  std::set<uint32_t> indices;

  // Is a where expression
  if (root->leaf_) {
    // Get column name and entry
    const std::string& columnName = std::get<0>(root->expr_);
    const std::unique_ptr<Entry>& entry = std::get<1>(root->expr_);

    // Throw if entry doesn't match column type
    if (entry->getType() != this->columnsTypes_[columnName]) {
      // Invariance: column is of type INTEGER or TEXT
      EntryType columnType = this->columnsTypes_[columnName];
      std::string type = columnType == EntryType::INTEGER ? "integer" : "text";
      throw std::invalid_argument("Error: Column " + columnName + " is of type " + type);
    }

    const std::unique_ptr<Column>& column = this->columns_[columnName];

    // Find entry in column
    auto iter = column->find(*entry);

    // While iter meets where condition, insert page index into indices
    while (*iter != *column->end() && *((**iter).first) == *entry) {
      std::cout << static_cast<IntEntry&>(*((**iter).first)).getVal();
      std::cout << " == ";
      std::cout << static_cast<IntEntry&>(*entry).getVal();
      std::cout << std::endl;
      indices.insert((**iter).second);
      ++(*iter);
    }

    return indices;
  }

  // Is a where operation

  // Get LHS where indices
  std::set<uint32_t> l_indices = whereHelper(root->where1_);
  // Get RHS where indices
  std::set<uint32_t> r_indices = whereHelper(root->where2_);

  // Get union or intersection of wheres
  if (root->op_ == "AND") {
    indices = setIntersection(l_indices, r_indices);
  } else { // "OR"
    indices = setUnion(l_indices, r_indices);
  }

  return indices;
}

// Given a where tree, returns a ordered set of B+ page indices
// Page indices are in order so that rows print in same order as tablename.data
std::set<uint32_t> Table::TableImpl::where(std::unique_ptr<SQLSelect::WhereTree>& root) {
  // Get page indices
  std::set<uint32_t> indices = whereHelper(root);
  // Return primary keys
  return indices;
}

// Print rows given select statement criteria
void Table::TableImpl::printColumns_(std::vector<string>& columns, bool where,
                                     unique_ptr<SQLSelect::WhereTree>& whereTree) {
  // Check that columns exist
  for (std::string& column : columns) {
    if (this->columns_.find(column) == this->columns_.end()) {
      // Column doesn't exist, so print error and return
      std::cout << "Error: Column \"" << column << "\"";
      std::cout << " doesn't exist in " << this->name_ << std::endl;
      return;
    }
  }

  // Get page indices from whereTree if where == true
  std::set<uint32_t> pageIndices;
  if (where) {
    try {
      // this->where() will throw if try to equate
      // a column to the wrong type
      pageIndices = this->where(whereTree);
    } catch (std::invalid_argument e) {
      // Catch invalid argument error, print and return
      std::cout << e.what() << std::endl;
      return;
    }
  }

  // Print columns using cursor
  // If where == true, print individual rows
  // Otherwise, print every row using cursor
  if (where) {
    std::cout << "where" << std::endl;
  } else {
    for (auto it = this->begin(); it != this->end(); ++it) {
      std::vector<std::unique_ptr<Entry>> row = std::move(*it);

      // Print given columns
      // EntryType entryType;
      // for (int i = 0; i < .size(); ++i) {
      //   entryType = row[i]->getType();
      //   if (entryType == EntryType::NULL_) {
      //     std::cout << "null" << std::endl;
      //   } else if (entryType == EntryType::INTEGER) {
      //     std::cout << static_cast<IntEntry&>(*row[i]).getVal() << std::endl;
      //   } else if (entryType == EntryType::TEXT) {
      //     std::cout << static_cast<IntEntry&>(*row[i]).getVal() << std::endl;
      //   }
      //   std::cout << 
      // }

      std::cout << "no where" << std::endl;
    }
  }
}

// Print rows given select statement criteria
void Table::printColumns(std::vector<string>& columns, bool where,
                         unique_ptr<SQLSelect::WhereTree>& whereTree) {
  this->impl_->printColumns_(columns, where, whereTree);
}

Cursor Table::TableImpl::begin() {
  std::string rowPath = this->data_file_ + this->data_ext_;
  std::string dataPath = this->row_file_ + this->row_ext_;
  return Cursor(rowPath, dataPath, false);
}

Cursor Table::TableImpl::end() {
  std::string rowPath = this->data_file_ + this->data_ext_;
  std::string dataPath = this->row_file_ + this->row_ext_;
  return Cursor(rowPath, dataPath, true);
}