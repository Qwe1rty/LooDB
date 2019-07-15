#include "../../api/Entry/Entry.h"
#include "../../api/Entry/IntEntry.h"
#include "../../api/Entry/StringEntry.h"
#include "../../api/Entry/NullEntry.h"
#include "../../api/Entry/EntryCodec.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>

using namespace std;

void test_entry_equality() {
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
}

void test_entry_vectors() {
  unique_ptr<Entry> int1 = make_unique<IntEntry>(5);
  unique_ptr<Entry> int2 = make_unique<IntEntry>(5);
  unique_ptr<Entry> text1 = make_unique<StringEntry>("Hello");
  unique_ptr<Entry> text2 = make_unique<StringEntry>("World");
  unique_ptr<Entry> null1 = make_unique<NullEntry>();
  unique_ptr<Entry> null2 = make_unique<NullEntry>();

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

void test_entrycodec() {
  EntryCodec CODEC = EntryCodec();

  unique_ptr<Entry> null3 = make_unique<NullEntry>();
  vector<char> encoded_null3 = CODEC.encode(null3);
  for (int i = 0; i < encoded_null3.size(); ++i) {
    cout << encoded_null3[i];
  }
  cout << endl;
  unique_ptr<Entry> decoded_null3 = CODEC.decode(encoded_null3);
  cout << "null3 == decoded_null3: " << (*null3 == *decoded_null3) << endl;

  unique_ptr<Entry> int3 = make_unique<IntEntry>(-1234);
  vector<char> encoded_int3 = CODEC.encode(int3);
  for (int i = 0; i < encoded_int3.size(); ++i) {
    cout << encoded_int3[i];
  }
  cout << endl;
  unique_ptr<Entry> decoded_int3 = CODEC.decode(encoded_int3);
  cout << "int3 == decoded_int3: " << (*int3 == *decoded_int3) << endl;

  unique_ptr<Entry> text3 = make_unique<StringEntry>("Aloha");
  vector<char> encoded_text3 = CODEC.encode(text3);
  for (int i = 0; i < encoded_text3.size(); ++i) {
    cout << encoded_text3[i];
  }
  cout << endl;
  unique_ptr<Entry> decoded_text3 = CODEC.decode(encoded_text3);
  cout << "text3 == decoded_text3: " << (*text3 == *decoded_text3) << endl;
}

int main() {
  
  test_entry_equality();

  test_entry_vectors();

  test_entrycodec();
}