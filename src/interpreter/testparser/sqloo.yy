%skeleton "lalr1.cc" /* -*- C++ -*- */
%require  "3.0"
%defines

%define api.token.constructor
%define api.value.type variant

%code requires {
  #include <iostream>
  #include <string>
  class Parser;
}

// The parsing context.
%param { Parser& p }

%code {
# include "Parser.h"
}

%define api.token.prefix {TOK_}
%token
  END  0  "EOF"
  SEMI  ";"
  COMMA   ","
  LPAREN    "("
  RPAREN    ")"
  DASH   "'"
  CREATE "create"
  DROP "drop"
  INSERT "insert"
  INTO "into"
  TABLE "table"
  VALUES "values"
  NULL_ "null"
;

%token <int> INT
%token <std::string> STRING

%printer { yyo << $$; } <*>;

%%

%start sqloo;

sqloo:
  statements {};

statements:
  statements statement {}
| statement {};

statement:
  create {}
| drop {}
| insert {};

create:
  CREATE TABLE STRING SEMI {
    std::cout << "creating table " << $3 << std::endl;
  };

drop:
  DROP TABLE STRING SEMI {
    std::cout << "dropping table " << $3 << std::endl;
  };

insert:
  INSERT INTO STRING VALUES rows SEMI {
    std::cout << "inserting " << std::endl;
  };

rows:
  rows COMMA row {}
| row {};

row:
  LPAREN values RPAREN {};

values:
  values COMMA value {}
| value {};

value:
  NULL_ {}
| INT {}
| text {};

text:
  DASH STRING DASH {
    std::cout << "StringEntry: " << $2 << std::endl;
  };

%%

void yy::parser::error (const std::string& m) {
  std::cerr << "Parse error: " << m << std::endl;
}