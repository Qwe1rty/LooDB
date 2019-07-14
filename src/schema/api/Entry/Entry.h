#ifndef LOODB_ENTRY_H
#define LOODB_ENTRY_H

#include "EntryType.h"

class Entry {

    EntryType type_;

    // Virtual private less than operator
    virtual bool less(const Entry&) const = 0;

    // Virtual private less than or equals operator
    virtual bool lesseq(const Entry&) const = 0;

    // Virtual private greater than operator
    virtual bool greater(const Entry&) const = 0;

    // Virtual private greater than or equals operator
    virtual bool greatereq(const Entry&) const = 0;

    // Virtual private equals operator
    virtual bool equal(const Entry&) const = 0;

    // Virtual private not equals operator
    virtual bool notequal(const Entry&) const = 0;

  public:

    // Constructor
    Entry(EntryType);

    // Get EntryType
    EntryType getType() const;

    // Overload less than operator
    // Calls private virtual less()
    bool operator<(const Entry&) const;

    // Overload less than or equals operator
    // Calls private virtual lesseq()
    bool operator<=(const Entry&) const;

    // Overload greater than operator
    // Calls private virtual greater()
    bool operator>(const Entry&) const;

    // Overload greater than or equals operator
    // Calls private virtual greatereq()
    bool operator>=(const Entry&) const;

    // Overload equals operator
    // Calls private virtual equal()
    bool operator==(const Entry&) const;

    // Overload not equals operator
    // Calls private virtual notequal()
    bool operator!=(const Entry&) const;

};

#endif // LOODB_ENTRY_H
