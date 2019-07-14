#include "../api/virtual_machine.h"
using namespace std;

class VM::Impl{
  // stmt_: pointer to a statement object
  unique_ptr<SQLStatement> stmt_;
 public:
  Impl(unique_ptr<SQLStatement> s) : stmt_(std::move(s)) {}
  ~ Impl();
};

VM::VM(unique_ptr<SQLStatement> s) : impl_{make_unique<Impl>(std::move(s))}  {}
