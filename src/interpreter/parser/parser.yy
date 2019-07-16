%skeleton "lalr1.cc" /* -*- C++ -*- */
%require  "3.0"
%defines

%define api.token.constructor
%define api.value.type variant
// %define parse.assert

%code requires {
  # include <string>
  class Driver;
}

// The parsing context.
%param { Driver& drv }

// %locations

// %define parse.trace
// %define parse.error verbose

%code {
# include "Driver.h"
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  ASSIGN  ":="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%type  <int> exp

%printer { yyo << $$; } <*>;

%%
%start unit;
unit: assignments exp  { drv.result = $2; };

assignments:
  %empty                 {}
| assignments assignment {};

assignment:
  "identifier" ":=" exp { drv.variables[$1] = $3; };

%left "+" "-";
%left "*" "/";
exp:
  "number"
| "identifier"  { $$ = drv.variables[$1]; }
| exp "+" exp   { $$ = $1 + $3; }
| exp "-" exp   { $$ = $1 - $3; }
| exp "*" exp   { $$ = $1 * $3; }
| exp "/" exp   { $$ = $1 / $3; }
| "(" exp ")"   { $$ = $2; }
%%

// void
// yy::parser::error (const location_type& l, const std::string& m)
// {
//   std::cerr << l << ": " << m << '\n';
// }

void
yy::parser::error (const std::string& m)
{
  std::cerr << "hello" << std::endl;
  std::cerr << m << std::endl;
}