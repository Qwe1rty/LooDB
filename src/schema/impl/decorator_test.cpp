//#include "../api/Column/Column.h"
//#include "../api/Column/UniqueRestriction.h"
//#include "../api/Column/BaseColumn.h"
//#include "../api/Entry/EntryCodec.h"
//#include "../api/Entry/IntEntry.h"
//#include "../api/Entry/StringEntry.h"
//#include "../api/Entry/NullEntry.h"
//#include "../../filesystem/pagination/page/api/EntryPage.h"
//#include "../api/Column/NotNullRestriction.h"
//
//#include <memory>
//#include <iostream>
//
//
//int main() {
//
//  const uint32_t NUMBER = 15;
//
//  EntryCodec codec{};
//  Pager data{"data.txt"};
//
//  for (uint32_t i = 0; i < NUMBER; ++i) {
//    std::unique_ptr<Entry> e = std::make_unique<IntEntry>(200 + i);
//    std::unique_ptr<Page> ep = std::make_unique<EntryPage>(codec.encode(e), 0);
//    data.append(ep);
//  }
//  for (uint32_t i = 0; i < NUMBER; ++i) {
//    std::unique_ptr<Entry> pk = std::make_unique<IntEntry>(10000 + i);
//    std::unique_ptr<Page> pkp = std::make_unique<EntryPage>(codec.encode(pk), 0);
//    data.append(pkp);
//  }
//
//
//  std::unique_ptr<Column> not_null =
//    std::make_unique<NotNullRestriction>(
//      std::make_unique<BaseColumn>("not_null.col", EntryType::TEXT, data)
//    );
//
//  std::cout << not_null->valid(StringEntry("yay")) << std::endl; // 1
//  std::cout << not_null->valid(IntEntry(100)) << std::endl;      // 0
//  std::cout << not_null->valid(NullEntry()) << std::endl;        // 0
//  std::cout << std::endl;
//
//
//  std::unique_ptr<Column> primary =
//    std::make_unique<NotNullRestriction>(
//      std::make_unique<UniqueRestriction>(
//        std::make_unique<BaseColumn>("primary.col", EntryType::INTEGER, data)
//      )
//    );
//
//  for (uint32_t i = 0; i < NUMBER; ++i) primary->write(i, i + NUMBER);
//
//  std::cout << primary->valid(StringEntry("yay")) << std::endl; // 0
//  std::cout << primary->valid(IntEntry(100)) << std::endl;      // 1
//  std::cout << primary->valid(NullEntry()) << std::endl;        // 0
//  std::cout << std::endl;
//  std::cout << primary->valid(IntEntry(200)) << std::endl;      // 0
//  std::cout << primary->valid(IntEntry(204)) << std::endl;      // 0
//  std::cout << primary->valid(IntEntry(215)) << std::endl;      // 1
//  std::cout << std::endl;
//}
