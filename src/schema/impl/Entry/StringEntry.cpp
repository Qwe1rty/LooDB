#include "../../api/Entry/StringEntry.h"
#include "../../api/Entry/EntryType.h"
#include <string>

// Constructor
StringEntry::StringEntry(std::string val) : Entry(EntryType::TEXT), val_(val) {}

// Override private less than operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type TEXT or NULL_
bool StringEntry::less(const Entry& other) const {
  if (other.getType() == EntryType::TEXT) {
    return val_ < static_cast<const StringEntry&>(other).val_;
  }
  return false;
}

// Override private less than or equals operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type TEXT or NULL_
bool StringEntry::lesseq(const Entry& other) const {
  if (other.getType() == EntryType::TEXT) {
    return val_ <= static_cast<const StringEntry&>(other).val_;
  }
  return false;
}

// Override private greater than operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type TEXT or NULL_
bool StringEntry::greater(const Entry& other) const {
  if (other.getType() == EntryType::TEXT) {
    return val_ > static_cast<const StringEntry&>(other).val_;
  }
  return false;
}

// Override private greater than or equals operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type TEXT or NULL_
bool StringEntry::greatereq(const Entry& other) const {
  if (other.getType() == EntryType::TEXT) {
    return val_ <= static_cast<const StringEntry&>(other).val_;
  }
  return false;
}

// Override private equals operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type TEXT or NULL_
bool StringEntry::equal(const Entry& other) const {
  if (other.getType() == EntryType::TEXT) {
    return val_ == static_cast<const StringEntry&>(other).val_;
  }
  return false;
}

// Override private not equals operator
// First, checks if types are equivalent
// If so, compare values
// Otherwise, return false
// Invariance: other will always be
// of type TEXT or NULL_
bool StringEntry::notequal(const Entry& other) const {
  if (other.getType() == EntryType::TEXT) {
    return val_ != static_cast<const StringEntry&>(other).val_;
  }
  return false;
}