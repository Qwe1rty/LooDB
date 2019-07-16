#include "sqloo.tab.hh"
#include <iostream>
#include <sstream>

extern FILE *yyin;
extern int yy_scan_string(const char *);

int main(int, char**) {
  // Open
  std::cout << "Opening loodb" << std::endl;

  // Create string stream
  std::stringstream ss;
  char c;

  // Accept white space
  std::cin >> std::noskipws;

  // Get query
  while (std::cin >> c) {
    if (c == ';') { // End of query
      ss << c;

      // std::cout << ss.str() << std::endl;

      // Parse the query
      yy_scan_string(ss.str().c_str());
      yyparse();

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