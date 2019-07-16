#ifndef LOODB_PARSER_H
#define LOODB_PARSER_H

#include "../../statements/api/Statement.h"
#include <memory>

class Parser {
  
 public:

  static std::unique_ptr<SQLStatement> parse(std::string);
  
};


#endif
