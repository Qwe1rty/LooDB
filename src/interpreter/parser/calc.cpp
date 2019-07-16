#include <iostream>
#include "Driver.h"

// int
// main (int argc, char *argv[])
// {
//   int res = 0;
//   Driver drv;
//   for (int i = 1; i < argc; ++i)
//     if (argv[i] == std::string ("-p"))
//       drv.trace_parsing = true;
//     else if (argv[i] == std::string ("-s"))
//       drv.trace_scanning = true;
//     else if (!drv.parse (argv[i]))
//       std::cout << drv.result << '\n';
//     else
//       res = 1;
//   return res;
// }

int main () {
  Driver drv;
  drv.parse ("hello");
  std::cout << drv.result << std::endl;
  std::cout << drv.variables["two"] << std::endl;
  std::cout << drv.variables["one"] << std::endl;
}