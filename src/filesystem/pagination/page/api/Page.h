#ifndef LOODB_PAGE_H
#define LOODB_PAGE_H

#include "PageCodec.h"

#include <cstdint>
#include <memory>


class Page {

public:

  // PAGE_SIZE: This is the constant size of all our pages
  // PAGE_CODEC: Global converter interface
  
  const static uint32_t PAGE_SIZE;
  const static PageCodec PAGE_CODEC;

  virtual ~Page() = 0;
};

#endif //LOODB_PAGE_H
