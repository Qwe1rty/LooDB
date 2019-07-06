#ifndef LOODB_CELLBP_H
#define LOODB_CELLBP_H

template <typename Entry>

class CellBP {
// key_: A value, integer or string, representing a primary key
// values_: The page numbers of the items stored in the row corresponding to our key

 public:
  Entry key_;
  std::vector<uint64_t> values_;

  CellBP(Entry k, std::vector<uint64_t> v) : key_{k}, values_{v} {}
  ~ CellBP() {}

//more to come

}

#endif
