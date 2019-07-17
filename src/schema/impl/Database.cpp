#include "../api/Database.h"
#include <sys/stat.h>
#include<dirent.h>
#include <iostream>
#include<string.h>
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
