#ifndef LOODB_ENTRY_H
#define LOODB_ENTRY_H

#include "EntryType.h"
#include <memory>

class Entry {

    // Private members of Entry
    struct EntryImpl {
      EntryType type_;
    };

    // pImpl for Entry
    std::unique_ptr<EntryImpl> impl_;

  public:

    // Constructor
    Entry(EntryType);

    // Overload less than operator
    virtual bool operator<(const Entry&) = 0;

    // Overload less than or equals operator
    virtual bool operator<=(const Entry&) = 0;

    // Overload greater than operator
    virtual bool operator>(const Entry&) = 0;

    // Overload greater than or equals operator
    virtual bool operator>=(const Entry&) = 0;

    // Overload equals operator
    virtual bool operator==(const Entry&) = 0;

    // Overload not equals operator
    virtual bool operator!=(const Entry&) = 0;

};

#endif // LOODB_ENTRY_H
