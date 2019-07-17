#ifndef LOODB_PAGER_H
#define LOODB_PAGER_H

#include "../../page/api/Page.h"

#include <cstdint>
#include <memory>
#include <string>


class Pager final {

  const static uint32_t DEFAULT_CACHE_LIMIT = 2000;

public:

  explicit Pager(const std::string&, uint32_t = DEFAULT_CACHE_LIMIT);

  template<typename T>
  std::unique_ptr<T> fetch(uint32_t);
  std::unique_ptr<Page> read(uint32_t);

  void write(uint32_t, const std::unique_ptr<Page>&);
  uint32_t append(const std::unique_ptr<Page>&); // Returns the page number of the appended page

  uint32_t length() const; // Returns number of bytes the file contains
  uint32_t size() const;   // Returns number of pages the file contains
  const std::string& name() const;


private:

  class Impl;
  struct ImplDeleter {
    void operator()(Impl*);
  };

  std::unique_ptr<Impl, ImplDeleter> impl_;
};

#include "../impl/Pager.tpp"

#include "../impl/Pager.tpp"

#endif //LOODB_PAGER_H