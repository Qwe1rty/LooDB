#include "../api/Table.h"
#include "../api/Cursor.h"
#include "../api/Column/Column.h"
#include "../api/Entry/Entry.h"
#include "../api/Entry/EntryType.h"
#include "../api/Entry/NullEntry.h"
#include "../api/Entry/IntEntry.h"
#include "../api/Entry/StringEntry.h"
#include "../api/Entry/EntryCodec.h"
#include "../../filesystem/pagination/interface/api/Pager.h"
#include "../../filesystem/pagination/page/api/EntryPage.h"
#include "../../filesystem/pagination/page/api/BPTreeLeafPage.h"
#include "../../filesystem/pagination/page/api/PropertiesPage.h"
#include <sys/stat.h>
#include <dirent.h>
#include <memory>
#include <iostream>
#include <string.h>
#include <string>
#include <exception>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <tuple>
using namespace std;

Table::TableImpl::TableImpl(string s) : name_(s)  {
  struct stat sb;
  path_.append(name_);  // creates path ./loo/{table_name}
  if (stat(path_.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
    // read in colums
    populateTable();
  } else {
    buildTable();
  }
}

Table::Table(string s) : impl_{make_unique<TableImpl>(s)} {}

void Table::TableImpl::populateTable(){
  // cerr << "Found table: " << name_ << endl;
  vector<string> col_files;
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
          // cerr << "- 0 - found file: " << data_file_<< endl;
        } else if ((input.find(row_ext_) != string::npos)
          && strcmp(input.substr(0, (input.length()-row_ext_.length())).c_str(), name_.c_str()) == 0) {
          row_file_ = input;
          // cerr << "- 1 - found file: " << row_file_ << endl;
        } else if ((input.find(prop_ext_) != string::npos)
          && strcmp(input.substr(0, (input.length()-prop_ext_.length())).c_str(), name_.c_str()) == 0) {
          prop_file_ = input;
          // cerr << "- 1 - found file: " << prop_file_ << endl;
        }else if (input.find(col_ext_) != string::npos) {
          // TODO: add columns based on this
          col_files.emplace_back(input.substr(0, (input.length()-col_ext_.length())));
          // cerr << "- 2 - found file: " << input.substr(0, (input.length()-col_ext_.length())) << endl;
        }
      }
    }
    if(strcmp(data_file_.c_str(), ".") == 0 
      || strcmp(row_file_.c_str(),".") == 0 
      || strcmp(prop_file_.c_str(),".") == 0 ) {
      throw domain_error("Invalid State with Default Files in Table " + name_);
    }
    closedir(pDIR);
  }

  populateHelper(col_files);
}

void Table::TableImpl::populateHelper(vector<string> & col) {
  // create prop path to read columns in
  string prop_path = path_;
  prop_path.append("/");
  prop_path.append(name_);
  prop_path.append(prop_ext_);
  Pager prop{prop_path};
  // cerr << "p: prop path: " << prop_path << endl;

  // create pager to data file
  string data_path = path_;
  data_path.append("/");
  data_path.append(name_);
  data_path.append(data_ext_);
  data_pager_ = std::make_unique<Pager>(data_path);
  // cerr << "p: data path: " << data_path << endl;
  
  if(col.size() != prop.size()) {
    cout << "Error: Columns have been corrupted when building from disk" << endl;
    return;
  }
  for(int i = 0; i < prop.size(); ++i) {
    const auto page = prop.fetch<PropertiesPage>(i);
    string col_path = path_;
    col_path.append("/");
    col_path.append(col.at(i));
    col_path.append(col_ext_);

    if(page->restrictions_ == "primary key") {
      pkey_column_ = col.at(i);
      columns_.insert({col.at(i), 
            make_unique<UniqueRestriction>(
              make_unique<NotNullRestriction>(
                make_unique<BaseColumn>(col_path,  page->type_ , *data_pager_)
              ))});
      // cerr << "p: primary key" << endl;
    } else if(page->restrictions_ == "not null") {
      columns_.insert({col.at(i), make_unique<NotNullRestriction>(
            make_unique<BaseColumn>(col_path,page->type_  , *data_pager_)
            )});
      // cerr << "p: not null" << endl;
    } else {
      columns_.insert({ col.at(i), make_unique<BaseColumn>(col_path, page->type_ , *data_pager_)});
      // cerr << "p: no mods" << endl;
    }
    columnsTypes_.insert({col.at(i), page->type_});
    columnsIndices_.insert({col.at(i), i});
    indexToColumn_.insert({ i, col.at(i)});
  }
  //// cerr << "Help build object representation " << (col.size() == prop.size()) << " " << prop_path<< endl;
}

void Table::TableImpl::buildTable() {
  // to be used by create table command
  // cerr << "Build table" << endl;
  // cerr << path_ << endl;

  string data_path = path_;
  string row_path = path_;
  string prop_path = path_;

  data_path.append("/");
  data_path.append(name_);
  data_path.append(data_ext_);

  row_path.append("/");
  row_path.append(name_);
  row_path.append(row_ext_);

  prop_path.append("/");
  prop_path.append(name_);
  prop_path.append(prop_ext_);

  // cerr << data_path << " - " << row_path << " - " << prop_path << endl;

  // create directory
  mkdir(path_.c_str(), 0777);
  // write file names using pager 
  Pager d{data_path}, r{row_path}, p{prop_path};
}

void Table::createColumns(std::vector<std::tuple<std::string, EntryType, std::string>>& c){
  // cerr << "insert columns" << endl;

  int propIndex = 0;
  // create pager to data file
  string data_path = impl_->path_;
  data_path.append("/");
  data_path.append(impl_->name_);
  data_path.append(impl_->data_ext_);
  impl_->data_pager_ = std::make_unique<Pager>(data_path);
  // cerr << "data path: " << data_path << endl;

  // create pager to data file
  string prop_path = impl_->path_;
  prop_path.append("/");
  prop_path.append(impl_->name_);
  prop_path.append(impl_->prop_ext_);
  Pager prop{prop_path};
  // cerr << "prop path: " << prop_path << endl;

  for(auto &col:c) {
    // path for each column
    string col_path = impl_->path_;
    col_path.append("/");
    col_path.append(get<0>(col));
    col_path.append(impl_->col_ext_);
 
    // create a column with respective entry type and modifications (decorations)
    if(get<2>(col) == "primary key") {
      impl_->pkey_column_ = get<0>(col);
       impl_->columns_.insert({get<0>(col), 
            make_unique<UniqueRestriction>(
              make_unique<NotNullRestriction>(
                make_unique<BaseColumn>(col_path, get<1>(col), *impl_->data_pager_)
              ))}); 
      // cerr << "primary key" << endl;
    } else if(get<2>(col) == "not null") {
       impl_->columns_.insert({get<0>(col), make_unique<NotNullRestriction>(
            make_unique<BaseColumn>(col_path, get<1>(col), *impl_->data_pager_)
            )});
      // cerr << "not null" << endl;
    }else {
       impl_->columns_.insert({ get<0>(col), make_unique<BaseColumn>(col_path, get<1>(col), *impl_->data_pager_)});
      // cerr << "no mods" << endl;
    }
    impl_->columnsTypes_.insert({get<0>(col), get<1>(col)});
    impl_->columnsIndices_.insert({get<0>(col), propIndex});
    impl_->indexToColumn_.insert({ propIndex, get<0>(col)});

    unique_ptr<Page> p = make_unique<PropertiesPage>(get<1>(col), get<0>(col), get<2>(col));
    auto index = prop.append(p);
    if (index != propIndex) {
      cout << "Error: Table initialization failed with column (" << get<0>(col) << ")" << endl;
      return;
    }
    ++propIndex;
    // cerr << "col path: " << col_path << endl;

  }
}

void Table::insertColumns(std::vector<std::unique_ptr<Entry>>& e) {

  try {
    checkInsertValid(e);
  }
  catch (const std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
    return;
  }

  string data_path = impl_->path_;
  string row_path = impl_->path_;

  data_path.append("/");
  data_path.append(impl_->name_);
  data_path.append(impl_->data_ext_);

  row_path.append("/");
  row_path.append(impl_->name_);
  row_path.append(impl_->row_ext_);

  Pager data_file{data_path};
  Pager row_file{row_path};

  const EntryCodec entry_codec{};

  // Create row page's entry index vector, and determine the location of where the row page will be entered
  std::vector<uint64_t> entry_indexes{};
  uint32_t row_index = row_file.size();

  // Record which column is the primary key, and eventually which page index it is
  uint32_t pkey_column = static_cast<uint32_t>(impl_->columnsIndices_.at(impl_->pkey_column_));
  uint32_t pkey_index{0};

  // Append the data entries and then pass the information to each column
  for (int i = 0; i < e.size(); ++i) {

    // Write entry and get its index
    const std::unique_ptr<Page> entry_page = std::make_unique<EntryPage>(
      entry_codec.encode(e.at(i)),
      0
    );
    uint32_t entry_index = data_file.append(std::move(entry_page));

    // Add the pair to the column
    Column& column = *impl_->columns_.at(impl_->indexToColumn_.at(i));
    column.write(entry_index, row_index);

    // Add the pair to the entry_indexes vector
    entry_indexes.emplace_back(entry_index);

    // If it's the primary key column, record the primary key's entry page index
    if (i == pkey_column) pkey_index = entry_index;
  }

  // Write back the modified row file
  row_file.write(
    row_index,
    std::make_unique<BPTreeLeafPage>(
      0, // Currently the right_ pointer is unused
      std::vector<CellBP>{CellBP{pkey_index, std::move(entry_indexes)}}
    )
  );

  // std::cerr << "Insert is successful" << std::endl;
}

void Table::checkInsertValid(std::vector<std::unique_ptr<Entry>>& e) {
  // Check correct number of values
  if (e.size() != this->impl_->columns_.size()) {
    throw std::invalid_argument(
      "Error: Column " + this->impl_->name_ + " expects "
      + std::to_string(this->impl_->columns_.size()) + " values."
    );
  }

  // Check that values are valid column entries
  for (int i = 0; i < this->impl_->columns_.size(); ++i) {
    std::string columnName = this->impl_->indexToColumn_[i];
    if (!this->impl_->columns_.at(columnName)->valid(*e[i])) {
      throw std::invalid_argument(
        "Error: Attempted inserted value is invalid for column " +
        columnName +
        ", does not meet column restrictions."
      );
    }
  }

  // std::// cerr << "insert values are valid" << std::endl;
}

void printSet(std::set<uint32_t>& set) {
  std::cerr << "Printing set:";
  for (auto it=set.begin(); it!=set.end(); ++it)
    std::cerr << ' ' << *it;
  std::cerr << '\n';
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
  std::set_intersection(set1.begin(), set1.end(),
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
    // std::// cerr << "leaf" << std::endl;
    // Get column name and entry
    const std::string& columnName = std::get<0>(root->expr_);
    const std::unique_ptr<Entry>& entry = std::get<1>(root->expr_);

    // Throw if column doesn't exist
    if (this->columns_.find(columnName) == this->columns_.end()) {
      throw std::invalid_argument("Error: Column " + columnName + " doesn't exist.");
    }

    // Throw if entry doesn't match column type
    if (entry->getType() != this->columnsTypes_.at(columnName)) {
      // Invariance: column is of type INTEGER or TEXT
      EntryType columnType = this->columnsTypes_.at(columnName);
      std::string type = columnType == EntryType::INTEGER ? "integer" : "text";
      throw std::invalid_argument("Error: Column " + columnName + " is of type " + type);
    }

    const std::unique_ptr<Column>& column = this->columns_.at(columnName);

    // Find entry in column
    auto iter = column->begin();//find(*entry);

    // While iter meets where condition, insert page index into indices
    while (*iter != *column->end() ) {
      // std::// cerr << static_cast<StringEntry&>(*((**iter).first)).getVal();
      // std::// cerr << " == ";
      // std::// cerr << static_cast<StringEntry&>(*entry).getVal();
      // std::// cerr << std::endl;
      if(*((**iter).first) == *entry) {
        indices.insert((**iter).second);
      }
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
  
  // Check if select *
  bool star = false;
  if (columns[0] == "*") {
    star = true;
  } else {
    // Check that columns exist
    for (std::string& column : columns) {
      if (this->columns_.find(column) == this->columns_.end()) {
        // Column doesn't exist, so print error and return
        std::cout << "Error: Column \"" << column << "\"";
        std::cout << " doesn't exist in " << this->name_ << std::endl;
        return;
      }
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
    // std::// cerr << "Printing table! (where rows)" << std::endl;
    for (auto it = pageIndices.begin(); it != pageIndices.end(); ++it) {
      auto cursor = this->find(*it);
      std::vector<std::unique_ptr<Entry>> row = std::move(*cursor);
      this->printRow(row, columns, star);
    }
  } else {
    // Print all rows
    // std::// cerr << "Printing table! (all rows)" << std::endl;
    for (auto it = this->begin(); it != this->end(); ++it) {
      std::vector<std::unique_ptr<Entry>> row = std::move(*it);
      this->printRow(row, columns, star);
    }
  }
}

// Print rows given select statement criteria
void Table::printColumns(std::vector<string>& columns, bool where,
                         unique_ptr<SQLSelect::WhereTree>& whereTree) {
  this->impl_->printColumns_(columns, where, whereTree);
}

void Table::TableImpl::printRow(std::vector<std::unique_ptr<Entry>>& row,
                                           std::vector<string>& columns, bool star) {
  // // std::// cerr << "printing row" << std::endl;
  
  EntryType entryType;
  if (star) { // Print all columns
    std::cout << "|";
    for (int i = 0; i < row.size(); ++i) {
      entryType = row.at(i)->getType();
      if (entryType == EntryType::NULL_) {
        std::cout << "null";
      } else if (entryType == EntryType::INTEGER) {
        std::cout << static_cast<IntEntry&>(*row.at(i)).getVal();
      } else if (entryType == EntryType::TEXT) {
        std::cout << static_cast<StringEntry&>(*row.at(i)).getVal();
      }
      std::cout << "|";
    }
  } else { // Print given columns
    std::cout << "|";
    for (int i = 0; i < columns.size(); ++i) {
      int columnIndex = this->columnsIndices_.at(columns.at(i));

      entryType = row.at(columnIndex)->getType();
      if (entryType == EntryType::NULL_) {
        std::cout << "null";
      } else if (entryType == EntryType::INTEGER) {
        std::cout << static_cast<IntEntry&>(*row.at(columnIndex)).getVal();
      } else if (entryType == EntryType::TEXT) {
        std::cout << static_cast<StringEntry&>(*row.at(columnIndex)).getVal();
      }
      std::cout << "|";
    }
  }

  std::cout << std::endl;
}

Cursor Table::TableImpl::begin() {
  std::string row_path = path_;
  row_path.append("/");
  row_path.append(row_file_);


  std::string data_path = path_;
  data_path.append("/");
  data_path.append(data_file_);

  // // std::// cerr << row_path << " " << data_path << std::endl;

  return Cursor(row_path, data_path, 0);
}

Cursor Table::TableImpl::end() {
  std::string row_path = path_;
  row_path.append("/");
  row_path.append(row_file_);


  std::string data_path = path_;
  data_path.append("/");
  data_path.append(data_file_);

  // // std::// cerr << row_path << " " << data_path << std::endl;

  return Cursor(row_path, data_path, -1);
}

Cursor Table::TableImpl::find(uint32_t pageIndex) {
  std::string row_path = path_;
  row_path.append("/");
  row_path.append(row_file_);


  std::string data_path = path_;
  data_path.append("/");
  data_path.append(data_file_);

  // // std::// cerr << row_path << " " << data_path << std::endl;

  int index = static_cast<int>(pageIndex);
  return Cursor(row_path, data_path, index);
}