#include "../api/Table.h"
using namespace std;

Table::TableImpl::TableImpl(string s) : name_(s)  {}

Table::Table(string s) : impl_{make_unique<TableImpl>(s)} {}
