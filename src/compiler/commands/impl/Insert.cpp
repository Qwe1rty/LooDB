#include "../api/Insert.h"

COMInsert::COMInsert(std::string t) : Command(t) {}

COMInsert::~COMInsert() = default;

bool COMInsert::valid() const {
  // determine validity
  return false;
}

void COMInsert::execute() {
   // code to create a table
}

bool COMInsert::isValid() const {
  return valid();
}

void COMInsert::executeCommand() {
  execute();
}