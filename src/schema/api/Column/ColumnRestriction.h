#ifndef LOODB_COLUMNRESTRICTION_H
#define LOODB_COLUMNRESTRICTION_H

#include "Column.h"
#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"

#include <memory>


// Decorator interface for Column
class ColumnRestriction : public Column  {

  // Base column
  const std::unique_ptr<Column> base_;

protected:

  Column& base() const;

  ColumnRestriction(std::unique_ptr<Column>);
};


#endif // LOODB_COLUMNRESTRICTION_H