#ifndef LOODB_CELLBP_H
#define LOODB_CELLBP_H

#include <cstdint>
#include <vector>


class CellBP {

  public:

    // key_: The page number referring to the primary key (index)
    // values_: The page numbers of the items stored in the row corresponding to our key
    uint64_t key_;
    std::vector<uint64_t> values_;

    CellBP(uint64_t, std::vector<uint64_t>);
};

#endif
