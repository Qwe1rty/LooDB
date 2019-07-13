#ifndef LOODB_COMMAND_H
#define LOODB_COMMAND_H

class Command {

 public:
  virtual void execute() = 0;
  virtual ~Command() = default;
};

#endif
