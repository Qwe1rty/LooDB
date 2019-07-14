#include "../api/Page.h"


Page::Page(PageType type) :
  type_{type}
{}

PageType Page::type() const {
  return type_;
}