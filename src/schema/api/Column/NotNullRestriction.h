#ifndef LOODB_NOTNULLRESTRICTION_H
#define LOODB_NOTNULLRESTRICTION_H

#include "ColumnRestriction.h"
#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"
#include <memory>

// Decoration for Column
class NotNullRestriction : public ColumnRestriction  {

    bool valid_(Entry) override;

    std::unique_ptr<Page> read_(Entry) override;

    void write_(Entry, Page&) override;

  public:

    // Constructor
    NotNullRestriction(std::unique_ptr<Column> );

};

#endif // LOODB_NOTNULLRESTRICTION_H
