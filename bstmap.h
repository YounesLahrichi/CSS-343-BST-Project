// Yusuf Pisan pisan@uw.edu
// 15 Jan 2018

// BST class
// Creates a BST to store values
// Uses Node which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef BSTMAP_H
#define BSTMAP_H

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class BSTMap {

  // display BST tree in a human-readable format
  // comment out printSideways or printVertical
  friend ostream &operator<<(ostream &out, const BSTMap &bst);

public:
  using key_type = string;
  using mapped_type = uint64_t;
  using value_type = pair<key_type, mapped_type>;

  // constructor, empty tree
  BSTMap() = default;

  // copy constructor
  BSTMap(const BSTMap &bst);

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (uses same helper as rebalance)
  explicit BSTMap(const vector<value_type> &v);

  // destructor
  virtual ~BSTMap();

  // move not allowed
  BSTMap(BSTMap &&other) = delete;

  // assignment not allowed
  BSTMap &operator=(const BSTMap &other) = delete;

  // move assignment not allowed
  BSTMap &operator=(BSTMap &&other) = delete;

  // true if no nodes in BST
  bool empty() const;

  // Number of nodes in BST
  int size() const;

  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int height() const;

  // delete all nodes in tree
  void clear();

  // true if item is in BST
  bool contains(const key_type &key) const;

  // same as contains, but returns 1 or 0
  // compatibility with std::map
  size_t count(const key_type &k) const;

  // If k matches the key returns a reference to its value
  // If k does not match any key, inserts a new element
  // with that key and returns a reference to its mapped value.
  mapped_type &operator[](const key_type &k);

  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void inorder(void visit(const value_type &item)) const;

  // preorder traversal: root-left-right
  void preorder(void visit(const value_type &item)) const;

  // postorder traversal: left-right-root
  void postorder(void visit(const value_type &item)) const;

  // balance the BST by saving all nodes to a vector inorder
  // and then recreating the BST from the vector
  void rebalance();

  // returns true if item successfully erased - BONUS
  bool erase(const key_type &k);

  //gets all occurences of words with the prefix k
  vector<value_type> getAll(const key_type &k) const;

  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BSTMap &other) const;

  // not == to each other
  bool operator!=(const BSTMap &other) const;

private:
  // Node for BST
  struct Node {
    // key-value pair
    value_type data;
    // children
    struct Node *left;
    struct Node *right;
  };

  // refer to data type "struct Node" as Node
  using Node = struct Node;

  // print Node
  friend ostream &operator<<(ostream &out, const Node &n);

  // root of the tree
  Node *root{nullptr};

  // recursively builds the tree given a vector of values
  static Node *buildTree(const vector<value_type>& v, int start, int end);

  // print tree sideways with root on left
  static ostream &printSideways(ostream &out, const Node *curr, int level = 0);

  // helper for printVertical
  static ostream &centeredPrint(ostream &out, int space, const string &str,
                                char fillChar = ' ');

  // print tree with the root at top
  static ostream &printTreeLevel(ostream &out, queue<const Node *> &q,
                                 int width, int depth, int maxDepth);

  // helper function for displaying tree sideways, works recursively
  static ostream &printVertical(ostream &out, Node *curr);

  // height of a Node, nullptr is 0, root is 1, static, no access to 'this'
  // helper function to height(), used by printVertical
  static int getHeight(const Node *n);

  // recursively finds the number of nodes in the BST
  static int findSize(Node* curr);

  // helper function to the getAll method
  static void findAll(const key_type &k, vector<value_type> &v, Node* curr);

  // recursively deletes nodes
  static void deleteNode(Node* curr);

  // recursive copy constructor helper method
  static void copy(Node *from, Node *to);

  // generates a vector of the BSTMap's Nodes inorder
  static void rebalanceVector(vector<Node*>& nodes, Node* curr);
  
  // structures a balanced BSTMap with a given vector of Nodes
  static Node* rebalanceTree(vector<Node*>& nodes, int start, int end);

  // traverses the BST in the postOrderTraversal
  static void postOrderTraverse(void visit(const value_type &item), Node* curr);

  // traverses the BST in the preOrderTraversal
  static void preOrderTraverse(void visit(const value_type &item), Node* curr);

  // traverses the BST in the inOrderTraversal
  static void inOrderTraverse(void visit(const value_type &item), Node* curr);

  // helper method for the != operator, recursively checks if two trees are equal
  static bool sameTree(Node* other, Node* our);

  // sorts the BST by the key value
  static bool sortByKey(value_type &a, value_type &b);

  // helper function for the Erase method which deals with having no children
  void noChildErase(Node* parent, Node* curr);

  // helper function for the Erase method which deals with having 2 children
  void bothChildErase(Node* curr);

  // helper function for the Erase method which deals with having only a right child
  void rightChildErase(Node* parent, Node* curr);

  // helper function for the Erase method which deals with having left child
  void leftChildErase(Node* parent, Node* curr);

  // helper function for the erase method to choose a node to erase
  void chooseErase(Node* parent, Node* curr);
};

#endif // BSTMAP_H
