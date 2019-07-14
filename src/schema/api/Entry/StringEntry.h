#ifndef LOODB_STRINGENTRY_H
#define LOODB_STRINGENTRY_H

#include "Entry.h"
#include <string>

class StringEntry : public Entry {

    std::string val_;

    // Override private less than operator
    // First, checks if types are equivalent
    // If so, compare values
    // Otherwise, return false
    // Invariance: other will always be
    // of type TEXT or NULL_
    bool less(const Entry&) const override;

    // Override private less than or equals operator
    // First, checks if types are equivalent
    // If so, compare values
    // Otherwise, return false
    // Invariance: other will always be
    // of type TEXT or NULL_
    bool lesseq(const Entry&) const override;

    // Override private greater than operator
    // First, checks if types are equivalent
    // If so, compare values
    // Otherwise, return false
    // Invariance: other will always be
    // of type TEXT or NULL_
    bool greater(const Entry&) const override;

    // Override private greater than or equals operator
    // First, checks if types are equivalent
    // If so, compare values
    // Otherwise, return false
    // Invariance: other will always be
    // of type TEXT or NULL_
    bool greatereq(const Entry&) const override;

    // Override private equals operator
    // First, checks if types are equivalent
    // If so, compare values
    // Otherwise, return false
    // Invariance: other will always be
    // of type TEXT or NULL_
    bool equal(const Entry&) const override;

    // Override private not equals operator
    // First, checks if types are equivalent
    // If so, compare values
    // Otherwise, return false
    // Invariance: other will always be
    // of type TEXT or NULL_
    bool notequal(const Entry&) const override;

  public:

    // Constructor
    StringEntry(std::string);

};

#endif // LOODB_STRINGENTRY_H
