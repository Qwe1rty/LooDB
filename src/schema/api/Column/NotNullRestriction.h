#ifndef LOODB_NOTNULLRESTRICTION_H
#define LOODB_NOTNULLRESTRICTION_H

#include "ColumnRestriction.h"
#include "../Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"

// Decoration for Column
class NotNullRestriction : public ColumnRestriction  {

    bool valid_(Entry) override;

    Page read_(Entry) override;

    void write_(Entry, Page) override;

  public:

    // Constructor
    NotNullRestriction( /* params */ );

};

#endif // LOODB_NOTNULLRESTRICTION_H
