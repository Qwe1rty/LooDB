#ifndef LOODB_COMMAND_H
#define LOODB_COMMAND_H

class Command {

  virtual void execute() = 0;
 public:
  virtual ~Command() = default;
};

#endif
