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

  // pImpl for Base Column
  class Impl;
  std::unique_ptr<Impl> impl_;

  bool valid_(const Entry&) const override;
  uint32_t read_(uint32_t) override;
  void write_(uint32_t entry_index, uint32_t row_index) override;
  bool empty_() const override;

  // class Iterator;
  // BaseColumn::Iterator begin_() override;
  // BaseColumn::Iterator end_() override;
  // BaseColumn::Iterator find_(Entry) override;

public:

  // Constructor
  BaseColumn(const std::string&, EntryType, const std::unique_ptr<Pager>&);
};

#endif // LOODB_BASECOLUMN_H
