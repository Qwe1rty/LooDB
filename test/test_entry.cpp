#include "../src/schema/api/Entry/Entry.h"
#include "../src/schema/api/Entry/IntEntry.h"
#include "../src/schema/api/Entry/StringEntry.h"
#include "../src/schema/api/Entry/NullEntry.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main() {
  unique_ptr<Entry> int1 = make_unique<IntEntry>(5);
  unique_ptr<Entry> int2 = make_unique<IntEntry>(5);
  unique_ptr<Entry> text1 = make_unique<StringEntry>("Hello");
  unique_ptr<Entry> text2 = make_unique<StringEntry>("World");
  unique_ptr<Entry> null1 = make_unique<NullEntry>();
  unique_ptr<Entry> null2 = make_unique<NullEntry>();

  // std::cerr << "int1 type: " << int1->getType() << endl;
  // std::cerr << "int2 type: " << int2->getType() << endl;
  // std::cerr << "int1 == int2: " << (*int1 == *int2) << endl;

  // std::cerr << "text1 type: " << text1->getType() << endl;
  // std::cerr << "text2 type: " << text2->getType() << endl;
  // std::cerr << "text1 == text2: " << (*text1 == *text2) << endl;

  // std::cerr << "null1 type: " << null1->getType() << endl;
  // std::cerr << "null2 type: " << null2->getType() << endl;
  // std::cerr << "null1 == null2: " << (*null1 == *null2) << endl;

  // std::cerr << "int1 == null1: " << (*int1 == *null1) << endl;
}