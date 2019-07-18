#include "../../api/Column/ColumnRestriction.h"


ColumnRestriction::ColumnRestriction(std::unique_ptr<Column> base) :
  base_{std::move(base)}
{}

Column& ColumnRestriction::base() const {
  return *base_;
}