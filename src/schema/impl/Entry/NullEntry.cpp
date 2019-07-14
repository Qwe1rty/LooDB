#include "../../api/Entry/NullEntry.h"
#include "../../api/Entry/EntryType.h"

// Constructor
NullEntry::NullEntry() : Entry(EntryType::NULL_) {}

// Override private less than operator
// First, checks if types are equivalent
// If so, return true
// Otherwise, return false
// Invariance: other will be of type
// NULL_, INTEGER or TEXT
bool NullEntry::less(const Entry& other) const {
  if (other.getType() == EntryType::NULL_) {
    return true;
  }
  return false;
}

// Override private less than or equals operator
// First, checks if types are equivalent
// If so, return true
// Otherwise, return false
// Invariance: other will be of type
// NULL_, INTEGER or TEXT
bool NullEntry::lesseq(const Entry& other) const {
  if (other.getType() == EntryType::NULL_) {
    return true;
  }
  return false;
}

// Override private greater than operator
// First, checks if types are equivalent
// If so, return true
// Otherwise, return false
// Invariance: other will be of type
// NULL_, INTEGER or TEXT
bool NullEntry::greater(const Entry& other) const {
  if (other.getType() == EntryType::NULL_) {
    return true;
  }
  return false;
}

// Override private greater than or equals operator
// First, checks if types are equivalent
// If so, return true
// Otherwise, return false
// Invariance: other will be of type
// NULL_, INTEGER or TEXT
bool NullEntry::greatereq(const Entry& other) const {
  if (other.getType() == EntryType::NULL_) {
    return true;
  }
  return false;
}

// Override private equals operator
// First, checks if types are equivalent
// If so, return true
// Otherwise, return false
// Invariance: other will be of type
// NULL_, INTEGER or TEXT
bool NullEntry::equal(const Entry& other) const {
  if (other.getType() == EntryType::NULL_) {
    return true;
  }
  return false;
}

// Override private not equals operator
// First, checks if types are equivalent
// If so, return true
// Otherwise, return false
// Invariance: other will be of type
// NULL_, INTEGER or TEXT
bool NullEntry::notequal(const Entry& other) const {
  if (other.getType() == EntryType::NULL_) {
    return true;
  }
  return false;
}