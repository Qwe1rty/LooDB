#ifndef LOODB_VM_H
#define LOODB_VM_H

#include "../../statements/api/Statement.h"
#include "../../../schema/api/Database.h"
#include <memory>

class VM {

 public:

  void execute(std::unique_ptr<SQLStatement>, Database &);
};

#endif
