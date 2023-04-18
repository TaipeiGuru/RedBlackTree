// This is the Red Black Tree project, which sorts integer values into a binary tree following RBT properties. Last modified by Jason Randolph on 4-7-23.

// Imports
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctype.h>
#include <cmath>
#include "node.h"

using namespace std;

// Function prototypes
void addValue(Node* &treeRoot, int value);
void fixTree(Node* &newNode, Node* &treeRoot);
void printTree(Node* treeRoot, int tabCounter);
void read(Node* &treeRoot);
void search(Node* treeRoot, int value);
void remove(Node* &treeRoot, int value);

int main() { 
  
	// Initializing variables
  Node* treeRoot = NULL;
  char input[20];

  cout << "Welcome to Red Black Tree!" << endl;
  
  // Standard repeating message sequence using bool and while loop.
  bool active = true;
  while(active == true) {
    cout << "\nPlease input a command below. You may \"ADD,\" \"READ,\" \"PRINT,\" \"SEARCH,\" and \"QUIT.\"" << endl;
    cin.get(input, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if(strcmp(input, "ADD") == 0) {
      int num;
      cout << "\nEnter a number: " << endl;
      cin >> num;
      cin.clear();
      cin.ignore(10000, '\n');
      addValue(treeRoot, num);
      cout << "\nYour number has been added." << endl;
    } else if(strcmp(input, "READ") == 0) {
      read(treeRoot);
      cout << "\nYour number(s) have been added." << endl;
    } else if(strcmp(input, "PRINT") == 0) {
      printTree(treeRoot, 0);
    } else if(strcmp(input, "SEARCH") == 0) {
	    int num;
      cout << "\nEnter a number: " << endl;
      cin >> num;
      cin.clear();
      cin.ignore(10000, '\n');
      search(treeRoot, num);
    } else if(strcmp(input, "QUIT") == 0) {
      active = false;
    } else {
      cout << "\nSorry, invalid input." << endl; 
    }
  }
  return 0;
}

void search(Node* treeRoot, int value) {
  if(treeRoot == NULL) {
    cout << "The value " << value << " is not in the tree." << endl;
  } else {
    if(treeRoot->getValue() == value) {
      cout << "The value " << value << " exists in this tree." << endl; 
    } else {
      if(value > treeRoot->getValue()) {
        search(treeRoot->getRight(), value); 
      } else { 
        search(treeRoot->getLeft(), value); 
      }
    }
  }
}

// fix tree function. Checks for 4 cases (root = NULL is checked in the add function). 
void fixTree(Node* &newNode, Node* &treeRoot) {
  // initialize parent. If the parent is NULL, the node must be the root and is set to black. Otherwise, parent is set to the node's parent.
  Node* parent = NULL;
  if(newNode->getParent() == NULL) {
    newNode->setColor(1);
    return;
  } else {
    parent = newNode->getParent();
  }
  
  // initialize grandparent, check for NULL and set to grandparent if otherwise
  Node* grandParent = NULL;
  if(parent != NULL && parent->getParent() != NULL) {
    grandParent = parent->getParent();
  }
  
  // initialize uncle. Check to see which side the node is coming from so that the uncle is set to the appropriate node
  Node* uncle = NULL;
  if(parent != NULL && grandParent != NULL) {
    if(parent->getValue() < grandParent->getValue()) {
      uncle = grandParent->getRight();
    } else {  
      uncle = grandParent->getLeft();
    }
  }
  
  // case 2: parent is black. No action needed so function ends
  if(parent != NULL) {
    if(parent->getColor() == 1) {
      return;
    }
  }
  
  // cases 3-5 are broken into 2 if statements, with the primary difference being whether uncle = NULL or not. This matters since NULL = black in a RBT
  if(parent != NULL && grandParent != NULL && uncle != NULL) {
    
    // case 3: parent and uncle are red. 
    if(uncle->getColor() == 0 && parent->getColor() == 0) {
      
      // change parent and uncle to red
      grandParent->getLeft()->setColor(1);
      grandParent->getRight()->setColor(1);
      
      // change grandparent to black
      grandParent->setColor(0);
      
      // recursively call on grandparent
      fixTree(grandParent, treeRoot);
    
    // case 4: uncle is black, node is right and parent is left
    } else if(newNode->getValue() >= parent->getValue() && parent->getValue() < grandParent->getValue() && uncle->getColor() == 1) {
      
      // tree rotation through parent
      newNode->setParent(grandParent);
      grandParent->setLeft(newNode);
      if(newNode->getLeft() != NULL) {
	      newNode->getLeft()->setParent(parent);
	      parent->setRight(newNode->getLeft());
      } else {
	      parent->setRight(NULL);
      }
      parent->setParent(newNode);
      newNode->setLeft(parent);
      fixTree(parent, treeRoot);
      
    // case 5: uncle is black, node is left, parent is left
    } else if(newNode->getValue() < parent->getValue() && parent->getValue() < grandParent->getValue() && uncle->getColor() == 1) {
      
      // switch colors
      grandParent->setColor(0);
      parent->setColor(1);
      
      // tree rotation through grandparent
      if(parent->getRight() != NULL) {
	      grandParent->setLeft(parent->getRight());
	      parent->getRight()->setParent(grandParent);
      } else {
        grandParent->setLeft(NULL);
      }
      parent->setRight(grandParent);
      if(grandParent->getParent() != NULL) {
        parent->setParent(grandParent->getParent());
        if(parent->getValue() < grandParent->getParent()->getValue()) {
          grandParent->getParent()->setLeft(parent);
        } else {
          grandParent->getParent()->setRight(parent);
        }
      } else {
        
        // reset treeRoot if the parent is NULL
        parent->setParent(NULL);
        treeRoot = parent;
      }
      grandParent->setParent(parent);
      
    // case 4: same case 4 as above, except switched (node is left and parent is right)
    } else if(newNode->getValue() < parent->getValue() && parent->getValue() >= grandParent->getValue() && uncle->getColor() == 1) {
      newNode->setParent(grandParent);
      grandParent->setRight(newNode);
      if(newNode->getRight() != NULL) {
	      newNode->getRight()->setParent(parent);
	      parent->setLeft(newNode->getRight());
      } else {
	      parent->setLeft(NULL);
      }
      parent->setParent(newNode);
      newNode->setRight(parent);
      fixTree(parent, treeRoot);
    
    // case 5: same case 5 as above, except switched (node is right and parent is right)
    } else if(newNode->getValue() >= parent->getValue() && parent->getValue() >= grandParent->getValue()) {
      grandParent->setColor(0);
      parent->setColor(1);
      if(parent->getLeft() != NULL) {
        grandParent->setRight(parent->getLeft());
        parent->getLeft()->setParent(grandParent);
      } else {
        grandParent->setRight(NULL);
      }
      parent->setLeft(grandParent);
      if(grandParent->getParent() != NULL) {
        parent->setParent(grandParent->getParent());
        if(parent->getValue() < grandParent->getParent()->getValue()) {
          grandParent->getParent()->setLeft(parent);
        } else {
          grandParent->getParent()->setRight(parent);
        }
      } else {
        parent->setParent(NULL);
        treeRoot = parent;
      }
      grandParent->setParent(parent);
    }
    
  // this else statement accounts for the possibility of uncle being NULL. Exact same code as above except it doesn't check for uncle's properties as that would seg fault
  } else if(parent != NULL && grandParent != NULL && uncle == NULL) {
    if(newNode->getValue() >= parent->getValue() && parent->getValue() < grandParent->getValue()) {
      newNode->setParent(grandParent);
      grandParent->setLeft(newNode);
      if(newNode->getLeft() != NULL) {
        newNode->getLeft()->setParent(parent);
        parent->setRight(newNode->getLeft());
      } else {
	      parent->setRight(NULL);
      }
      parent->setParent(newNode);
      newNode->setLeft(parent);
      fixTree(parent, treeRoot);
    } else if(newNode->getValue() < parent->getValue() && parent->getValue() < grandParent->getValue()) {
      grandParent->setColor(0);
      parent->setColor(1);
      if(parent->getRight() != NULL) {
        grandParent->setLeft(parent->getRight());
        parent->getRight()->setParent(grandParent);
      } else {
        grandParent->setLeft(NULL);
      }
      parent->setRight(grandParent);
      if(grandParent->getParent() != NULL) {
        parent->setParent(grandParent->getParent());
        if(parent->getValue() < grandParent->getParent()->getValue()) {
          grandParent->getParent()->setLeft(parent);
        } else {
          grandParent->getParent()->setRight(parent);
        }
      } else {
        parent->setParent(NULL);
        treeRoot = parent;
      }
      grandParent->setParent(parent);
    } else if(newNode->getValue() < parent->getValue() && parent->getValue() >= grandParent->getValue()) {
      newNode->setParent(grandParent);
      grandParent->setRight(newNode);
      if(newNode->getRight() != NULL) {
        newNode->getRight()->setParent(parent);
        parent->setLeft(newNode->getRight());
      } else {
        parent->setLeft(NULL);
      }
      parent->setParent(newNode);
      newNode->setRight(parent);
      fixTree(parent, treeRoot);
    } else if(newNode->getValue() >= parent->getValue() && parent->getValue() >= grandParent->getValue()) {
      grandParent->setColor(0);
      parent->setColor(1);
      if(parent->getLeft() != NULL) {
        grandParent->setRight(parent->getLeft());
        parent->getLeft()->setParent(grandParent);
      } else {
        grandParent->setRight(NULL);
      }
      parent->setLeft(grandParent);
      if(grandParent->getParent() != NULL) {
        parent->setParent(grandParent->getParent());
        if(parent->getValue() < grandParent->getParent()->getValue()) {
          grandParent->getParent()->setLeft(parent);
        } else {
          grandParent->getParent()->setRight(parent);
        }
      } else {
        parent->setParent(NULL);
        treeRoot = parent;
      }
      grandParent->setParent(parent);
    }
  }
}

// Add value function
void addValue(Node* &treeRoot, int value) {
  
  // parent node used to keep track of "previous" node
  Node* current = treeRoot;
  Node* parent = treeRoot;
  
  // If tree is empty, set to root
  if(treeRoot == NULL) {
    Node* newNode = new Node(value);
    newNode->setParent(NULL);
    newNode->setColor(1);
    treeRoot = newNode;
    
    // same logic as in BST: figure out which direction to add, recursion, and then set connections to parent/child
  } else {
    while(current != NULL) {
      parent = current;
      if(value >= current->getValue()) {
        current = current->getRight(); 
      } else {
        current = current->getLeft();
      }
    }
    Node* newNode = new Node(value);
    newNode->setParent(parent);
    if(parent->getValue() <= value) {
      parent->setRight(newNode); 
    } else {
      parent->setLeft(newNode);
    }
    
    // fix tree after each number is added
    fixTree(newNode, treeRoot);
  }
}


// Adding from a file. Same logic as in BST
void read(Node* &treeRoot) {
  
  // The file name is entered and then a file with that name is opened.
  cout << "Please enter the name of your file:" << endl;
  char input[20];
  cin >> input;
  cin.ignore(10000, '\n');
  ifstream numFile;
  numFile.open(input);
  int num;
  
  // While the file is open, take in the first number. Cin separates by whitespace so no additional work needed. 
  if(numFile.is_open() == true) {
    
    // Repeat while numbers are left in the file (help with this from Galbraith).
    while(numFile >> num) {   
      
      // Insert that number into the tree.
      addValue(treeRoot, num);
    }
  }
  
  // Close file.
  numFile.close();
}

// print Tree function. Same logic as in BST
void printTree(Node* treeRoot, int tabCounter) {
  // If there isn't any data in the tree, end the function.
  if (treeRoot == NULL) {
    return;
  }
    // Otherwise, increase the horizontal distance using a tab counter.
  tabCounter++;
 
  // Display the right child first
  printTree(treeRoot->getRight(), tabCounter);
 
  // Add a new line and then the appropriate number of spaces depending on which generation it is (hence the use of the tab counter).
  cout << endl;
  for (int i = 1; i < tabCounter; i++) {
    cout << "\t";
  }
  
  // Enter the value at that node.
 	cout << treeRoot->getValue();
  
  // Get color value and output a letter based on the int value
  if(treeRoot->getColor() == 1) {
    cout << " (B)" << endl; 
  } else {
    cout << " (R)" << endl;
  }
	
  // Then, display the left child
  printTree(treeRoot->getLeft(), tabCounter);
}
