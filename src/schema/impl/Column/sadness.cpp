#include "../../api/Column/BaseColumn.h"
#include "../../api/Entry/IntEntry.h"
#include "../../api/Entry/EntryCodec.h"
#include "../../../filesystem/pagination/page/api/EntryPage.h"

#include <iostream>


int main() {

  std::unique_ptr<Entry> e1 = std::make_unique<IntEntry>(123);
  std::unique_ptr<Entry> e2 = std::make_unique<IntEntry>(124);
  std::unique_ptr<Entry> e3 = std::make_unique<IntEntry>(125);

  std::unique_ptr<Entry> pk1 = std::make_unique<IntEntry>('0');
  std::unique_ptr<Entry> pk2 = std::make_unique<IntEntry>('1');
  std::unique_ptr<Entry> pk3 = std::make_unique<IntEntry>('2');

  EntryCodec codec{};
  std::unique_ptr<Page> ep1 = std::make_unique<EntryPage>(codec.encode(e1), 0);
  std::unique_ptr<Page> ep2 = std::make_unique<EntryPage>(codec.encode(e2), 0);
  std::unique_ptr<Page> ep3 = std::make_unique<EntryPage>(codec.encode(e3), 0);
  std::unique_ptr<Page> pkp1 = std::make_unique<EntryPage>(codec.encode(pk1), 0);
  std::unique_ptr<Page> pkp2 = std::make_unique<EntryPage>(codec.encode(pk2), 0);
  std::unique_ptr<Page> pkp3 = std::make_unique<EntryPage>(codec.encode(pk3), 0);

  Pager data{"data.txt"};
  data.append(ep1);
  data.append(ep2);
  data.append(ep3);
  data.append(pkp1);
  data.append(pkp2);
  data.append(pkp3);

  BaseColumn col{"toast.txt", EntryType::INTEGER, data};
  for (int i = 0; i < 3; i++) {

    std::cout << "Attempting insert of: " << i << ' ' << i + 3 << std::endl;
    col.write(i, i + 3);
    std::cout << "Insertion complete with: " << i << ' ' << i + 3 << '\n' << std::endl;

    int limit = 0;
    for (auto pk = col.begin(); *pk != *col.end(); pk->operator++()) {
      std::cout << "\nPrimary key: " << std::flush;
      std::cout << **pk << ", next iteration: " << (*pk != *col.end()) << std::endl;

      ++limit;
      if (limit >= 10) break;
    }
    std::cout << '\n' << std::endl;
  }
}