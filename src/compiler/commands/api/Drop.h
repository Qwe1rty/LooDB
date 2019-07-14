#ifndef LOODB_COMDROP_H
#define LOODB_COMDROP_H

#include "Command.h"


class COMDrop : public Command {
 
  bool isValid() const override;
  void execute() override;

 public:
  
  COMDrop(std::string);
  ~ COMDrop();

};

#endif