#include "../api/Database.h"
#include <sys/stat.h>
#include<dirent.h>
#include <iostream>
#include<string.h>
#include <cstdlib> 
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
    cerr << "Table Not Found " << endl;
  }
}

// Create a table in database
void Database::create_table(const SQLCreate& s) {
  if(impl_->tables_.find(s.table_name_) != impl_->tables_.end()) {
    cerr << "Table Already Exists" << endl;
  } else {
    cerr << "Creating Table" << endl;

    struct stat sb;
    string path("./");
    path.append(impl_->name_);
    path.append(string("/"));
    path.append(s.table_name_);

    cerr << path << endl;

    // create db since the folder does not exist
    impl_->tables_.insert({s.table_name_, Table(s.table_name_)});
    cerr << s.getColumns().size() << endl;
    impl_->tables_.at(s.table_name_.c_str()).createColumns(s.getColumns());
    // -- bool valid = impl_->tables_.at(s.table_name_.c_str()).checkCreateValid(s.getColumns());
   // cout << !valid << endl;
    //impl_->tables_.find(s->table_name_).insert(s->columns_);
  }
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
    
    //bool valid = impl_->tables_.at(s.table_name_.c_str()).checkInsertValid(s.getEntries());
    //impl_->tables_.at(s.table_name_.c_str()).createColumns(s.getEntries());
  } else {
    cerr << "Table does not exist" << endl;
  }
}