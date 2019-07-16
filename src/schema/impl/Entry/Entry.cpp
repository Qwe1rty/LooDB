#include "../../api/Entry/Entry.h"
#include "../../api/Entry/EntryType.h"

Entry::Entry(EntryType type) : type_(type) {}

EntryType Entry::getType() const {
  return this->type_;
}

bool Entry::operator<(const Entry& other) const {
  return this->less(other);
}

bool Entry::operator<=(const Entry& other) const {
  return this->lesseq(other);
}

bool Entry::operator>(const Entry& other) const {
  return this->greater(other);
}

bool Entry::operator>=(const Entry& other) const {
  return this->greatereq(other);
}

bool Entry::operator==(const Entry& other) const {
  return this->equal(other);
}

bool Entry::operator!=(const Entry& other) const {
  return this->notequal(other);
}