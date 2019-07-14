#ifndef LOODB_COMSELECT_H
#define LOODB_COMSELECT_H

#include "Command.h"

class COMSelect : public Command {
 
  bool valid() const override;
  void execute() override;

 public:
  
  COMSelect(std::string);
  ~ COMSelect();
  bool isValid() const;
  void executeCommand();

};

#endif