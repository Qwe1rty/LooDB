#include "../api/Select.h"

COMSelect::COMSelect(std::string t) : Command(t) {}

COMSelect::~COMSelect() = default;

bool COMSelect::valid() const {
  // determine validity
  return false;
}

void COMSelect::execute() {
   // code to create a table
}

bool COMSelect::isValid() const {
  return valid();
}

void COMSelect::executeCommand() {
  execute();
}