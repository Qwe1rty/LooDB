#ifndef LOODB_UNIQUERESTRICTION_H
#define LOODB_UNIQUERESTRICTION_H

#include "ColumnRestriction.h"
#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"
#include <memory>

// Decoration for Column
class UniqueRestriction : public ColumnRestriction  {

    bool valid_(Entry) override;

    std::unique_ptr<Page> read_(Entry) override;

    void write_(Entry, Page&) override;

  public:

    // Constructor
    UniqueRestriction( /* params */ );

};

#endif // LOODB_UNIQUERESTRICTION_H
