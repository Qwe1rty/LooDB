#ifndef LOODB_COLUMNRESTRICTION_H
#define LOODB_COLUMNRESTRICTION_H

#include "Column.h"
#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"

#include <memory>


// Decorator for Column
class ColumnRestriction : public Column  {

protected:

  // Base column, and its constructor
  std::unique_ptr<Column> base_;

  ColumnRestriction(std::unique_ptr<Column>);
};


#endif // LOODB_COLUMNRESTRICTION_H