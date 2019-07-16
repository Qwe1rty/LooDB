#include "../../api/Column/BaseColumn.h"
#include "../../../filesystem/pagination/page/api/BTreeHeaderPage.h"
#include "../../../filesystem/pagination/page/api/BTreeNodePage.h"


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

  void split(int split_index,
             BTreeNodePage& node,
             Pager& pager) {


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

      split(0, *new_root, impl_->index_file_);
      // TODO SPLIT CHILD


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