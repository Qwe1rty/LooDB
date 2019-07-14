#ifndef LOODB_COMINSERT_H
#define LOODB_COMINSERT_H

#include "Command.h"

class COMInsert : public Command {
 
  bool valid() const override;
  void execute() override;

 public:
  
  COMInsert(std::string);
  ~ COMInsert();
  bool isValid() const;
  void executeCommand();

};

#endif