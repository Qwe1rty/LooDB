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

  struct Iterator : Column::Iterator {

    uint32_t operator* () override;
    Iterator& operator++ () override;
    bool operator!= (const Column::Iterator&) override;
    bool operator== (const Column::Iterator&) override;

    class Impl;
    std::unique_ptr<Impl> impl_;

    explicit Iterator(std::unique_ptr<Impl>);
  };

  bool valid_(const Entry&) const override;
  uint32_t read_(const Entry&) override; // TODO rename to at_ to make it less misleading
  void write_(uint32_t entry_index, uint32_t row_index) override;
  bool empty_() const override;

  std::unique_ptr<Column::Iterator> begin_() override;
  std::unique_ptr<Column::Iterator> end_() override;
  std::unique_ptr<Column::Iterator> find_(const Entry&) override;

  // PIMPL for Base Column
  class Impl;
  struct ImplDeleter {
    void operator()(Impl*);
  };
  std::unique_ptr<Impl, ImplDeleter> impl_;
};

#endif // LOODB_BASECOLUMN_H
