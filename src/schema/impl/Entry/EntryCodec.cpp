#include "../../api/Entry/EntryCodec.h"
#include "../../api/Entry/Entry.h"
#include "../../api/Entry/IntEntry.h"
#include "../../api/Entry/StringEntry.h"
#include "../../api/Entry/NullEntry.h"
#include "../../api/Entry/EntryType.h"
#include <sstream>
#include <string>
#include <memory>

using Object = std::unique_ptr<Entry>;
using Serial = std::vector<char>;
using namespace std;

// Convert an Entry object to vector<char>
Serial EntryCodec::encode(const Object& entry) const {
  // Create vector<char>
  std::vector<char> bytes;

  // Store type
  // 0 -> NULL_
  // 1 -> INTEGER
  // 2 -> TEXT
  EntryType type = entry->getType();
  bytes.emplace_back('0' + type);

  // Store value as list of chars
  if (type == EntryType::NULL_) {
    // Do not store anything
  } else if (type == EntryType::INTEGER) {
    const auto intEntry = static_cast<IntEntry*>(entry.get());
    const std::string value = std::to_string(intEntry->getVal());
    for (int i = 0; i < value.size(); ++i) {
      bytes.emplace_back(value[i]);
    }
  } else if (type == EntryType::TEXT) {
    const auto stringEntry = static_cast<StringEntry*>(entry.get());
    const std::string value = stringEntry->getVal();
    for (int i = 0; i < value.size(); ++i) {
      bytes.emplace_back(value[i]);
    }
  }

  return bytes;
}

// Convert a vector<char> to Entry object
Object EntryCodec::decode(const Serial& bytes) const {
  // Get type
  // 0 -> NULL_
  // 1 -> INTEGER
  // 2 -> TEXT
  int type = bytes[0] - '0';

  // Put chars into a stringstream
  std::stringstream ss;
  for (int i = 1; i < bytes.size(); ++i) {
    ss << bytes[i];
  }

  // Create Entry pointer
  std::unique_ptr<Entry> entry;
  switch(type) {
    case 0: // NULL_
      entry = std::make_unique<NullEntry>();
      break;
    
    case 1: // INTEGER
      entry = std::make_unique<IntEntry>(std::stoi(ss.str()));
      break;
    
    case 2: // TEXT
      entry = std::make_unique<StringEntry>(ss.str());
      break;
  }

  return entry;
}