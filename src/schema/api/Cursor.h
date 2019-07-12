#ifndef LOODB_CURSOR_H
#define LOODB_CURSOR_H

#include "Table.h"
#include "../../filesystem/pagination/page/api/Page.h"
#include <memory>
#include <string>
#include <map>

// Private members of Cursor
struct CursorImpl {
  // TODO: Figure out how Cursor is implemented
  // std::map<std::string, Column::Iterator> row_;
};

class Cursor {

    // Declare Table a friend of Cursor
    friend class Table;

    // pImpl for Cursor
    std::unique_ptr<CursorImpl> impl_;

  public:

    // Constructor
    Cursor( /* params */ );

    // Check if this is equal to other
    bool operator!=(const Cursor&);

    // Dereference and return a Page
    Page operator*();

    // Increment cursor
    Cursor& operator++();

};

#endif // LOODB_CURSOR_H