#ifndef LOODB_PROPERTIESPAGE_H
#define LOODB_PROPERTIESPAGE_H

#include "Page.h"
#include "../../../../schema/api/Entry/EntryType.h"


struct PropertiesPage : public Page {

  EntryType type_;
  std::string restrictions_;

  PropertiesPage(EntryType, const std::string&);
};

#endif //LOODB_PROPERTIESPAGE_H
