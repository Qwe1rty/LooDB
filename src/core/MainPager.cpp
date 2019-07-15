#include "../filesystem/pagination/interface/api/Pager.h"
#include "../filesystem/pagination/page/api/BPTreeHeaderPage.h"

#include <iostream>


int main() {

  Pager pager{"toast"};

  std::unique_ptr<Page> page = std::make_unique<BPTreeHeaderPage>(123);

  pager.write(0, page);
  const auto read = pager.read(0);

  const auto* cast = dynamic_cast<BPTreeHeaderPage*>(read.get());

  std::cout << cast->type() << std::endl;
  std::cout << cast->root_ << std::endl;

  return 0;
}