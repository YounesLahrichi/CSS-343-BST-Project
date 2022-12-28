# autocomplete

Use a Binary Search Tree to store key-value pairs where the values represent the frequency of keys (cities, words, movie names, etc)

Traverse the BST to find all entries that match the given prefix. Sort them by weight

### cpp files

- bstmap.h/cpp: Binary Search Tree header and implementation
- bstmapprinter.cpp: Functions for printing BST on screen
- autocomple.h/cpp: Autocomplete
- testbst.cpp: Testing BST functions
- testac.cpp: Testing Autocomplete functions
- main.cpp: Accepts inputs to return strings sorted by their frequency

### Text files for testing
- small.txt Short list of words
- wiktionary.txt Large list of words
- cities.txt Cities

### Shell scripts

- runit.sh: compile and run he program
- create-output.sh: compile, run, check for clang-tidy, clang-format and valgrind warnings
- check-code-coverage: examine if any lines not executed during tests

### Disabled checks
- cppcoreguidelines-pro-type-member-init, -hicpp-member-init: causing warnings with the struct Node left and
  right pointers not being initialized in the struct. We attempted to fix the issue by
  initializing the values in the struct to nullptr (i.e. Node* right = nullptr), but that
  caused issues with the way we were initiliazing the Nodes in the bstmap.cpp file. Lastly
  to fix the new errors, we attempted to add a constructor as the error results called for, this
  only caused more errors and so we opted to disable the check since the warning was "warning"
  of an issue that would never be a problem in the code since a Node is neveer being created
  without its pointers being set.

