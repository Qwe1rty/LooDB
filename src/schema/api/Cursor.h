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

        // Paths for row and data files
        std::string rowPath_;
        std::string dataPath_;

        // Pager for row and data files
        std::unique_ptr<Pager> row_;
        std::unique_ptr<Pager> data_;

        // Page index
        uint32_t page_index_;

        // Constructor
        // Takes in path to row and bool loc
        // pageIndex == 0 -> start, pageIndex == -1 -> end
        // Otherwise, use uint32_t(pageIndex)
        Impl(std::string rowPath, std::string dataPath, int pageIndex);
    };

    // pImpl for Cursor
    std::unique_ptr<Impl> impl_;

  public:

    // Constructor
    // Takes in path to row and bool loc
    // pageIndex == 0 -> start, pageIndex == -1 -> end
    // Otherwise, use uint32_t(pageIndex)
    Cursor(std::string rowPath, std::string dataPath, int pageIndex);

    // Check if this is equal to other
    bool operator!=(const Cursor& other) const;

    // Increment cursor
    Cursor& operator++();

    // Dereference and return a Page pointer
    std::vector<std::unique_ptr<Entry>> operator*() const;

};

#endif // LOODB_CURSOR_H