#include "autocomplete.h"
#include <fstream>

using namespace std;

void testBSTAll();

// reads a file of String and int values into phrases
void Autocomplete::readFile(const string &fileName) {
  ifstream ifs(fileName);
  int n;
  string key;
  uint64_t value;
  ifs >> n;
  getline(ifs, key);
  for (int i = 0; i < n; i++) {
    ifs >> value;
    ifs.ignore();
    getline(ifs, key);
    phrases[key] = value;
  }
  ifs.close();
  phrases.rebalance();
}
// sorter
bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// generates a vector of values from phrases that have the
// given prefix, sorted by weight
vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  vector<BSTMap::value_type> v = phrases.getAll(prefix);
  sort(v.begin(), v.end(), sortByWeight);
  return v;
}
