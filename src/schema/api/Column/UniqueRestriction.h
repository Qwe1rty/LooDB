#ifndef LOODB_UNIQUERESTRICTION_H
#define LOODB_UNIQUERESTRICTION_H

#include "ColumnRestriction.h"
#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"
#include <memory>

// Decoration for Column
class UniqueRestriction : public ColumnRestriction  {

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
    UniqueRestriction(std::unique_ptr<Column> );

    // Validate an Entry before writing to Column
    bool valid(const Entry& entry) const;

    // Retrieve the page index for the primary key associated with the entry
    uint32_t read(const Entry& entry);

    // Write to Column
    void write(uint32_t entry_index, uint32_t row_index);

     // Check if Column is empty
    bool empty() const;

    std::unique_ptr<Iterator> begin();
    std::unique_ptr<Iterator> end();
    std::unique_ptr<Iterator> find(const Entry&);

};

#endif // LOODB_UNIQUERESTRICTION_H
