#include "../../api/Entry/IntEntry.h"
#include "../../api/Entry/EntryType.h"

// Constructor
IntEntry::IntEntry(int val) : Entry(EntryType::INTEGER), val_(val) {}

// Override private less than operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type INTEGER or NULL_
bool IntEntry::less(const Entry& other) const {
  if (other.getType() == EntryType::INTEGER) {
    return val_ < static_cast<const IntEntry&>(other).val_;
  }
  return false;
}

// Override private less than or equals operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type INTEGER or NULL_
bool IntEntry::lesseq(const Entry& other) const {
  if (other.getType() == EntryType::INTEGER) {
    return val_ <= static_cast<const IntEntry&>(other).val_;
  }
  return false;
}

// Override private greater than operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type INTEGER or NULL_
bool IntEntry::greater(const Entry& other) const {
  if (other.getType() == EntryType::INTEGER) {
    return val_ > static_cast<const IntEntry&>(other).val_;
  }
  return false;
}

// Override private greater than or equals operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type INTEGER or NULL_
bool IntEntry::greatereq(const Entry& other) const {
  if (other.getType() == EntryType::INTEGER) {
    return val_ <= static_cast<const IntEntry&>(other).val_;
  }
  return false;
}

// Override private equals operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type INTEGER or NULL_
bool IntEntry::equal(const Entry& other) const {
  if (other.getType() == EntryType::INTEGER) {
    return val_ == static_cast<const IntEntry&>(other).val_;
  }
  return false;
}

// Override private not equals operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type INTEGER or NULL_
bool IntEntry::notequal(const Entry& other) const {
  if (other.getType() == EntryType::INTEGER) {
    return val_ != static_cast<const IntEntry&>(other).val_;
  }
  return false;
}