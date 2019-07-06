#ifndef LOODB_BPTREEHEADERPAGE_H
#define LOODB_BPTREEHEADERPAGE_H

class BPTreeHeaderPage : public Page {
// tree_root_: has the page number of the root node of our B+ Tree

 public:
  uint64_t tree_root_;
  BPTreeHeaderPage(uint64_t root) : tree_root_{root} {}
  ~ BPTreeHeaderPage() override {}

}

#endif
