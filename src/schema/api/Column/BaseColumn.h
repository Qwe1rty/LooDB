#ifndef LOODB_BASECOLUMN_H
#define LOODB_BASECOLUMN_H

#include "Column.h"
#include "../Entry/Entry.h"
#include "../Entry/EntryType.h"
#include "../../../filesystem/pagination/page/api/Page.h"
#include "../../../filesystem/pagination/interface/api/Pager.h"
#include <memory>
#include <string>

class BaseColumn : public Column  {

    // Private members of Base Column
    struct BaseColumnImpl{
      std::string name_;
      EntryType type_;
      std::unique_ptr<Pager> file_;
    };

    // pImpl for Base Column
    std::unique_ptr<BaseColumnImpl> impl_;

    // class Iterator;

    bool valid_(Entry) override;

    std::unique_ptr<Page> read_(Entry) override;

    void write_(Entry, Page&) override;

    bool empty_() override;

    // BaseColumn::Iterator begin_() override;

    // BaseColumn::Iterator end_() override;

    // BaseColumn::Iterator find_(Entry) override;

  public:

    // Constructor
    BaseColumn( /* params */ );

};

#endif // LOODB_BASECOLUMN_H
