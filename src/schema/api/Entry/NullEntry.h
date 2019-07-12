#ifndef LOODB_NULLENTRY_H
#define LOODB_NULLENTRY_H

#include "Entry.h"
#include "EntryType.h"
#include <memory>

class NullEntry : public Entry {

    // Private members of NullEntry
    struct NullEntryImpl {
      EntryType type_;
      const int val_ = 0;
    };

    // pImpl for Entry
    std::unique_ptr<NullEntryImpl> impl_;

  public:

    // Constructor
    NullEntry(EntryType, int);

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

#endif // LOODB_NULLENTRY_H
