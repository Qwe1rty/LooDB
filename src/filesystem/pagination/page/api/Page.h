#ifndef LOODB_PAGE_H
#define LOODB_PAGE_H

#include "../../interface/api/PageType.h"

#include <cstdint>
#include <memory>


class Page {

public:

  // PAGE_SIZE: This is the constant size of all our pages
  constexpr static uint32_t PAGE_SIZE = 4096;

  PageType type() const;

  virtual ~Page() = 0;

protected:

  Page(PageType);

private:

  const PageType type_;
};

#endif //LOODB_PAGE_H
