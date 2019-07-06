#ifndef LOODB_BPTREENODEPAGE_H
#define LOODB_BPTREENODEPAGE_H

template <typename Entry>

class BPTreeNodePage : public Page {

 public:
  uint64_t right_;
  std::vector<Entry> value_;

  BPTreeInternalNode(uint64_t right, std::vector<Cell> node);
  ~ BPTreeInternalNode() {}
}

#endif

// more to come
