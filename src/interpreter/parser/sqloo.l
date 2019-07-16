%{
  #include "sqloo.tab.hh"
  #include <iostream>
  #include <string>
  using namespace std;
%}

%option noyywrap

%%

[ \t\n ] ;

";" return yy::parser::make_SEMI();

"," return yy::parser::make_COMMA();

"(" return yy::parser::make_LPAREN();

")" return yy::parser::make_RPAREN();

"'" return yy::parser::make_DASH();

create {
  return CREATE;
}

drop {
  return DROP;
}

insert {
  return INSERT;
}

into {
  return INTO;
}

table {
  return TABLE;
}

values {
  return VALUES;
}

null {
  return NULL__;
}

[0-9]+ {
  // yylval.ival = atoi(yytext);
  return INT;
}

[a-zA-Z0-9]+ {
  // must free sval in Bison
  // yylval.sval = strdup(yytext);
  return yy::parser::make_STRING(yytext);
}

%%