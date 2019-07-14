#include "../api/Drop.h"

COMDrop::COMDrop(std::string t) : Command(t) {}

COMDrop::~COMDrop() = default;

bool COMDrop::valid() const {
  // determine validity
  return false;
}

void COMDrop::execute() {
   // code to create a table
}

bool COMDrop::isValid() const {
  return valid();
}

void COMDrop::executeCommand() {
  execute();
}