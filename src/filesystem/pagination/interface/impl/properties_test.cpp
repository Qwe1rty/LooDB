#include <iostream>
#include "../api/PageCodec.h"
#include "../../page/api/PropertiesPage.h"
#include "../api/Pager.h"


int main() {

  std::unique_ptr<Page> p = std::make_unique<PropertiesPage>(EntryType::TEXT, "col", "primary key");

  Pager pager{"chicken"};

  auto index = pager.append(p);
  const auto pp = pager.fetch<PropertiesPage>(index);

  std::cout << pp->type_ << std::endl;
  std::cout << pp->column_ << std::endl;
  std::cout << pp->restrictions_ << std::endl;
}
