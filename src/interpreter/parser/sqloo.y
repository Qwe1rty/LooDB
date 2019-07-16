%language "c++"

%code requires {
  #include "../schema/api/Entry/Entry.h"
  #include "../schema/api/Entry/StringEntry.h"
  #include <iostream>
  #include <string>
  #include <memory>
  using namespace std;

  // Declare stuff from Flex that Bison needs to know about:
  // extern int yylex();
  extern int yyparse();

  // Give Flex the prototype of yylex we want ...
  # define YY_DECL yy::parser::symbol_type yylex ()
  // ... and declare it for the parser's sake.
  YY_DECL;

  void yyerror(const char *s);
}

// define the constant-string tokens:
%token CREATE
%token DROP
%token INSERT
%token INTO
%token TABLE
%token VALUES
%token NULL__
%token END_OF_FILE 0

%define api.token.prefix {TOK_}
%token
  SEMI  ";"
  COMMA   ","
  LPAREN    "("
  RPAREN    ")"
  DASH   "'"
;

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  Initially (by default), yystype
// is merely a typedef of "int", but for non-trivial projects, tokens could
// be of any arbitrary data type.  So, to deal with that, the idea is to
// override yystype's default typedef to be a C union instead.  Unions can
// hold all of the types of tokens that Flex could return, and this this means
// we can return ints or floats or strings cleanly.  Bison implements this
// mechanism with the %union directive:
// %union {
//   int ival;
//   char * sval;
//   Entry * eval;
// }

// Define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the %union:
// %token <ival> INT
// %token <sval> STRING

%define api.token.constructor
%define api.value.type variant

// Define the types of terminals
%token <int> INT
%token <std::string> STRING

// Define the types of non terminals
%type <unique_ptr<Entry>> text

%%

%start sqloo;

sqloo:
  statements
  ;

statements:
  statements statement
  | statement
  ;

statement:
  create
  | drop
  | insert
  ;

create:
  CREATE TABLE STRING ';' {
    cout << "creating table " << $3 << endl;
  };

drop:
  DROP TABLE STRING ';' {
    cout << "dropping table " << $3 << endl;
  };

insert:
  INSERT INTO STRING VALUES rows ';' {
    cout << "inserting " << endl;
  };

rows:
  rows ',' row
  | row
  ;

row:
  '(' values ')'
  ;

values:
  values ',' value
  | value
  ;

value:
  NULL__
  | INT
  | text
  ;

text:
  '\'' STRING '\'' {
    $$ = std::make_unique<StringEntry>($2);
  };

%%

void yyerror(const char *s) {
  cout << "Parse error: " << s << endl;
}