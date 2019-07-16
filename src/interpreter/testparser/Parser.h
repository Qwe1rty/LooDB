#ifndef LOODB_PARSER_H
#define LOODB_PARSER_H

#include "../statements/api/Statement.h"
#include <memory>
#include "sqloo.tab.hh"

// Give Flex the prototype of yylex we want
# define YY_DECL yy::parser::symbol_type yylex (Parser& p)
// and declare it for the parser's sake.
YY_DECL;

class Parser {
  public:
    Parser();

    std::unique_ptr<SQLStatement> result;

    int parse(const std::string& query);

    void begin();
    void end();
};

#endif // LOODB_PARSER_H