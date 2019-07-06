#ifndef LOODB_DATABASEHEADERPAGE_H
#define LOODB_DATABASEHEADERPAGE_H

class DatabaseHeaderPage : public Page {
// columns_: stores the page numbers of header pages belonging to BTrees (columns)
// bp_header_: has the page number of our B+Tree's header page

 public:
  std::vector<uint64_t> columns_;
  uint64_t bp_header_;

  DatabaseHeaderPage(std::vector<uint64_t> c, uint64_t bp) :
	 columns_{c}, bp_header_{bp} {}
  ~ DatabaseHeaderPage() override {}

}	

#endif
