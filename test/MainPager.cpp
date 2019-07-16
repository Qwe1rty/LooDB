#include "../src/filesystem/pagination/interface/api/Pager.h"
#include "../src/filesystem/pagination/page/api/BPTreeHeaderPage.h"

#include <iostream>


int main() {

  Pager pager{"toast.txt"};

  std::unique_ptr<Page> page = std::make_unique<BPTreeHeaderPage>(124);

  pager.write(1, page);
  const auto read = pager.read(1);

  const auto* cast = dynamic_cast<BPTreeHeaderPage*>(read.get());

  std::cout << cast->type() << std::endl; // 0
  std::cout << cast->root_ << std::endl; // 124, or seen as a pipe character in the file

  std::cout << '\n';
  std::cout << pager.length() << std::endl;
  std::cout << pager.size() << std::endl;

  return 0;
}