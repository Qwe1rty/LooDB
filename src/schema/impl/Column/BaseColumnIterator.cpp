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

  Iterator(Impl&, std::stack<uint32_t> path, std::stack<uint32_t> cells);
};

struct BaseColumn::Iterator::Impl {

  // Unfortunate double pointer indirection :/
  // Good enough for now, I guess
  std::unique_ptr<BaseColumn::Impl::Iterator> impl_;

  explicit Impl(std::unique_ptr<BaseColumn::Impl::Iterator>);
};


/*
 * Public member functions
 */

BaseColumn::Impl::Iterator BaseColumn::Impl::begin_() {

  const auto header = fetch_header();

  std::stack<uint32_t> path{};
  std::stack<uint32_t> cells{};

  if (!header->empty_) {

    path.push(header->root_);
    auto node = fetch_node(header->root_);

    uint32_t child_index = node->node_.front().left_;

    while (node->node_.front().left_ > 0) {

      path.push(child_index);
      node = fetch_node(child_index);
    }
  }

  return BaseColumn::Impl::Iterator{
    *this,
    std::move(path),
    std::move(cells)
  };
}

BaseColumn::Impl::Iterator BaseColumn::Impl::end_() {

  return BaseColumn::Impl::Iterator{
    *this,
    std::stack<uint32_t>{},
    std::stack<uint32_t>{}
  };
}

BaseColumn::Impl::Iterator BaseColumn::Impl::find_(const Entry& entry) {

  const auto header = fetch_header();

  if (!header->empty_) {

    std::stack<uint32_t> path{};
    std::stack<uint32_t> cells{};

    path.push(header->root_);
    auto node = fetch_node(header->root_);

    while (true) {

      // Find the index where the entry would be located
      uint32_t cell{0};
      while (cell < node->node_.size() && entry > *fetch_entry(node->node_.at(cell).key_)) {
        ++cell;
      }
      cells.push(cell);

      // If it's been found, return iterator to it
      if (entry == *fetch_entry(node->node_.at(cell).key_)) {
        return BaseColumn::Impl::Iterator{*this, std::move(path), std::move(cells)};
      }

      // If it hasn't been found, try to see if it's contained in a child node, and if it is,
      // then "recurse" to that node (AKA not a leaf). Otherwise, you're done, as it's not in the tree
      uint32_t child_index = cell < node->node_.size() ?
        node->node_.at(cell).left_ :
        node->right_;

      if (child_index > 0) {
        path.push(child_index);
        node = fetch_node(child_index);
      }
      else break;
    }
  }

  // Return the end iterator if it's not found or tree is empty
  return end_();
}


/*
 * Iterator implementation
 */

uint32_t BaseColumn::Impl::Iterator::operator*() {
  return parent_.fetch_node(path_.top())->node_.at(cells_.top()).key_;
}

BaseColumn::Impl::Iterator& BaseColumn::Impl::Iterator::operator++() {

  // If it's not already at the end or just empty
  if (!path_.empty() && !cells_.empty()) {
    do {

      // Increment cell value for this B-Tree node
      uint32_t cell = cells_.top() + 1;
      cells_.pop();

      // Fetch the current node, and see if we need to backtrack
      const auto node = parent_.fetch_node(path_.top());
      if (cell < node->node_.size()) break;
      path_.pop();

    } while (!path_.empty());
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
           iter.cells_ == cells_;
  }

  return false;
}

BaseColumn::Impl::Iterator::Iterator(BaseColumn::Impl& parent,
                                     std::stack<uint32_t> path,
                                     std::stack<uint32_t> cells) :
  parent_{parent},
  path_{std::move(path)},
  cells_{std::move(cells)}
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

BaseColumn::Iterator::Impl::Impl(std::unique_ptr<BaseColumn::Impl::Iterator> impl) :
  impl_{std::move(impl)}
{}


/*
 * BaseColumn.h implementations
 */

std::unique_ptr<Column::Iterator> BaseColumn::begin_() {
  return std::make_unique<BaseColumn::Iterator>(
    std::make_unique<BaseColumn::Iterator::Impl>(impl_->begin_())
  );
}

std::unique_ptr<Column::Iterator> BaseColumn::end_() {
  return std::make_unique<BaseColumn::Iterator>(
    std::make_unique<BaseColumn::Iterator::Impl>(impl_->end_())
  );
}

std::unique_ptr<Column::Iterator> BaseColumn::find_(const Entry& entry) {
  return std::make_unique<BaseColumn::Iterator>(
    std::make_unique<BaseColumn::Iterator::Impl>(impl_->find_(entry))
  );
}

BaseColumn::Iterator::Iterator(std::unique_ptr<BaseColumn::Iterator::Impl> impl) :
  impl_{std::move(impl)}
{}
