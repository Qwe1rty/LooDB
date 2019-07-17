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
  #include "../statements/api/Select.h"
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
  END 0 "EOF"
  SEMI ";"
  COMMA ","
  LPAREN "("
  RPAREN ")"
  DASH "'"
  STAR "*"
  EQUAL "="

  TABLE "table"
  NULL_ "null"

  CREATE "create"
  INTEGER "integer"
  TEXT "text"
  PRIMARY_KEY "primary key"
  NOT_NULL "not null"

  DROP "drop"

  INSERT "insert"
  INTO "into"
  VALUES "values"

  SELECT "select"
  FROM "from"
  WHERE "where"
  AND "and"
  OR "or"
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
  }
| select {
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

%type <std::unique_ptr<SQLStatement>> select;
select:
  SELECT cols FROM STRING SEMI {
    $$ = std::make_unique<SQLSelect>(std::move($4), std::move($2), false, nullptr);
  }
| SELECT cols FROM STRING WHERE whereExpr SEMI {
    $$ = std::make_unique<SQLSelect>(std::move($4), std::move($2), true, std::move($6));
  };

%type <std::vector<std::tuple<std::string, EntryType, std::string>>> columns;
columns:
  columns COMMA column {
    $1.emplace_back(std::move($3));
    $$ = std::move($1);
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
    $1.emplace_back(std::move($3));
    $$ = std::move($1);
  }
| entry {
    $$.emplace_back(std::move($1));
  };

%type <std::vector<std::string>> cols;
cols:
  STAR {
    $$.emplace_back("*");
  }
| cols COMMA col {
    $1.emplace_back(std::move($3));
    $$ = std::move($1);
  }
| col {
    $$.emplace_back(std::move($1));
  };

%type <std::string> col;
col:
  STRING {
    $$ = std::move($1);
  };

%type<std::unique_ptr<SQLSelect::WhereTree>> whereExpr;
whereExpr:
  whereTerm {
    $$ = std::move($1);
  }
| whereExpr OR whereTerm{
    $$ = std::make_unique<SQLSelect::WhereTree>("OR", std::move($1), std::move($3));
  };

%type<std::unique_ptr<SQLSelect::WhereTree>> whereTerm;
whereTerm:
  whereFactor {
    $$ = std::move($1);
  }
| whereTerm AND whereFactor{
    $$ = std::make_unique<SQLSelect::WhereTree>("AND", std::move($1), std::move($3));
  };

%type<std::unique_ptr<SQLSelect::WhereTree>> whereFactor;
whereFactor:
  STRING EQUAL entry {
    // std::cout << $1 << "=" << $3->getType() << std::endl;
    $$ = std::make_unique<SQLSelect::WhereTree>(std::move($1), std::move($3));
  }
| LPAREN whereExpr RPAREN {
    $$ = std::move($2);
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