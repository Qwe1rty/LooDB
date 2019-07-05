#ifndef LOODB_PAGE_H
#define LOODB_PAGE_H

#include <cstdint>
#include <memory>


class Page {

public:

  // PAGE_SIZE: This is the constant size of all our pages
  const static uint64_t PAGE_SIZE = 4096;

  virtual ~ Page() = 0;
};

#endif //LOODB_PAGE_H
