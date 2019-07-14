#ifndef LOODB_COMINSERT_H
#define LOODB_COMINSERT_H

#include "Command.h"

class COMInsert : public Command {
 
  bool isValid() const override;
  void execute() override;

 public:
  
  COMInsert(std::string);
  ~ COMInsert();

};

#endif