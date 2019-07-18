#include "../api/Database.h"
#include <sys/stat.h>
#include<dirent.h>
#include <iostream>
#include<string.h>
#include <cstdlib> 
#include <algorithm>
using namespace std;

Database::DatabaseImpl::DatabaseImpl() {
  struct stat sb;
  if (stat(name_.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
    // read in tables
    helper();
  } else {
    // create db since the folder does not exist
    mkdir(name_.c_str(), 0777);
  }
}

Database::Database() : impl_{make_unique<DatabaseImpl>()} {}

void Database::DatabaseImpl::helper() {
  DIR *pDIR;
  struct dirent *entry;
  struct stat sb;
  // creates the ./loo path
  string path("./");
  path.append(name_);
  // this will assume that only table folders are stored in here
  if( pDIR = opendir(path.c_str()) ){
    while(entry = readdir(pDIR)){
      if( strcmp(entry->d_name, ".")  != 0 
        && strcmp(entry->d_name, "..") != 0 ) {
        tables_.insert({entry->d_name, Table(entry->d_name)});
      }
    }
    closedir(pDIR);
  }
}

void Database::drop_table(const SQLDrop& s) {
  if(impl_->tables_.find(s.table_name_) != impl_->tables_.end()) {
    struct stat sb;
    string path("./");
    path.append(impl_->name_);
    path.append(string("/"));
    path.append(s.table_name_);
    cerr << path << endl;
    if (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {
      if (system(NULL)) {
       string rm = string("rm -r ");
       rm.append(path);
       system(rm.c_str());
       impl_->tables_.erase(s.table_name_);
      } else {
       cerr << "Command processor doesn't exists" << endl; 
      }
      cerr << "Table Found " << endl;
    }
  } else {
    cout << "Error: Table Not Found " << endl;
  }
}

// Create a table in database
void Database::create_table(const SQLCreate& s) {
  if(impl_->tables_.find(s.table_name_) != impl_->tables_.end()) {
    cout << "Error: Table Already Exists" << endl;
  } else {
    cerr << "Creating Table" << endl;

    struct stat sb;
    string path("./");
    path.append(impl_->name_);
    path.append(string("/"));
    path.append(s.table_name_);

    cerr << path << endl;
    bool valid = checkCreateValid(s.getColumns()); 
    if (valid) {
      impl_->tables_.insert({s.table_name_, Table(s.table_name_)});
      impl_->tables_.at(s.table_name_).createColumns(s.getColumns());
    }
    cerr << "# of columns " << s.getColumns().size() << endl;
    cerr << (valid ? "- is valid -" : "- is not valid-") << endl;
  }
}


bool Database::checkCreateValid(std::vector<std::tuple<std::string, EntryType, std::string>>& c) {
  vector<string> tempColumns;
  for(auto & col : c) {
    tempColumns.emplace_back(get<0>(col));
  }
  // remove repeated columns
  sort(tempColumns.begin(), tempColumns.end());
  tempColumns.erase(unique(tempColumns.begin(), tempColumns.end()), tempColumns.end());
  
  vector<string> tempPkeys, tempnNull;
  for(auto & col : c) {
    get<2>(col) == "primary key" ? tempPkeys.emplace_back(get<2>(col)) : tempnNull.emplace_back(get<2>(col));
    cerr << get<2>(col) << endl;
  }
  // remove repeated modification
  sort(tempPkeys.begin(), tempPkeys.end());
  tempPkeys.erase(unique(tempPkeys.begin(), tempPkeys.end()), tempPkeys.end());

  if (tempColumns.size() != c.size()) {
    cout << "Error: Columns need to be unique" << endl;
  }
  if ((tempPkeys.size() + tempnNull.size())  != c.size()) {
    cout << "Error: The primary key restriction can only be assigned to one column" << endl;
  }
  return (tempColumns.size() == c.size()) && ((tempPkeys.size() + tempnNull.size())  == c.size());
}

// Insert a row into a database table
void Database::insert(const SQLInsert& s) {
  if(impl_->tables_.find(s.table_name_) != impl_->tables_.end()) {
    cerr << "Table Exists" << endl;

    struct stat sb;
    string path("./");
    path.append(impl_->name_);
    path.append(string("/"));
    path.append(s.table_name_);

    cerr << path << endl;
    
    impl_->tables_.at(s.table_name_).insertColumns(s.getEntries());
  } else {
    cout << "Error: Table does not exist" << endl;
  }
}

void Database::select(const SQLSelect& s) {
  if(impl_->tables_.find(s.table_name_) != impl_->tables_.end()) {
    impl_->tables_.at(s.table_name_).printColumns(
      s.getColumns(),
      s.hasWhere(),
      s.getWhereTree()
    );
  } else {
    cout << "Error: Table does not exist" << endl;
  }
}
