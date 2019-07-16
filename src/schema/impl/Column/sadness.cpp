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
  std::cout << "ADSHADSADSKJ" << std::endl;
  col.write(0, 3);
  std::cout << "ADSHADSADSKJ" << std::endl;
  col.write(1, 4);
  std::cout << "ADSHADSADSKJ" << std::endl;
  col.write(2, 5);
  std::cout << "ADSHADSADSKJ" << std::endl;
}