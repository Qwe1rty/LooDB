#ifndef LOODB_CURSOR_H
#define LOODB_CURSOR_H

#include "Entry/Entry.h"
#include "../../filesystem/pagination/interface/api/Pager.h"
#include <memory>
#include <vector>

class Cursor {
  
    // Private members of Cursor
    class Impl {
      public:

        // Flag for start or end
        // loc == false -> start
        // loc == true -> end
        bool loc_;

        // Pager for B+tree and data files
        Pager& bptree_;
        Pager& data_;

        // Page index
        uint32_t page_index_;

        // Constructor
        // Takes in path to B+tree and bool loc
        // loc == false -> start, loc == true -> end
        Impl(Pager& bptree, Pager& data, bool loc);
    };

    // pImpl for Cursor
    std::unique_ptr<Impl> impl_;

  public:

    // Constructor
    // Takes in path to B+tree and bool loc
    // loc == false -> start, loc == true -> end
    Cursor(Pager& bptree, Pager& data, bool loc);

    // Check if this is equal to other
    bool operator!=(const Cursor& other) const;

    // Increment cursor
    Cursor& operator++();

    // Dereference and return a Page pointer
    std::vector<std::unique_ptr<Entry>> operator*() const;

};

#endif // LOODB_CURSOR_H