#include "Parser.h"
#include "sqloo.tab.hh"

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

Parser::Parser() {}

int Parser::parse(const std::string& query) {
  yy::parser parse (*this);

  YY_BUFFER_STATE buffer = yy_scan_string(query.c_str());
  int res = parse.parse();
  yy_delete_buffer(buffer);

  return res;
}