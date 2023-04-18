// Node CPP files for Red Black Tree.

#include "node.h"
#include <iostream>

using namespace std;

Node::Node(int myValue) {
  // two child pointers, value, and a color. 0 is red, 1 is black
  leftChild = NULL;
  rightChild = NULL;
  value = myValue;
  
  // set all nodes to red initially
  color = 0;
}

Node::~Node() {
  leftChild = NULL;
  rightChild = NULL;
}

// Getters
int Node::getValue() {
  return value;
}

Node* Node::getRight() {
  return rightChild; 
}

Node* Node::getLeft() {
  return leftChild; 
}

Node* Node::getParent() {
  return parent; 
}

int Node::getColor() {
  return color;
}

// Setters
void Node::setRight(Node* right) {
  rightChild = right; 
}

void Node::setLeft(Node* left) {
  leftChild = left; 
}

void Node::setParent(Node* newParent) {
  parent = newParent;
}

void Node::setValue(int myValue) {
  value = myValue; 
}

void Node::setColor(int newColor) {
  color = newColor;
} 
