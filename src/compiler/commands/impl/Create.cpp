#include "../api/Create.h"

COMCreate::COMCreate(std::string t) : Command(t) {}

COMCreate::~COMCreate() = default;

bool COMCreate::valid() const {
  // determine validity
  return false;
}

void COMCreate::execute() {
   // code to create a table
}

bool COMCreate::isValid() const {
  return valid();
}

void COMCreate::executeCommand() {
  execute();
}
