#include "../api/PropertiesPage.h"

#include <string>


PropertiesPage::PropertiesPage(EntryType type, const std::string& restrictions) :
  Page(PROPERTIES_PAGE),
  type_{type},
  restrictions_{restrictions}
{}