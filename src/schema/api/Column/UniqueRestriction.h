#ifndef LOODB_UNIQUERESTRICTION_H
#define LOODB_UNIQUERESTRICTION_H

#include "ColumnRestriction.h"
#include "../Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"

// Decoration for Column
class UniqueRestriction : public ColumnRestriction  {

    bool valid_(Entry) override;

    Page read_(Entry) override;

    void write_(Entry, Page) override;

  public:

    // Constructor
    UniqueRestriction( /* params */ );

};

#endif // LOODB_UNIQUERESTRICTION_H
