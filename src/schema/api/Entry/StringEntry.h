#ifndef LOODB_STRINGENTRY_H
#define LOODB_STRINGENTRY_H

#include "Entry.h"
#include "EntryType.h"
#include <memory>
#include <string>

class StringEntry : public Entry {

    // Private members of StringEntry
    struct StringEntryImpl {
      EntryType type_;
      std::string val_;
    };

    // pImpl for Entry
    std::unique_ptr<StringEntryImpl> impl_;

  public:

    // Constructor
    StringEntry(EntryType, std::string);

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

#endif // LOODB_STRINGENTRY_H
