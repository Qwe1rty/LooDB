#ifndef LOODB_COMDROP_H
#define LOODB_COMDROP_H

#include "Command.h"


class COMDrop : public Command {
 
  bool valid() const override;
  void execute() override;

 public:
  
  COMDrop(std::string);
  ~ COMDrop();
  bool isValid() const;
  void executeCommand();

};

#endif