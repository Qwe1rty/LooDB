#ifndef LOODB_COLUMN_H
#define LOODB_COLUMN_H

#include "../Entry/Entry.h"
#include "../../../filesystem/pagination/page/api/Page.h"
#include <memory>

class Column {

public:

  struct Iterator {

    // operator* will dereference to the page number of the:
    //  1) the entry
    //  2) page index of the associated primary key
    virtual std::pair<std::unique_ptr<Entry>, uint32_t> operator* () = 0;
    virtual Iterator& operator++ () = 0;
    virtual bool operator!= (const Iterator&) = 0;
    virtual bool operator== (const Iterator&) = 0;

    virtual ~Iterator() = default;
  };

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

  virtual ~Column() = default;

private:

  // Validate an Entry before writing to Column
  virtual bool valid_(const Entry& entry) const = 0;

  // Retrieve the page index for the primary key associated with the entry
  virtual uint32_t read_(const Entry& entry) = 0;

  // Write to Column
  virtual void write_(uint32_t entry_index, uint32_t row_index) = 0;

  // Check if Column is empty
  virtual bool empty_() const = 0;

  virtual std::unique_ptr<Iterator> begin_() = 0;
  virtual std::unique_ptr<Iterator> end_() = 0;
  virtual std::unique_ptr<Iterator> find_(const Entry&) = 0;
};


#endif // LOODB_COLUMN_H