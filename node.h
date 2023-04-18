// Node class for Red Black Tree.

#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

class Node {
 public:
 
 // constructor and destructor
  Node(int myValue);
  ~Node();
 
 // getters
  int getValue();
  Node* getLeft();
  Node* getRight();
  Node* getParent();
  int getColor();
 
 // setters
  void setRight(Node* right);
  void setLeft(Node* left);
  void setParent(Node* newParent);
  void setValue(int myValue);
  void setColor(int newColor);
 private:
 
 // node data
  Node* rightChild;
  Node* leftChild;
  Node* parent;
  // red is 0, black is 1
  int color;
  int value;
};
#endif
