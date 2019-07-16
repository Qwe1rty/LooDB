#include "../../api/Column/BaseColumn.h"
#include "../../../filesystem/pagination/page/api/BTreeHeaderPage.h"
#include "../../../filesystem/pagination/page/api/BTreeNodePage.h"
#include "../../../filesystem/pagination/page/api/EntryPage.h"
#include "../../../schema/api/Entry/EntryCodec.h"


struct BaseColumn::Impl {

  std::string name_;
  const EntryType type_;
  Pager index_file_;
  Pager& data_file_;
};


/*
 * BTree helper functions
 */

namespace {

  // Split a child node into 2
  // TODO possible just pass in the root
  void split(Pager& pager,
             uint32_t split_index,
             BTreeNodePage& root,
             BTreeNodePage& child) {

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
    root.node_.at(split_index + 1).left_ = pager.size();
    pager.append(std::move(right_split));

    // Erase the middle element of the child now that it's stored in the parent
    child.node_.erase(child.node_.cbegin() + (BTreeNodePage::ORDER - 1));
  }

  // Inserts a key without a node that is not full (so it doesn't immediately need splitting)
  void insert_capacity(Pager& pager,
                       uint32_t insert_index,
                       BTreeNodePage& node,
                       const std::unique_ptr<Entry>& entry) {


  }
}


/*
 * Public member functions
 */

bool BaseColumn::valid_(const Entry& entry) const {

  return entry.getType() == impl_->type_;
}

uint32_t BaseColumn::read_(uint32_t) {

  return 102931258;
}

void BaseColumn::write_(uint32_t entry_index, uint32_t row_index) {

  if (empty_()) {

    // Make root node and append to end of file
    auto root_node = std::make_unique<BTreeNodePage>(
      true,
      0,
      std::vector<Cell>{}
    );
    impl_->index_file_.append(std::move(root_node));

    // Update the header's empty_ and root_ fields
    auto header = impl_->index_file_.fetch<BTreeHeaderPage>(0);
    header->empty_ = false;
    header->root_ = impl_->index_file_.size() - 1;
    impl_->index_file_.write(0, std::move(header));
  }

  else {

    auto header = impl_->index_file_.fetch<BTreeHeaderPage>(0);
    auto old_root = impl_->index_file_.fetch<BTreeNodePage>(header->root_);

    // If the node is full
    if (old_root->node_.size() >= 2 * BTreeNodePage::ORDER + 1) {

      // Create a new root with the old root as its first child
      auto new_root = std::make_unique<BTreeNodePage>(
        false,
        BTreeNodePage::ORDER,
        std::vector<Cell>{
          Cell{
            entry_index,
            row_index,
            header->root_
          }
        }
      );

      split(impl_->index_file_, 0, *new_root, *old_root);

      // Compare the key to be inserted and the previous root's middle key
      uint64_t middle_index{new_root->node_.at(0).key_};
      const EntryCodec codec{};
      const auto middle_entry = codec.decode(impl_->index_file_.fetch<EntryPage>(middle_index)->value_);
      const auto insert_entry = codec.decode(impl_->index_file_.fetch<EntryPage>(entry_index)->value_);

      uint32_t i = middle_entry < insert_entry;
      insert_capacity(impl_->index_file_, i, insert_entry);

      // Append the new root, and update the header to point to it

    }

    else {

    }
  }
}

bool BaseColumn::empty_() const {

  // Contains more than just the header page
  return impl_->index_file_.fetch<BTreeHeaderPage>(0)->empty_;
}


/*
 * Constructor
 */

BaseColumn::BaseColumn(const std::string& name, EntryType type, const std::unique_ptr<Pager>& data_file) :
  impl_{std::make_unique<Impl>(
      name,
      type,
      Pager{name, Page::SIZE},
      data_file
  )}
{

}