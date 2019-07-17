#include "../../api/Column/BaseColumn.h"

#include "BaseColumn.cpp"

#include <stack>


class BaseColumn::Impl::Iterator {

private:

  Impl& parent_;
  std::stack<uint32_t> path_;
  std::stack<uint32_t> cells_;

public:

  uint32_t operator* ();
  Iterator& operator++ ();
  bool operator!= (const Column::Iterator&);
  bool operator== (const Column::Iterator&);

  Iterator(Impl&, std::stack<uint32_t> path, std::stack<uint32_t> positions);
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

//  std::stack<uint32_t> path{};
//  std::stack<uint32_t> cells{};
//  const auto header = fetch_header();
//
//  if (!header->empty_) {
//
//    path.push(header->root_);
//    auto node = fetch_node(header->root_);
//
//    while (node->node_.front().left_ != 0) {
//      uint32_t child_index = node->node_.front().left_;
//      path.push(child_index);
//      node = fetch_node(child_index);
//    }
//  }
//
//  return BaseColumn::Impl::Iterator{
//    *this,
//    std::move(path),
//    std::move(cells)
//  };
}

BaseColumn::Impl::Iterator BaseColumn::Impl::end_() {

//  std::stack<uint32_t> path{};
//  std::stack<uint32_t> cells{};
//  const auto header = fetch_header();
//
//  if (!header->empty_) {
//
//    path.push(header->root_);
//    auto node = fetch_node(header->root_);
//
//    while (node->right_ != 0) {
//      uint32_t child_index = node->right_;
//      path.push(child_index);
//      node = fetch_node(child_index);
//    }
//
//    last = node->node_.size();
//  }
//
//  return BaseColumn::Impl::Iterator{
//    *this,
//    std::move(path),
//    last
//  }; // TODO double check this
}

BaseColumn::Impl::Iterator BaseColumn::Impl::find_(const Entry& entry) {

  std::stack<uint32_t> path{};
  std::stack<uint32_t> cells{};

  const auto header = fetch_header();

  if (!header->empty_) {

    path.push(header->root_);
    auto node = fetch_node(header->root_);

    while (true) {

      // Find the index where the entry would be located
      uint32_t cell{0};
      while (cell < node->node_.size() && entry > *fetch_entry(node->node_.at(cell).key_)) ++cell;

      uint32_t child_index = cell < node->node_.size() ?
        node->node_.at(cell).left_ :
        node->right_;

      // If there's a child within, then "recurse" to that node (AKA not a leaf).
      // Otherwise, you're done
      if (child_index > 0) {

        path.push(child_index);
        cells.push(cell);
        node = fetch_node(child_index);
      }
      else break;
    }
  }

  return BaseColumn::Impl::Iterator{
    *this,
    std::move(path),
    std::move(cells),
  };
}


/*
 * Iterator implementation
 */

uint32_t BaseColumn::Impl::Iterator::operator*() {
  return parent_.fetch_node(path_.top())->node_.at(cells_.top()).key_;
}

BaseColumn::Impl::Iterator& BaseColumn::Impl::Iterator::operator++() {

//  const auto node = parent_.fetch_node(path_.top());
//  uint32_t child_index;

  ++last_;

  if (last_ < node->node_.size()) {

  }

  while ()

//  // Get the next inorder child page index
//  if (cell_ + 1 < node->node_.size()) {
//    ++cell_;
//    if (node->node_.at(cell_).left_ > 0) {
//
//    }
//  }
//  else {
//
//  }
//
//  // If this cell has a child, then "recurse" into it
//  if (child_index > 0) {
//    path_.push(child_index);
//    cell_ = 0;
//  }
//
//  // If the

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
           iter.cells_ == cells_;
  }

  return false;
}

BaseColumn::Impl::Iterator::Iterator(BaseColumn::Impl& parent,
                                     std::stack<uint32_t> path,
                                     std::stack<uint32_t> positions,
                                     uint32_t last) :
  parent_{parent},
  path_{std::move(path)},
  cells_{std::move(positions)},
  last_{last}
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
