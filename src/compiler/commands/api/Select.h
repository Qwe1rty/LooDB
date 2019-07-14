#ifndef LOODB_COMSELECT_H
#define LOODB_COMSELECT_H

#include "Command.h"

class COMSelect : public Command {
 
  bool isValid() const override;
  void execute() override;

 public:
  
  COMSelect(std::string);
  ~ COMSelect();

};

#endif