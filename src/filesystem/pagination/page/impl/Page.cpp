#include "../api/Page.h"


Page::Page(PageType type) :
  type_{type}
{}

Page::~Page() = default;

PageType Page::type() const {
  return type_;
}