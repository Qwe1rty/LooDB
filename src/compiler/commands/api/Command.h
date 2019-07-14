#ifndef LOODB_COMMAND_H
#define LOODB_COMMAND_H

class Command {

  virtual bool isValid() const = 0;
  virtual void execute() = 0;
  std::string table_;
 
 protected:

  Command(std::string);

 public:
  
  virtual ~Command();;
};

#endif
