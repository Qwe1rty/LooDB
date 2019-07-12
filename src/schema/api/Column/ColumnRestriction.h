#ifndef LOODB_COLUMNRESTRICTION_H
#define LOODB_COLUMNRESTRICTION_H

#include "Column.h"
#include "../Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"
#include <memory>

// Private members of Column Restriction
struct ColumnRestrictionImpl{
  std::unique_ptr<Column> base_;
};

// Decorator for Column
class ColumnRestriction : public Column  {

    // pImpl for Column Restriction
    std::unique_ptr<ColumnRestrictionImpl> impl_;

    virtual bool valid_(Entry);

    virtual Page read_(Entry);

    virtual void write_(Entry, Page);

  public:

    // Constructor
    ColumnRestriction( /* params */ );

};

#endif // LOODB_COLUMNRESTRICTION_H
