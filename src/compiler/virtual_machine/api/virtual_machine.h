#ifndef LOODB_VM_H
#define LOODB_VM_H

#include "../../statements/api/Statement.h"
#include <memory>

class VM {

  class Impl;
  std::unique_ptr<Impl> impl_;

 public:

  VM(std::unique_ptr<SQLStatement> );
  void execute();
};

#endif
