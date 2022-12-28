// Yusuf Pisan pisan@uw.edu
// 17 Jan 2021

// BST class
// Creates a BST to store values
// Uses Node which holds the data

#include "bstmap.h"
#include <cassert>

using namespace std;

// copy constructor
BSTMap::BSTMap(const BSTMap &bst) {
  if (bst.root == nullptr) {
    return;
  }
  root = new Node{bst.root->data, nullptr, nullptr};
  copy(bst.root, root);
}

// given an array of length n
// create a tree to have all items in that array
// with the minimum height (uses same helper as rebalance)
BSTMap::BSTMap(const vector<value_type> &v) {
  vector<value_type> vTree(v);
  sort(vTree.begin(), vTree.end(), sortByKey);
  root = buildTree(vTree, 0, vTree.size());
}

// sorts the BST by the key value
bool BSTMap::sortByKey(value_type &a, value_type &b) {
  return a.first < b.first;
}

// recursively builds the tree given a vector of values
BSTMap::Node *BSTMap::buildTree(const vector<value_type> &v, int start,
                                int end) {
  if (start < end) {
    int mid = (start + end) / 2;
    Node *newNode =
        new Node{v[mid], buildTree(v, start, mid), buildTree(v, mid + 1, end)};
    return newNode;
  }
  return nullptr;
}

// destructor
BSTMap::~BSTMap() { clear(); }

// delete all nodes in tree
void BSTMap::clear() {
  deleteNode(root);
  root = nullptr;
}

// true if no nodes in BST
bool BSTMap::empty() const { return root == nullptr; }

// Number of nodes in BST
int BSTMap::size() const { return findSize(root); }

// recursively finds the number of nodes in the BST
int BSTMap::findSize(Node *curr) {
  return curr == nullptr ? 0 : 1 + findSize(curr->left) + findSize(curr->right);
}

// true if item is in BST
bool BSTMap::contains(const key_type &key) const {
  Node *curr = root;
  while (curr != nullptr) {
    if (curr->data.first == key) {
      return true;
    }
    curr = curr->data.first < key ? curr->right : curr->left;
  }
  return false;
}

// If k matches the key returns a reference to its value
// If k does not match any key, inserts a new element
// with that key and returns a reference to its mapped value.
BSTMap::mapped_type &BSTMap::operator[](const key_type &k) {
  // assert(false && "operator[] has not been implemented");
  if (root == nullptr) {
    root = new Node{{k, 0}, nullptr, nullptr};
    return root->data.second;
  }
  Node *curr;
  Node *move = root;
  while (move != nullptr) {
    curr = move;
    if (curr->data.first == k) {
      return curr->data.second;
    }
    move = move->data.first < k ? move->right : move->left;
  }
  if (curr->data.first > k) {
    curr->left = new Node{{k, 0}, nullptr, nullptr};
    return curr->left->data.second;
  }
  curr->right = new Node{{k, 0}, nullptr, nullptr};
  return curr->right->data.second;
}

// gets all occurences of words with the prefix k
vector<BSTMap::value_type> BSTMap::getAll(const key_type &k) const {
  vector<value_type> v;
  findAll(k, v, root);
  return v;
}

// helper function to the getAll method
void BSTMap::findAll(const key_type &k, vector<value_type> &v, Node *curr) {
  if (curr != nullptr) {
    if (curr->data.first.substr(0, k.size()) == k) {
      v.push_back(curr->data);
    }
    findAll(k, v, curr->left);
    findAll(k, v, curr->right);
  }
}

// 0 if empty, 1 if only root, otherwise
// height of root is max height of subtrees + 1
int BSTMap::height() const { return getHeight(root); }

// height of a Node, nullptr is 0, root is 1, static, no access to 'this'
// helper function to height(), used by printVertical
int BSTMap::getHeight(const Node *n) {
  return n != nullptr ? 1 + int(fmax(getHeight(n->left), getHeight(n->right)))
                      : 0;
}

// same as contains, but returns 1 or 0
// compatibility with std::map
size_t BSTMap::count(const key_type &k) const { return contains(k) ? 1 : 0; }

// inorder traversal: left-root-right
// takes a function that takes a single parameter of type T
void BSTMap::inorder(void visit(const value_type &item)) const {
  inOrderTraverse(visit, root);
}

// traverses the BST in the inOrderTraversal
void BSTMap::inOrderTraverse(void visit(const value_type &item), Node *curr) {
  if (curr != nullptr) {
    inOrderTraverse(visit, curr->left);
    visit(curr->data);
    inOrderTraverse(visit, curr->right);
  }
}

// preorder traversal: root-left-right
void BSTMap::preorder(void visit(const value_type &item)) const {
  preOrderTraverse(visit, root);
}

// traverses the BST in the preOrderTraversal
void BSTMap::preOrderTraverse(void visit(const value_type &item), Node *curr) {
  if (curr != nullptr) {
    visit(curr->data);
    preOrderTraverse(visit, curr->left);
    preOrderTraverse(visit, curr->right);
  }
}

// postorder traversal: left-right-root
void BSTMap::postorder(void visit(const value_type &item)) const {
  postOrderTraverse(visit, root);
}

// traverses the BST in the postOrderTraversal
void BSTMap::postOrderTraverse(void visit(const value_type &item), Node *curr) {
  if (curr != nullptr) {
    postOrderTraverse(visit, curr->left);
    postOrderTraverse(visit, curr->right);
    visit(curr->data);
  }
}

// balance the BST by saving all nodes to a vector inorder
// and then recreating the BST from the vector
void BSTMap::rebalance() {
  vector<Node *> nodes;
  rebalanceVector(nodes, root);
  root = rebalanceTree(nodes, 0, nodes.size());
}

// structures a balanced BSTMap with a given vector of Nodes
BSTMap::Node *BSTMap::rebalanceTree(vector<Node *> &nodes, int start, int end) {
  if (start < end) {
    int mid = (start + end) / 2;
    nodes[mid]->left = rebalanceTree(nodes, start, mid);
    nodes[mid]->right = rebalanceTree(nodes, mid + 1, end);
    return nodes[mid];
  }
  return nullptr;
}

// generates a vector of the BSTMap's Nodes inorder
void BSTMap::rebalanceVector(vector<Node *> &nodes, Node *curr) {
  if (curr != nullptr) {
    rebalanceVector(nodes, curr->left);
    nodes.push_back(curr);
    rebalanceVector(nodes, curr->right);
  }
}

// trees are equal if they have the same structure
// AND the same item values at all the nodes
bool BSTMap::operator==(const BSTMap &other) const {
  return sameTree(other.root, root);
}

// helper method for the != operator, recursively checks if two trees are equal
bool BSTMap::sameTree(Node *other, Node *our) {
  if (other == nullptr && our == nullptr) {
    return true;
  }
  if (other == nullptr || our == nullptr) {
    return false;
  }
  return (other->data == our->data) && sameTree(other->left, our->left) &&
         sameTree(other->right, our->right);
}

// not == to each other
bool BSTMap::operator!=(const BSTMap &other) const {
  return !sameTree(other.root, root);
}

// recursive copy constructor helper method
void BSTMap::copy(Node *from, Node *to) {
  if (from->left != nullptr) {
    Node *left = new Node;
    to->left = left;
    to->left->data = from->left->data;
    copy(from->left, to->left);
  } else {
    to->left = nullptr;
  }
  if (from->right != nullptr) {
    Node *right = new Node;
    to->right = right;
    to->right->data = from->right->data;
    copy(from->right, to->right);
  } else {
    to->right = nullptr;
  }
}

// recursively deletes nodes
void BSTMap::deleteNode(Node *curr) {
  if (curr != nullptr) {
    deleteNode(curr->left);
    deleteNode(curr->right);
    delete curr;
  }
}

// returns true if item successfully erased
bool BSTMap::erase(const key_type &k) {
  Node *parent = nullptr;
  Node *curr = root;
  while (curr != nullptr) {
    if (curr->data.first == k) {
      break;
    }
    parent = curr;
    curr = curr->data.first < k ? curr->right : curr->left;
  }
  if (curr == nullptr) {
    return false;
  }
  chooseErase(parent, curr);
  return true;
}

// helper function for the erase method to choose which
// erase case to execute
void BSTMap::chooseErase(Node *parent, Node *curr) {
  if (curr->left == nullptr && curr->right == nullptr) {
    noChildErase(parent, curr);
  } else if (curr->left != nullptr && curr->right == nullptr) {
    leftChildErase(parent, curr);
  } else if (curr->left == nullptr && curr->right != nullptr) {
    rightChildErase(parent, curr);
  } else {
    bothChildErase(curr);
  }
}

// helper function for the Erase method which deals with having no children
void BSTMap::noChildErase(Node *parent, Node *curr) {
  if (parent == nullptr) {
    root = nullptr;
  } else {
    if (parent->left == curr) {
      parent->left = nullptr;
    } else {
      parent->right = nullptr;
    }
  }
  delete curr;
}

// helper function for Erase method which deals with having left child
void BSTMap::leftChildErase(Node *parent, Node *curr) {
  if (parent == nullptr) {
    root = curr->left;
  } else {
    if (parent->left == curr) {
      parent->left = curr->left;
    } else {
      parent->right = curr->left;
    }
  }
  curr->left = nullptr;
  delete curr;
}

// helper function for Erase method which deals with having only a right child
void BSTMap::rightChildErase(Node *parent, Node *curr) {
  if (parent == nullptr) {
    root = curr->right;
  } else {
    if (parent->left == curr) {
      parent->left = curr->right;
    } else {
      parent->right = curr->right;
    }
  }
  curr->right = nullptr;
  delete curr;
}

// helper function for Erase method which deals with having 2 children
void BSTMap::bothChildErase(Node *curr) {
  Node *lowestParent = curr;
  Node *lowest = curr->right;
  while (lowest->left != nullptr) {
    lowestParent = lowest;
    lowest = lowest->left;
  }
  curr->data = lowest->data;
  chooseErase(lowestParent, lowest);
}