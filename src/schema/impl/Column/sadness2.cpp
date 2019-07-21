#include "../../api/Column/BaseColumn.h"
#include "../../api/Entry/IntEntry.h"
#include "../../api/Entry/EntryCodec.h"
#include "../../../filesystem/pagination/page/api/EntryPage.h"

#include <iostream>


int main() {

  const uint32_t DUPLICATES = 5;
  const uint32_t NUMBER = 50;

  // This creates a data file with:
  //   NUMBER amounts of unique entries, with NUMBER * DUPLICATE number of entries in total
  //   NUMBER * DUPLICATE amounts of unique primary keys, with NUMBER * DUPLICATE number of keys in total
  //
  // The purpose is to test the find(...) function, that should iterate through
  // DUPLICATE amount of primary keys with a particular associated entry


  EntryCodec codec{};
  Pager data{"sadness2.data"};

  for (uint32_t d = 0; d < DUPLICATES; ++d) {
    for (uint32_t i = 0; i < NUMBER; ++i) {

      std::unique_ptr<Entry> e = std::make_unique<IntEntry>(200 + i);
      std::unique_ptr<Page> ep = std::make_unique<EntryPage>(codec.encode(e), 0);
      std::cout << "entry at page: " << data.append(ep) << std::endl;
    }
  }

  for (uint32_t d = 0; d < DUPLICATES; ++d) {
    for (uint32_t i = 0; i < NUMBER; ++i) {

      std::unique_ptr<Entry> pk = std::make_unique<IntEntry>(10000 + i + (d * NUMBER));
      std::unique_ptr<Page> pkp = std::make_unique<EntryPage>(codec.encode(pk), 0);
      std::cout << "pk at page: " << data.append(pkp) << std::endl;
    }
  }


  // Insert all the entries in the .data into the BTree
  BaseColumn col{"sadness2.col", EntryType::INTEGER, data};

  for (uint32_t i = 0; i < NUMBER * DUPLICATES; ++i) {

    // Insert the element
    std::cout << "Attempting insert of: " << i << ' ' << i + (NUMBER *  DUPLICATES) << std::endl;
    col.write(i, i + (NUMBER * DUPLICATES));
    std::cout << "Insertion complete with: " << i << ' ' << i + (NUMBER * DUPLICATES) << '\n' << std::endl;
  }


  // Iterate through the whole tree
  for (auto pk = col.begin(); *pk != *col.end(); ++(*pk)) {
//    std::cout << "\nPrimary key: " << std::flush;
//    std::cout << (**pk).second << ", next iteration: " << (*pk != *col.end());
  }
  std::cout << "Whole tree has been iterated through\n" << std::endl;


  // Attempt to see if for every entry, the find(...) + iteration returns 5 entries
  for (int i = -5; i < static_cast<int>(NUMBER + 5); ++i) {

    std::unique_ptr<Entry> e = std::make_unique<IntEntry>(200 + i);

    for (const auto iter = col.find(*e); *((**iter).first) == *e; ++(*iter)) {

      const auto f = static_cast<IntEntry*>((**iter).first.get())->getVal();
      const auto s = (**iter).second;
      std::cout << "at index i: "
                << i
                << ", found key: "
                << f
                << ", at page: "
                << s
                << ", equal to end()?: "
                << ((*iter == *col.end()) ? "true" : "false")
                << std::endl;
    }
  }

}