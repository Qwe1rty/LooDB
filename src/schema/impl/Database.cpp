#include "../api/Database.h"
#include <sys/stat.h>
#include <iostream>
using namespace std;

Database::DatabaseImpl::DatabaseImpl() {
  struct stat sb;

  if (stat("loo", &sb) == 0 && S_ISDIR(sb.st_mode)) {
    cout << "Hi - loo is a directory" << endl; 
  } else {
    cout << "NO - loo is not a directory" << endl; 
  }
}

Database::Database() : impl_{make_unique<DatabaseImpl>()} {}

int main () {
  Database p;
  return 0;
}