#ifndef LOODB_INTENTRY_H
#define LOODB_INTENTRY_H

#include "Entry.h"
#include "EntryType.h"
#include <memory>

class IntEntry : public Entry {

    // Private members of IntEntry
    struct IntEntryImpl {
      EntryType type_;
      int val_;
    };

    // pImpl for Entry
    std::unique_ptr<IntEntryImpl> impl_;

  public:

    // Constructor
    IntEntry(EntryType, int);

    // Overload less than operator
    bool operator<(const Entry&) override;

    // Overload less than or equals operator
    bool operator<=(const Entry&) override;

    // Overload greater than operator
    bool operator>(const Entry&) override;

    // Overload greater than or equals operator
    bool operator>=(const Entry&) override;

    // Overload equals operator
    bool operator==(const Entry&) override;

    // Overload not equals operator
    bool operator!=(const Entry&) override;

};

#endif // LOODB_INTENTRY_H
