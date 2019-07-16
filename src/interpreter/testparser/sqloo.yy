%skeleton "lalr1.cc" /* -*- C++ -*- */
%require  "3.0"
%defines

%define api.token.constructor
%define api.value.type variant

%code requires {
  #include "../statements/api/Statement.h"
  #include "../statements/api/Create.h"
  #include "../statements/api/Drop.h"
  #include "../statements/api/Insert.h"
  #include "../../schema/api/Entry/Entry.h"
  #include "../../schema/api/Entry/EntryType.h"
  #include "../../schema/api/Entry/NullEntry.h"
  #include "../../schema/api/Entry/IntEntry.h"
  #include "../../schema/api/Entry/StringEntry.h"
  #include <iostream>
  #include <string>
  #include <tuple>
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
  TABLE "table"
  INTEGER "integer"
  TEXT "text"
  PRIMARY_KEY "primary key"
  NOT_NULL "not null"
  INTO "into"
  VALUES "values"
  NULL_ "null"
;

%token <int> INT
%token <std::string> STRING

%%

%start sqloo;

sqloo:
  statement {
    p.result = std::move($1);
    YYACCEPT;
  };

%type <std::unique_ptr<SQLStatement>> statement;
statement:
  create {
    $$ = std::move($1);
  }
| drop {
    $$ = std::move($1);
  }
| insert {
    $$ = std::move($1);
  };

%type <std::unique_ptr<SQLStatement>> create;
create:
  CREATE TABLE STRING LPAREN columns RPAREN SEMI {
    $$ = std::make_unique<SQLCreate>(std::move($3), std::move($5));
  };

%type <std::unique_ptr<SQLStatement>> drop;
drop:
  DROP TABLE STRING SEMI {
    $$ = std::make_unique<SQLDrop>(std::move($3));
  };

%type <std::unique_ptr<SQLStatement>> insert;
insert:
  INSERT INTO STRING VALUES row SEMI {
    $$ = std::make_unique<SQLInsert>(std::move($3), std::move($5));
  };

%type <std::vector<std::tuple<std::string, EntryType, std::string>>> columns;
columns:
  columns COMMA column {
    $$.emplace_back(std::move($3));
  }
| column {
    $$.emplace_back(std::move($1));
  };

%type <std::tuple<std::string, EntryType, std::string>> column;
column:
  STRING INTEGER restrictions {
    $$ = std::make_tuple(std::move($1), EntryType::INTEGER, std::move($3));
  }
| STRING TEXT restrictions {
    $$ = std::make_tuple(std::move($1), EntryType::TEXT, std::move($3));
  };

%type <std::string> restrictions;
restrictions:
  %empty {
    $$ = "";
  }
| restriction {
    $$ = std::move($1);
  }
| restriction restriction {
    if ($1 != $2) {
      $$ = $1 + ", " + $2;
    } else {
      std::cerr << "Parse error: duplicate restriction" << std::endl;
      YYERROR;
    }
  };

%type <std::string> restriction;
restriction:
  PRIMARY_KEY {
    $$ = "primary key";
  }
| NOT_NULL {
    $$ = "not null";
  };

%type <std::vector<std::unique_ptr<Entry>>> row;
row:
  LPAREN entries RPAREN {
    $$ = std::move($2);
  };

%type <std::vector<std::unique_ptr<Entry>>> entries;
entries:
  entries COMMA entry {
    $$.emplace_back(std::move($3));
  }
| entry {
    $$.emplace_back(std::move($1));
  };

%type <std::unique_ptr<Entry>> entry;
entry:
  NULL_ {
    $$ = std::make_unique<NullEntry>();
  }
| INT {
    $$ = std::make_unique<IntEntry>(std::move($1));
  }
| text {
    $$ = std::make_unique<StringEntry>(std::move($1));
  };

%type <std::string> text;
text:
  DASH STRING DASH {
    $$ = std::move($2);
  };

%%

void yy::parser::error (const std::string& m) {
  std::cerr << "Parse error: " << m << std::endl;
}