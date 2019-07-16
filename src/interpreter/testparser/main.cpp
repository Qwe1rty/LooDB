#include <iostream>
#include "Parser.h"

int main () {
  Parser p;
  p.parse ("hello");
  
  std::cout << "Received statement of type (";
  std::cout << p.result->type_;
  std::cout << ") on table ";
  std::cout << p.result->table_name_;
  std::cout << std::endl;
}