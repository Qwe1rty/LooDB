#ifndef LOODB_COLUMN_H
#define LOODB_COLUMN_H

#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"
#include <memory>

class Column {

    // class Iterator;

    // Validate an Entry before writing to Column
    virtual bool valid_(const Entry& entry) const = 0;

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

    // NVI for valid_()
    bool valid(const Entry& entry);

    // NVI for read_()
    uint32_t read(uint32_t entry_index);

    // NVI for write_()
    void write(uint32_t entry_index, uint32_t row_index);

    // NVI for empty_()
    bool empty() const;

    // NVI for begin_()
    // BaseColumn::Iterator begin();

    // NVI for end_()
    // BaseColumn::Iterator end();

    // NVI for find_()
    // BaseColumn::Iterator find(Entry);

};

#endif // LOODB_COLUMN_H
