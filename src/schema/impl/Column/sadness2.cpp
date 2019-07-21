#include "../../api/Column/BaseColumn.h"
#include "../../api/Entry/IntEntry.h"
#include "../../api/Entry/EntryCodec.h"
#include "../../../filesystem/pagination/page/api/EntryPage.h"

#include <iostream>


int main() {

  const uint32_t DUPLICATES = 5;
  const uint32_t NUMBER = 50;

  EntryCodec codec{};
  Pager data{"sadness2.data"};

  for (uint32_t i = 0; i < NUMBER; ++i) {

    std::unique_ptr<Entry> e = std::make_unique<IntEntry>(200 + i);
    std::unique_ptr<Page> ep = std::make_unique<EntryPage>(codec.encode(e), 0);
    data.append(ep);
  }

  for (uint32_t i = 0; i < NUMBER; ++i) {

    std::unique_ptr<Entry> pk = std::make_unique<IntEntry>(10000 + i);
    std::unique_ptr<Page> pkp = std::make_unique<EntryPage>(codec.encode(pk), 0);
    data.append(pkp);
  }

  BaseColumn col{"sadness2.col", EntryType::INTEGER, data};
  for (uint32_t i = 0; i < NUMBER; i++) {
    // Insert the element
    std::cout << "Attempting insert of: " << i << ' ' << i + NUMBER << std::endl;
    col.write(i, i + NUMBER);
    std::cout << "Insertion complete with: " << i << ' ' << i + NUMBER << '\n' << std::endl;

    // Iterate through the whole tree
//    for (auto pk = col.begin(); *pk != *col.end(); ++(*pk)) {
//      std::cout << "\nPrimary key: " << std::flush;
//      std::cout << (**pk).second << ", next iteration: " << (*pk != *col.end());
//    }
  }

  for (int i = -5; i < static_cast<int>(NUMBER + 5); ++i) {
    std::unique_ptr<Entry> e = std::make_unique<IntEntry>(200 + i);

    for (const auto iter = col.find(*e); *iter != *col.end() && *((**iter).first) == *e; ++(*iter)) {
      const auto f = (**iter).second;
      std::cout << "at index i: "
                << i
                << ", found f"
                << f
                << ", equal to end()?: "
                << ((*iter == *col.end()) ? "true" : "false")
                << std::endl;
    }
  }

}