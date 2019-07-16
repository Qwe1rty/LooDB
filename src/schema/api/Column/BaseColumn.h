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

public:

  // Constructor
  BaseColumn(const std::string&, EntryType, Pager&);

private:

  bool valid_(const Entry&) const override;
  uint32_t read_(uint32_t) override;
  void write_(uint32_t entry_index, uint32_t row_index) override;
  bool empty_() const override;

  // class Iterator;
  // BaseColumn::Iterator begin_() override;
  // BaseColumn::Iterator end_() override;
  // BaseColumn::Iterator find_(Entry) override;

  // PIMPL for Base Column
  class Impl;
  struct ImplDeleter {
    void operator()(Impl*);
  };

  std::unique_ptr<Impl, ImplDeleter> impl_;
};

#endif // LOODB_BASECOLUMN_H
