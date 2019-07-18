#include "../api/Select.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

SQLSelect::WhereTree::WhereTree(std::string columnName, std::unique_ptr<Entry> entry) :
  expr_(make_tuple(columnName, move(entry))), leaf_(true), op_(""), where1_(nullptr), where2_(nullptr) {}

SQLSelect::WhereTree::WhereTree(std::string op,
  std::unique_ptr<WhereTree> where1, std::unique_ptr<WhereTree> where2) :
  leaf_(false), op_(op), where1_(move(where1)), where2_(move(where2)) {}

SQLSelect::Impl::Impl(vector<string> columns, bool where, unique_ptr<SQLSelect::WhereTree> whereTree)
  : columns_(move(columns)), where_(where), whereTree_(move(whereTree)) {}

SQLSelect::SQLSelect(std::string tableName, std::vector<std::string> columns,
  bool where, unique_ptr<SQLSelect::WhereTree> whereTree) : 
  SQLStatement(tableName, stmtSelect), impl_{make_unique<Impl>(move(columns), where, move(whereTree))} {}

std::vector<std::string>& SQLSelect::Impl::getColumns_() {
  return this->columns_;
}

bool SQLSelect::Impl::getWhere() { return where_; }

std::unique_ptr<SQLSelect::WhereTree>& SQLSelect::Impl::getWhereTree_() {
  return this->whereTree_;
}

void SQLSelect::Impl::printWhereTreeHelper(std::unique_ptr<SQLSelect::WhereTree>& root) {
  // Base case
  if (root->leaf_) {
    // std::cerr << std::get<0>(root->expr_) << " = " << std::get<1>(root->expr_)->getType();
    return;
  }

  // std::cerr << "(";
  // printWhereTreeHelper(root->where1_);
  // std::cerr << " " << root->op_ << " ";
  // printWhereTreeHelper(root->where2_);
  // std::cerr << ")";

  return;
}

void SQLSelect::Impl::printWhereTree() {
  printWhereTreeHelper(whereTree_);
}

std::vector<std::string>& SQLSelect::getColumns() const {
  return this->impl_->getColumns_();
}

bool SQLSelect::hasWhere() const {
  return impl_->getWhere();
}

std::unique_ptr<SQLSelect::WhereTree>& SQLSelect::getWhereTree() const {
  return this->impl_->getWhereTree_();
}

void SQLSelect::printWhere() {
  impl_->printWhereTree();
}