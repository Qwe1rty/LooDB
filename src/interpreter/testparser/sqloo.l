%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <cstring> // strerror
# include <string>
# include "Parser.h"
# include "sqloo.tab.hh"
%}

%option noyywrap batch

blank [ \t\r]
int [0-9]+
string [a-zA-Z][a-zA-Z_0-9]*

%%

{blank}+ ;

";" return yy::parser::make_SEMI();
"," return yy::parser::make_COMMA();
"(" return yy::parser::make_LPAREN();
")" return yy::parser::make_RPAREN();
"'" return yy::parser::make_DASH();

"create" return yy::parser::make_CREATE();
"drop" return yy::parser::make_DROP();
"insert" return yy::parser::make_INSERT();
"table" return yy::parser::make_TABLE();

"integer" return yy::parser::make_INTEGER();
"text" return yy::parser::make_TEXT();
"primary key" return yy::parser::make_PRIMARY_KEY();
"not null" return yy::parser::make_NOT_NULL();

"into" return yy::parser::make_INTO();
"values" return yy::parser::make_VALUES();

"null" return yy::parser::make_NULL_();
{int} return yy::parser::make_INT(std::atoi(yytext));
{string} return yy::parser::make_STRING(yytext);
<<EOF>> return yy::parser::make_END();

%%