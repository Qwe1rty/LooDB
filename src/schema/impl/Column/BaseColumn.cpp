#include "../../api/Column/BaseColumn.h"
#include "../../../filesystem/pagination/page/api/BTreeHeaderPage.h"
#include "../../../filesystem/pagination/page/api/BTreeNodePage.h"
#include "../../../filesystem/pagination/page/api/EntryPage.h"
#include "../../../schema/api/Entry/EntryCodec.h"

#include <iostream>


class BaseColumn::Impl {

public:

  bool valid_(const Entry&) const;
  uint32_t read_(uint32_t);
  void write_(uint32_t entry_index, uint32_t row_index);
  bool empty_();

  Impl(std::string, EntryType, EntryCodec, Pager, Pager&);

private:

  std::string name_;
  const EntryType entry_type_;
  const EntryCodec entry_codec_;
  Pager index_file_;
  Pager& data_file_;

  std::unique_ptr<BTreeHeaderPage> fetch_header();
  std::unique_ptr<BTreeNodePage> fetch_node(int32_t);
  std::unique_ptr<Entry> fetch_entry(int32_t);

  void split(uint32_t, BTreeNodePage& root, BTreeNodePage& child);
  void insert_capacity(uint32_t row_index, 
                       uint32_t entry_index, 
                       uint32_t node_index);
};

void BaseColumn::ImplDeleter::operator()(Impl* impl) {
  delete impl;
}


/*
 * Private member functions
 */

std::unique_ptr<BTreeHeaderPage> BaseColumn::Impl::fetch_header() {
  return index_file_.fetch<BTreeHeaderPage>(0);
}

std::unique_ptr<BTreeNodePage> BaseColumn::Impl::fetch_node(int32_t index) {
  return index_file_.fetch<BTreeNodePage>(index);
}

std::unique_ptr<Entry> BaseColumn::Impl::fetch_entry(int32_t index) {
  return entry_codec_.decode(data_file_.fetch<EntryPage>(index)->value_);
}

// Split a child node into 2, TODO possibly just pass in the root
void BaseColumn::Impl::split(uint32_t split_index, BTreeNodePage& root, BTreeNodePage& child) {

  // Copy largest (BTreeNodePage::ORDER - 1) elements of the child into a right counterpart
  auto right_split = std::make_unique<BTreeNodePage>(
    child.leaf_,
    child.right_,
    std::vector<Cell>(
      child.node_.cbegin() + BTreeNodePage::ORDER - 1, // The middle element
      child.node_.cend()
    )
  );

  // Erase the elements from the child that are now in right_split, and update the child's
  // right pointer
  child.node_.erase(
    child.node_.cbegin() + BTreeNodePage::ORDER,
    child.node_.cend()
  );
  child.right_ = child.node_.at(BTreeNodePage::ORDER - 1).left_;

  // Insert the middle element of the child into the i'th slot of the parent,
  // updating the page numbers
  root.node_.insert(
    root.node_.cbegin() + split_index,
    child.node_.at(BTreeNodePage::ORDER - 1)
  );
  root.node_.at(split_index).left_ = root.node_.at(split_index + 1).left_;

  // Write the new child's page, and update the i+1'th cell in the root to point to the
  // new appended node
  root.node_.at(split_index + 1).left_ = index_file_.size();
  index_file_.append(std::move(right_split));

  // Erase the middle element of the child now that it's stored in the parent
  child.node_.erase(child.node_.cbegin() + (BTreeNodePage::ORDER - 1));
}

// Inserts a key without a node that is not full (so it doesn't immediately need splitting)
void BaseColumn::Impl::insert_capacity(const uint32_t row_index,
                                       const uint32_t entry_index,
                                       const uint32_t node_index) {

  std::cout << "insert_capacity with: " << row_index << ", " << entry_index << ", " << node_index << std::endl;

  // Fetch pages
  const auto entry = fetch_entry(entry_index);
  auto node = fetch_node(node_index);

  // Indexer used for traversing through keys in a node. The loop finds the right position where
  // the item should be inserted at
  int32_t i = 0;
  while (i < node->node_.size() && entry > fetch_entry(node->node_.at(i).key_)) ++i;

  if (!node->leaf_) {

    auto child = fetch_node(node->node_.at(i).left_);

    if (child->node_.size() >= 2 * BTreeNodePage::SIZE - 1) {

      // Split, and write back results of the modified child
      split(i + 1, *node, *child);
      index_file_.write(node->node_.at(i).left_, std::move(child));

      // Determine which of the two splitted children should contain the inserted entry
      if (fetch_entry(node->node_.at(i + 1).key_) < entry) ++i;
    }

    insert_capacity(row_index, entry_index, node->node_.at(i).key_);
  }

  // If the node is a leaf, you won't have to worry about child pages, so just insert the cell
  else node->node_.insert(node->node_.cbegin() + i, Cell{entry_index, row_index, 0});

  // Write back changes to the node
  index_file_.write(node_index, std::move(node));
}


/*
 * Public member functions
 */

bool BaseColumn::Impl::valid_(const Entry& entry) const {

  return entry.getType() == entry_type_;
}

uint32_t BaseColumn::Impl::read_(uint32_t) {

  return 102931258;
}

void BaseColumn::Impl::write_(uint32_t entry_index, uint32_t row_index) {

  std::cout << "size before: " << index_file_.size() << std::endl;

  if (empty_()) {

    // Make root node and append to end of file
    auto root_node = std::make_unique<BTreeNodePage>(
      true,
      0,
      std::vector<Cell>{}
    );
    index_file_.append(std::move(root_node));

    // Update the header's empty_ and root_ fields
    auto header = fetch_header();
    header->empty_ = false;
    header->root_ = index_file_.size() - 1;
    index_file_.write(0, std::move(header));
  }

  else {

    auto header = fetch_header();
    auto old_root = fetch_node(header->root_);

    // If the node is full
    if (old_root->node_.size() >= 2 * BTreeNodePage::ORDER - 1) {

      // Create a new root with the old root as its first child
      auto new_root = std::make_unique<BTreeNodePage>(
        false,
        BTreeNodePage::ORDER,
        std::vector<Cell>{Cell{entry_index, row_index, header->root_}}
      );

      split(0, *new_root, *old_root);

      // Compare the key to be inserted and the previous root's middle key
      uint64_t middle_index{new_root->node_.at(0).key_};
      uint32_t i = fetch_entry(middle_index) < fetch_entry(entry_index);
      insert_capacity(row_index, entry_index, new_root->node_.at(i).left_);

      // Write back the old root and new root before the header is updated (while old_root
      // index is still known)
      index_file_.write(header->root_, std::move(old_root));
      index_file_.append(std::move(new_root));

      // Update the header and write it back
      header->root_ = index_file_.size() - 1;
      index_file_.write(0, std::move(header));
    }

    else insert_capacity(row_index, entry_index, header->root_);
  }

  std::cout << "size after: " << index_file_.size() << std::endl;
}

bool BaseColumn::Impl::empty_() {

  // Contains more than just the header page
  return fetch_header()->empty_;
}

BaseColumn::Impl::Impl(std::string name,
                       EntryType entry_type,
                       EntryCodec entry_codec,
                       Pager index_file,
                       Pager& data_file) :
  name_{std::move(name)},
  entry_type_{entry_type},
  entry_codec_{std::move(entry_codec)},
  index_file_{std::move(index_file)},
  data_file_{data_file}
{
  if (index_file_.size() == 0) {
    index_file_.append(std::make_unique<BTreeHeaderPage>(0, true));
  }
}


/*
 * Iterator implementation
 */

uint32_t BaseColumn::Iterator::operator*() {
  // TODO
}

BaseColumn::Iterator& BaseColumn::Iterator::operator++() {
  // TODO
  return *this;
}

bool BaseColumn::Iterator::operator!=(const Column::Iterator& src) {
  return !(*this == src);
}

bool BaseColumn::Iterator::operator==(const Column::Iterator& src) {
  // TODO
}


/*
 * BaseColumn.h implementations
 */

bool BaseColumn::valid_(const Entry& entry) const {
  return impl_->valid_(entry);
}

uint32_t BaseColumn::read_(uint32_t index) {
  return impl_->read_(index);
}

void BaseColumn::write_(uint32_t entry_index, uint32_t row_index) {
  impl_->write_(entry_index, row_index);
}

bool BaseColumn::empty_() const {
  return impl_->empty_();
}

BaseColumn::BaseColumn(const std::string& name, EntryType type, Pager& data_file) :
  impl_{std::unique_ptr<Impl, ImplDeleter>(
    new Impl(
      name,
      type,
      EntryCodec{},
      Pager{name, Page::SIZE},
      data_file
    )
  )}
{}