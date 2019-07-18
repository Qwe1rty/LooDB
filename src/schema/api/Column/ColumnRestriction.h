#ifndef LOODB_COLUMNRESTRICTION_H
#define LOODB_COLUMNRESTRICTION_H

#include "Column.h"
#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"
#include <memory>

// Decorator for Column
class ColumnRestriction : public Column  {

    // Private members of Column Restriction
    struct ColumnRestrictionImpl{
      std::unique_ptr<Column> base_;
      ColumnRestrictionImpl(std::unique_ptr<Column>);
    };

      // Validate an Entry before writing to Column
    virtual bool valid_(const Entry& entry) const override;

    // Retrieve the page index for the primary key associated with the entry
    virtual uint32_t read_(const Entry& entry) override;

    // Write to Column
    virtual void write_(uint32_t entry_index, uint32_t row_index) override;
  
     // Check if Column is empty
    virtual bool empty_() const override;

    virtual std::unique_ptr<Iterator> begin_() override;
    virtual std::unique_ptr<Iterator> end_() override;
    virtual std::unique_ptr<Iterator> find_(const Entry&) override;

  protected:

    // pImpl for Column Restriction
    std::unique_ptr<ColumnRestrictionImpl> impl_;

  public:

    // Constructor
    ColumnRestriction(std::unique_ptr<Column>);
    
    // Validate an Entry before writing to Column
    bool valid(const Entry& entry) const;

    // Retrieve the page index for the primary key associated with the entry
    uint32_t read(const Entry& entry);

    // Write to Column
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

#endif // LOODB_COLUMNRESTRICTION_H
