#ifndef LOODB_BTREEHEADERPAGE_H
#define LOODB_BTREEHEADERPAGE_H

class BTreeHeaderPage : public Page {
// tree_root_: Has the page number of the root node in our BTree

 public:
  uint64_t tree_root_;
  BTreeHeaderPage(uint64_t root) : tree_root_{root} {}
  ~ BTreeHeaderPage() override {}

}

#endif
