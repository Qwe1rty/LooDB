#include "../../api/Column/BaseColumn.h"
#include "../../api/Entry/IntEntry.h"
#include "../../api/Entry/EntryCodec.h"
#include "../../../filesystem/pagination/page/api/EntryPage.h"

#include <iostream>


int main() {

  const int NUMBER = 10;

  EntryCodec codec{};
  Pager data{"data.txt"};
  BaseColumn col{"toast.txt", EntryType::INTEGER, data};

  for (int i = 0; i < NUMBER; ++i) {

    std::unique_ptr<Entry> e = std::make_unique<IntEntry>('0' + i);
    std::unique_ptr<Page> ep = std::make_unique<EntryPage>(codec.encode(e), 0);
    data.append(ep);
  }

  for (int i = 0; i < NUMBER; ++i) {

    std::unique_ptr<Entry> pk = std::make_unique<IntEntry>('a' + i);
    std::unique_ptr<Page> pkp = std::make_unique<EntryPage>(codec.encode(pk), 0);
    data.append(pkp);
  }

  for (int i = 0; i < NUMBER; i++) {

    // Insert the element;
    std::cout << "Attempting insert of: " << i << ' ' << i + NUMBER << std::endl;
    col.write(i, i + NUMBER);
    std::cout << "Insertion complete with: " << i << ' ' << i + NUMBER << '\n' << std::endl;

    // Iterate through the whole tree
    int limit = 0; // incase of infinite loop
    for (auto pk = col.begin(); *pk != *col.end(); ++(*pk)) {
//      std::cout << "\nPrimary key: " << std::flush;
//      std::cout << **pk << ", next iteration: " << (*pk != *col.end());
      ++limit;
      if (limit >= NUMBER + 5) {
        std::cout << "INFINITE LOOP" << std::endl;
        break;
      }
    }
    std::cout << "\n\n" << std::endl;
  }
}