#include "../api/Pager.h"


template<typename T>
std::unique_ptr<T> Pager::fetch(uint32_t page_index) {
  return std::unique_ptr<T>(static_cast<T*>(read(page_index).release()));
}