%skeleton "lalr1.cc" /* -*- C++ -*- */
%require  "3.0"
%defines

%define api.token.constructor
%define api.value.type variant

%code requires {
  #include "../statements/api/Statement.h"
  #include "../statements/api/Insert.h"
  #include "../statements/api/Drop.h"
  #include "../../schema/api/Entry/Entry.h"
  #include "../../schema/api/Entry/NullEntry.h"
  #include "../../schema/api/Entry/IntEntry.h"
  #include "../../schema/api/Entry/StringEntry.h"
  #include <iostream>
  #include <string>
  #include <memory>
  class Parser;
}

// The parsing context.
%param { Parser& p }

%code {
  #include "Parser.h"
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

%type <std::unique_ptr<SQLStatement>> drop;
drop:
  DROP TABLE STRING SEMI {
    std::cout << "dropping table " << $3 << std::endl;
    $$ = std::make_unique<SQLDrop>($3);
  };

%type <std::unique_ptr<SQLStatement>> insert;
insert:
  INSERT INTO STRING VALUES row SEMI {
    std::cout << "inserting " << std::endl;
    $$ = std::make_unique<SQLInsert>($3, std::move($5));
  };

%type <std::vector<std::unique_ptr<Entry>>> row;
row:
  LPAREN values RPAREN {
    $$ = std::move($2);
  };

%type <std::vector<std::unique_ptr<Entry>>> values;
values:
  values COMMA value {
    std::cout << "inserting " << $3->getType() << " into values" << std::endl;
    $$.emplace_back(std::move($3));
  }
| value {
    std::cout << "inserting " << $1->getType() << " into values" << std::endl;
    $$.emplace_back(std::move($1));
  };

%type <std::unique_ptr<Entry>> value;
value:
  NULL_ {
    $$ = std::make_unique<NullEntry>();
    std::cout << "value null: " << $$->getType() << std::endl;
  }
| INT {
    $$ = std::make_unique<IntEntry>($1);
    std::cout << "value int: " << $$->getType() << std::endl;
  }
| text {
    $$ = std::make_unique<StringEntry>($1);
    std::cout << "value text: " << $$->getType() << std::endl;
  };

%type <std::string> text;
text:
  DASH STRING DASH {
    std::cout << "text: " << $2 << std::endl;
    $$ = $2;
  };

%%

void yy::parser::error (const std::string& m) {
  std::cerr << "Parse error: " << m << std::endl;
}