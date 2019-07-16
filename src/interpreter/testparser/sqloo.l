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

<<EOF>> return yy::parser::make_END();
";" return yy::parser::make_SEMI();
"," return yy::parser::make_COMMA();
"(" return yy::parser::make_LPAREN();
")" return yy::parser::make_RPAREN();
"'" return yy::parser::make_DASH();
"*" return yy::parser::make_STAR();
"=" return yy::parser::make_EQUAL();

"table" return yy::parser::make_TABLE();
"null" return yy::parser::make_NULL_();

"create" return yy::parser::make_CREATE();
"integer" return yy::parser::make_INTEGER();
"text" return yy::parser::make_TEXT();
"primary key" return yy::parser::make_PRIMARY_KEY();
"not null" return yy::parser::make_NOT_NULL();

"drop" return yy::parser::make_DROP();

"insert" return yy::parser::make_INSERT();
"into" return yy::parser::make_INTO();
"values" return yy::parser::make_VALUES();

"select" return yy::parser::make_SELECT();
"from" return yy::parser::make_FROM();
"where" return yy::parser::make_WHERE();
"and" return yy::parser::make_AND();
"or" return yy::parser::make_OR();

{int} return yy::parser::make_INT(std::atoi(yytext));
{string} return yy::parser::make_STRING(yytext);

%%