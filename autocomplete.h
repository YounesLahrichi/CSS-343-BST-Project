#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "bstmap.h"

class Autocomplete {
public:
  // defeault constructor
  Autocomplete() = default;

  // reads a file of String and int values into phrases
  void readFile(const string &fileName);

  // generates a vector of values from phrases that have the
  // given prefix, sorted by weight
  vector<BSTMap::value_type> complete(const string &prefix) const;

private:
  // BST of phrases and their frequency
  BSTMap phrases;

  // sorter
  bool static sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b);
};

#endif // AUTOCOMPLETE_H
