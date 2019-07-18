#include "../api/Entry/Entry.h"
#include "../api/Entry/IntEntry.h"
#include "../../interpreter/statements/api/Select.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <memory>

void printSet(std::set<uint32_t>& set) {
  std::cout << "Printing set:";
  for (auto it=set.begin(); it!=set.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

std::set<uint32_t> setUnion(std::set<uint32_t>& set1, std::set<uint32_t>& set2) {
  // Declare union set
  std::set<uint32_t> union_;

  // Get union of set1 and set2
  std::set_union(set1.begin(), set1.end(),
    set2.begin(), set2.end(),
    std::inserter(union_, union_.begin()));

  return union_;
}

std::set<uint32_t> setIntersection(std::set<uint32_t>& set1, std::set<uint32_t>& set2) {
  // Declare intersection set
  std::set<uint32_t> intersection_;

  // Get union of set1 and set2
  std::set_intersection(set1.begin(), set1.end(),
    set2.begin(), set2.end(),
    std::inserter(intersection_, intersection_.begin()));

  return intersection_;
}

void union_intersection() {
  std::set<uint32_t> set1 = {1, 2, 3};
  std::set<uint32_t> set2 = {4, 5, 6};

  std::set<uint32_t> union_ = setUnion(set1, set2);
  std::set<uint32_t> intersection_ = setIntersection(set1, set2);

  printSet(union_);
  printSet(intersection_);
}

std::set<uint32_t> whereHelper(std::vector<std::pair<std::unique_ptr<Entry>, uint32_t>>& col1,
                               std::vector<std::pair<std::unique_ptr<Entry>, uint32_t>>& col2,
                               std::unique_ptr<SQLSelect::WhereTree>& root) {
  // Declare pks set
  std::set<uint32_t> pks;

  // Is a where expression
  if (root->leaf_) {
    // Get column and entry
    const std::string& columnName = std::get<0>(root->expr_);
    const std::vector<std::pair<std::unique_ptr<Entry>, uint32_t>>& column = columnName == "col1" ? col1 : col2;
    const std::unique_ptr<Entry>& entry = std::get<1>(root->expr_);

    // Find entry in column
    auto iter = column.begin();
    while (iter != column.end()) {
      std::cout << static_cast<IntEntry&>(*((*iter).first)).getVal();
      std::cout << " == ";
      std::cout << static_cast<IntEntry&>(*entry).getVal();
      std::cout << std::endl;
      if (*((*iter).first) == *entry) break;
      ++iter;
    }

    // While iter meets where condition, insert pk into pks
    while (iter != column.end() && *((*iter).first) == *entry) {
      pks.insert((*iter).second);
      ++iter;
    }

    printSet(pks);

    return pks;
  }

  // Is a where operation

  // Get LHS where pks
  std::set<uint32_t> l_pks = whereHelper(col1, col2, root->where1_);
  // Get RHS where pks
  std::set<uint32_t> r_psk = whereHelper(col1, col2, root->where2_);

  // Set pks to union or intersection of wheres
  if (root->op_ == "AND") {
    pks = setIntersection(l_pks, r_psk);
  } else { // "OR"
    pks = setUnion(l_pks, r_psk);
  }

  return pks;
}

std::set<uint32_t> where(std::vector<std::pair<std::unique_ptr<Entry>, uint32_t>>& col1,
                         std::vector<std::pair<std::unique_ptr<Entry>, uint32_t>>& col2,
                         std::unique_ptr<SQLSelect::WhereTree>& root) {
  // Get for primary keys
  std::set<uint32_t> pks = whereHelper(col1, col2, root);
  // Return primary keys
  return pks;
}

int main() {
  union_intersection();

  std::vector<std::pair<std::unique_ptr<Entry>, uint32_t>> col1;
  col1.emplace_back(std::make_pair(std::make_unique<IntEntry>(5), 5));
  col1.emplace_back(std::make_pair(std::make_unique<IntEntry>(5), 6));
  col1.emplace_back(std::make_pair(std::make_unique<IntEntry>(5), 8));
  col1.emplace_back(std::make_pair(std::make_unique<IntEntry>(6), 9));
  col1.emplace_back(std::make_pair(std::make_unique<IntEntry>(6), 10));

  std::vector<std::pair<std::unique_ptr<Entry>, uint32_t>> col2;
  col2.emplace_back(std::make_pair(std::make_unique<IntEntry>(7), 5));
  col2.emplace_back(std::make_pair(std::make_unique<IntEntry>(7), 8));
  col2.emplace_back(std::make_pair(std::make_unique<IntEntry>(8), 9));
  col2.emplace_back(std::make_pair(std::make_unique<IntEntry>(9), 10));
  col2.emplace_back(std::make_pair(std::make_unique<IntEntry>(10), 10));

  auto where1 = std::make_unique<SQLSelect::WhereTree>("col1", std::make_unique<IntEntry>(5));
  auto where2 = std::make_unique<SQLSelect::WhereTree>("col2", std::make_unique<IntEntry>(7));
  auto where3 = std::make_unique<SQLSelect::WhereTree>("col1", std::make_unique<IntEntry>(6));
  auto where4 = std::make_unique<SQLSelect::WhereTree>("AND", std::move(where1), std::move(where2));
  auto where5 = std::make_unique<SQLSelect::WhereTree>("OR", std::move(where4), std::move(where3));

  std::set<uint32_t> pks = where(col1, col2, where5);

  printSet(pks);
}