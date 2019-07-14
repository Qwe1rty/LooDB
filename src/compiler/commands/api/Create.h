#ifndef LOODB_COMCREATE_H
#define LOODB_COMCREATE_H

#include "Command.h"

class COMCreate : public Command {
 
  bool valid() const override;
  void execute() override;

 public:
  
  COMCreate(std::string);
  ~ COMCreate();
  bool isValid() const;
  void executeCommand();

};

#endif