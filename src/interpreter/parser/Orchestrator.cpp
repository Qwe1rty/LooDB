#include "Parser.h"
#include "../statements/api/Select.h"
#include "../statements/api/StatementType.h"
#include <iostream>
#include <sstream>
#include <memory>

int run() {
  // Open
  std::cout << "Opening loodb" << std::endl;

  // Create string stream
  std::stringstream ss;
  char c;

  // Create Parser
  Parser p;

  // Accept white space
  std::cin >> std::noskipws;

  // Get query
  while (std::cin >> c) {
    if (c == ';') { // End of query
      ss << c;

      // Parse the query
      int res = p.parse(ss.str());

      if (res == 0 && p.result) {
        std::cout << "Received statement of type (";
        std::cout << p.result->type_;
        std::cout << ") on table ";
        std::cout << p.result->table_name_;
        std::cout << std::endl;

        if (p.result->type_ == StatementType::stmtSelect) {
          if (static_cast<SQLSelect*>(p.result.get())->hasWhere()) {
            static_cast<SQLSelect*>(p.result.get())->printWhere();
          }
        }
      }

      // Clear ss
      ss.str(std::string()); // Faster than ss.str("")
      ss.clear();
    } else { // Keep building query
      if (c == '\n') {
        ss << ' ';
      } else {
        ss << c;
      }
    }
  }
  
  // Close
  std::cout << "Closing loodb" << std::endl;
}

int main () {
  run();
}