#ifndef LOODB_COMMAD_H
#define LOODB_COMMAD_H

#include <string>
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
