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
    Entry( /* params */ );

    // Overload less than operator
    bool operator<(const Entry&);

    // Overload less than or equals operator
    bool operator<=(const Entry&);

    // Overload greater than operator
    bool operator>(const Entry&);

    // Overload greater than or equals operator
    bool operator>=(const Entry&);

    // Overload equals operator
    bool operator==(const Entry&);

    // Overload not equals operator
    bool operator!=(const Entry&);

};

#endif //LOODB_ENTRY_H
