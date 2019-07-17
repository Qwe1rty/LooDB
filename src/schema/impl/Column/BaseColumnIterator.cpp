#include "../../api/Column/BaseColumn.h"

#include "BaseColumn.cpp"

#include <stack>


class BaseColumn::Impl::Iterator {

private:

  Impl& parent_;
  std::stack<uint32_t> path_;
  uint32_t cell_;

public:

  uint32_t operator* ();
  Iterator& operator++ ();
  bool operator!= (const Column::Iterator&);
  bool operator== (const Column::Iterator&);

  Iterator(Impl& parent, std::stack<uint32_t> path, uint32_t cell);
};

struct BaseColumn::Iterator::Impl {

  // Unfortunate double pointer indirection :/
  // Good enough for now, I guess
  std::unique_ptr<BaseColumn::Impl::Iterator> impl_;
};


/*
 * Public member functions
 */

BaseColumn::Impl::Iterator BaseColumn::Impl::begin_() {

  const auto header = fetch_header();
  if (header->empty_) {
    
  }
  auto node = fetch_node(header->root_);

  std::stack<uint32_t> path{};

  while (node->node_.at(0).left_ != 0) {
    node = fetch_node(node->node_.at(0).left_);
  }

  return BaseColumn::Impl::Iterator{*this, std::move(path), 0};
}

BaseColumn::Impl::Iterator BaseColumn::Impl::end_() {

  const auto header = fetch_header();
  auto node = fetch_node(header->root_);

  std::stack<uint32_t> path{};

  while (node->node_.at(0).left_ != 0) {
    node = fetch_node(node->node_.at(0).left_);
  }

  return BaseColumn::Impl::Iterator{*this, std::move(path), 0};
}

BaseColumn::Impl::Iterator BaseColumn::Impl::find_(const Entry& entry) {

  std::stack<uint32_t> path{};

  const auto header = fetch_header();
  auto node = fetch_node(header->root_);

  while (node->node_.at(0).left_ != 0) {
    node = fetch_node(node->node_.at(0).left_);
  }

  return BaseColumn::Impl::Iterator{*this, std::move(path), 0};
}


/*
 * Iterator implementation
 */

uint32_t BaseColumn::Impl::Iterator::operator*() {
  return parent_.fetch_node(path_.top())->node_.at(cell_).key_;
}

BaseColumn::Impl::Iterator& BaseColumn::Impl::Iterator::operator++() {

  const auto node = parent_.fetch_node(path_.top());
  uint32_t child_index;

  // Get the next inorder child page index
  if (cell_ + 1 < node->node_.size()) {
    ++cell_;
    child_index = node->node_.at(cell_).left_;
  }
  else {
    child_index = node->right_;
  }

  // If this cell has a child, then "recurse" into it
  if (child_index > 0) {
    path_.push(child_index);
    cell_ = 0;
  }

  return *this;
}

bool BaseColumn::Impl::Iterator::operator!=(const Column::Iterator& src) {
  return !(*this == src);
}

bool BaseColumn::Impl::Iterator::operator==(const Column::Iterator& src) {

  auto* src_cast = dynamic_cast<BaseColumn::Iterator const*>(&src);

  if (src_cast) {
    const auto& iter = *src_cast->impl_->impl_;
    return iter.path_ == path_ &&
           iter.cell_ == cell_;
  }

  return false;
}

BaseColumn::Impl::Iterator::Iterator(BaseColumn::Impl& parent,
                                     std::stack<uint32_t> path,
                                     uint32_t cell) :
  parent_{parent},
  path_{std::move(path)},
  cell_{cell}
{}


/*
 * BaseColumn::Iterator.h implementations
 */

uint32_t BaseColumn::Iterator::operator*() {
  return impl_->impl_->operator*();
}

BaseColumn::Iterator& BaseColumn::Iterator::operator++() {
  impl_->impl_->operator++();
  return *this;
}

bool BaseColumn::Iterator::operator!=(const Column::Iterator& src) {
  return !(*this == src);
}

bool BaseColumn::Iterator::operator==(const Column::Iterator& src) {
  return impl_->impl_->operator==(src);
}
