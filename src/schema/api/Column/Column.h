#ifndef LOODB_COLUMN_H
#define LOODB_COLUMN_H

#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"
#include <memory>

class Column {

    // class Iterator;

    // Validate an Entry before writing to Column
    virtual bool valid_(const Entry&) const = 0;

    // Retrieve the page index for the primary key associated with the entry
    virtual uint32_t read_(uint32_t entry_index) = 0;

    // Write to Column
    virtual void write_(uint32_t entry_index, uint32_t row_index) = 0;

    // Check if Column is empty
    virtual bool empty_() const = 0;

    // virtual BaseColumn::Iterator begin_() = 0;

    // virtual BaseColumn::Iterator end_() = 0;

    // virtual BaseColumn::Iterator find_(Entry) = 0;

  public:

    // Constructor
    Column( /* params */ );

    // NVI for valid_()
    bool valid(Entry);

    // NVI for read_()
    Page read(Entry);

    // NVI for write_()
    void write(Entry, Page);

    // NVI for empty_()
    bool empty();

    // NVI for begin_()
    // BaseColumn::Iterator begin();

    // NVI for end_()
    // BaseColumn::Iterator end();

    // NVI for find_()
    // BaseColumn::Iterator find(Entry);

};

#endif // LOODB_COLUMN_H
