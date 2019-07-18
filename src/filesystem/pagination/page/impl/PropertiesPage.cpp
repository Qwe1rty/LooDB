#include "../api/PropertiesPage.h"

#include <string>


PropertiesPage::PropertiesPage(EntryType type,
                               const std::string& column,
                               const std::string& restrictions) :
  Page(PROPERTIES_PAGE),
  type_{type},
  column_{column},
  restrictions_{restrictions}
{}