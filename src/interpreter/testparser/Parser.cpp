#include "Parser.h"
#include "sqloo.tab.hh"

Parser::Parser() {}

int Parser::parse(const std::string& query) {
  begin();

  yy::parser parse (*this);

  int res = parse.parse();

  end();

  return res;
}

void Parser::begin() {}
void Parser::end() {}