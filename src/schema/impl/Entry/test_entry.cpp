#include "../../api/Entry/Entry.h"
#include "../../api/Entry/IntEntry.h"
#include "../../api/Entry/StringEntry.h"
#include "../../api/Entry/NullEntry.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>

using namespace std;

int main() {
  unique_ptr<Entry> int1 = make_unique<IntEntry>(5);
  unique_ptr<Entry> int2 = make_unique<IntEntry>(5);
  unique_ptr<Entry> text1 = make_unique<StringEntry>("Hello");
  unique_ptr<Entry> text2 = make_unique<StringEntry>("World");
  unique_ptr<Entry> null1 = make_unique<NullEntry>();
  unique_ptr<Entry> null2 = make_unique<NullEntry>();

  cout << "int1 type: " << int1->getType() << endl;
  cout << "int2 type: " << int2->getType() << endl;
  cout << "int1 == int2: " << (*int1 == *int2) << endl;

  cout << "text1 type: " << text1->getType() << endl;
  cout << "text2 type: " << text2->getType() << endl;
  cout << "text1 == text2: " << (*text1 == *text2) << endl;

  cout << "null1 type: " << null1->getType() << endl;
  cout << "null2 type: " << null2->getType() << endl;
  cout << "null1 == null2: " << (*null1 == *null2) << endl;

  cout << "int1 == null1: " << (*int1 == *null1) << endl;

  vector<unique_ptr<Entry>> entries;

  entries.emplace_back(move(int1));
  entries.emplace_back(move(int2));
  entries.emplace_back(move(text1));
  entries.emplace_back(move(text2));
  entries.emplace_back(move(null1));
  entries.emplace_back(move(null2));

  for (int i = 0; i < entries.size(); ++i) {
    cout << entries[i]->getType() << endl;
  }

  vector<vector<unique_ptr<Entry>>> entries2;

  entries2.emplace_back(move(entries));

  vector<vector<unique_ptr<Entry>>> entries3;

  entries3 = move(entries2);
}