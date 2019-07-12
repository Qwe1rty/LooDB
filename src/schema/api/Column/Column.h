#ifndef LOODB_COLUMN_H
#define LOODB_COLUMN_H

#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"

class Column {

    // class Iterator;

    // Validate an Entry before writing to Column
    virtual bool valid_(Entry) = 0;

    // TODO: Figure out how read works
    virtual Page read_(Entry) = 0;

    // Write to Column
    virtual void write_(Entry, Page) = 0;

    // Check if Column is empty
    virtual bool empty_() = 0;

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
