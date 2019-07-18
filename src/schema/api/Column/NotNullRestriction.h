#ifndef LOODB_NOTNULLRESTRICTION_H
#define LOODB_NOTNULLRESTRICTION_H

#include "ColumnRestriction.h"
#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"
#include <memory>

// Decoration for Column
class NotNullRestriction : public ColumnRestriction  {

  // Validate an Entry before writing to Column
  bool valid_(const Entry& entry) const override;

    // Retrieve the page index for the primary key associated with the entry
  uint32_t read_(const Entry& entry) override;

    // Write to Column
  void write_(uint32_t entry_index, uint32_t row_index) override;

     // Check if Column is empty
  virtual bool empty_() const override;

  virtual std::unique_ptr<Iterator> begin_() override;
  virtual std::unique_ptr<Iterator> end_() override;
  virtual std::unique_ptr<Iterator> find_(const Entry&) override;

  public:

    // Constructor
    NotNullRestriction(std::unique_ptr<Column> );

    // NVI for valid_()
    bool valid(const Entry& entry) const;

    // NVI for read_()
    uint32_t read(const Entry& entry);

    // NVI for write_()
    void write(uint32_t entry_index, uint32_t row_index);

    // NVI for empty_()
    bool empty() const;

    //NVI for begin_()
    std::unique_ptr<Iterator> begin();

    // NVI for end_()
    std::unique_ptr<Iterator> end();

    // NVI for find_()
    std::unique_ptr<Iterator> find(const Entry&);
};

#endif // LOODB_NOTNULLRESTRICTION_H
