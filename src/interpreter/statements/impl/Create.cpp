#include "../api/Create.h"
#include "../../../schema/api/Entry/EntryType.h"

SQLCreate::Impl::Impl(std::vector<std::tuple<std::string, EntryType, std::string>> c) : columns_(c) {}

SQLCreate::SQLCreate(std::string t, std::vector<std::tuple<std::string, EntryType, std::string>> c) : 
  SQLStatement(t, stmtCreate), impl_{std::make_unique<Impl>(c)} {}
