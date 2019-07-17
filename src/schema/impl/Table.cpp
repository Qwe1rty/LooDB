#include "../api/Table.h"
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <exception>
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