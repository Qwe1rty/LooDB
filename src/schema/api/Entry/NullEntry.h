#ifndef LOODB_NULLENTRY_H
#define LOODB_NULLENTRY_H

#include "Entry.h"

class NullEntry : public Entry {

    const int val_ = 0;

    // Override private less than operator
    // First, checks if types are equivalent
    // If so, return true
    // Otherwise, return false
    // Invariance: other will be of type
    // NULL_, INTEGER or TEXT
    bool less(const Entry&) const override;

    // Override private less than or equals operator
    // First, checks if types are equivalent
    // If so, return true
    // Otherwise, return false
    // Invariance: other will be of type
    // NULL_, INTEGER or TEXT
    bool lesseq(const Entry&) const override;

    // Override private greater than operator
    // First, checks if types are equivalent
    // If so, return true
    // Otherwise, return false
    // Invariance: other will be of type
    // NULL_, INTEGER or TEXT
    bool greater(const Entry&) const override;

    // Override private greater than or equals operator
    // First, checks if types are equivalent
    // If so, return true
    // Otherwise, return false
    // Invariance: other will be of type
    // NULL_, INTEGER or TEXT
    bool greatereq(const Entry&) const override;

    // Override private equals operator
    // First, checks if types are equivalent
    // If so, return true
    // Otherwise, return false
    // Invariance: other will be of type
    // NULL_, INTEGER or TEXT
    bool equal(const Entry&) const override;

    // Override private not equals operator
    // First, checks if types are equivalent
    // If so, return true
    // Otherwise, return false
    // Invariance: other will be of type
    // NULL_, INTEGER or TEXT
    bool notequal(const Entry&) const override;

  public:

    // Constructor
    NullEntry();

};

#endif // LOODB_NULLENTRY_H
