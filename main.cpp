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
void fixTreeDeleteLeft(Node* &current, Node* &treeRoot);
void fixTreeDeleteRight(Node* &current, Node* &treeRoot);
void printTree(Node* treeRoot, int tabCounter);
void read(Node* &treeRoot);
void search(Node* treeRoot, int value);
void remove(Node* &inputNode, int value, Node* &treeRoot);

int main() { 
  
  // Initializing variables
  Node* treeRoot = NULL;
  char input[20];

  cout << "Welcome to Red Black Tree!" << endl;
  // Standard repeating message sequence using bool and while loop.
  bool active = true;
  while(active == true) {
    cout << "\nPlease input a command below. You may \"ADD,\" \"READ,\" \"PRINT,\" \"SEARCH,\" \"DELETE,\" and \"QUIT.\"" << endl;
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
      if(treeRoot == NULL) {
	      cout << "There's nothing in the tree to print." << endl;
      } else { 
	      printTree(treeRoot, 0);
      }
    } else if(strcmp(input, "SEARCH") == 0) {
      if(treeRoot == NULL) {
	      cout << "There's nothing in the tree to search." << endl;
      } else {
	    int num;
      cout << "\nEnter a number: " << endl;
      cin >> num;
      cin.clear();
      cin.ignore(10000, '\n');
      search(treeRoot, num);
      }
    } else if(strcmp(input, "DELETE") == 0) {
      if(treeRoot == NULL) {
	      cout << "There's nothing in the tree to print." << endl;
      } else { 
        int num;
        cout << "What number would you like to delete?" << endl;
        cin >> num;
        cin.clear();
        cin.ignore(10000, '\n');
        remove(treeRoot, num, treeRoot);
      }
    } else if(strcmp(input, "QUIT") == 0) {
      active = false;
    } else {
      cout << "\nSorry, invalid input." << endl; 
    }
  }
  return 0;
}

void fixTreeDeleteLeft(Node* &current, Node* &treeRoot) {
  Node* parent = NULL;
  if(current->getParent() != NULL) {
    parent = current->getParent(); 
  }
  Node* sibling = NULL;
  if(parent != NULL) {
    if(parent->getRight() != NULL) {
      sibling = current->getParent()->getRight(); 
    }
  }
  // case 1
  if(parent == NULL) {
    return;
  }
  if(sibling != NULL) {
    // case 2
    if(sibling->getColor() == 0) {
      if(sibling->getLeft() != NULL) {
        parent->setRight(sibling->getLeft());
        sibling->getLeft()->setParent(parent);
      }
      sibling->setParent(parent->getParent());
      if(sibling->getValue() < parent->getParent()->getValue()) {
        parent->getParent()->setLeft(sibling); 
      } else {
        parent->getParent()->setRight(sibling); 
      }
      sibling->setLeft(parent);
      parent->setParent(sibling);
      int color = parent->getColor();
      parent->setColor(sibling->getColor());
      sibling->setColor(color);
      fixTreeDeleteLeft(current, treeRoot);
      // case 3
    } else if(sibling->getColor() + parent->getColor() == 2 && sibling->getLeft() != NULL && sibling->getRight() != NULL) {
      if(sibling->getLeft()->getColor() == 1 && sibling->getRight()->getColor() == 1) {
        sibling->setColor(0);
        fixTreeDeleteLeft(parent, treeRoot);
      }
    }
    // case 3 but with NULL children
    if(sibling->getColor() + parent->getColor() == 2 && sibling->getLeft() == NULL && sibling->getRight() == NULL) {
      sibling->setColor(0);
      fixTreeDeleteLeft(parent, treeRoot);
    }
    // case 4
    if(sibling->getRight() != NULL && sibling->getLeft() != NULL) {
      if(parent->getColor() == 0 && sibling->getColor() + sibling->getRight()->getColor() + sibling->getLeft()->getColor() == 3) {
        parent->setColor(1);
        sibling->setColor(0);
	      return;
      }
      // case 4 but with NULL children
    }
    if(sibling->getLeft() == NULL && sibling->getRight() == NULL && parent->getColor() == 0 && sibling->getColor() == 1) {
      parent->setColor(1);
      sibling->setColor(0);
      // case 5
      return;
    }
    // case 5
    if(sibling->getRight() != NULL && sibling->getLeft() != NULL) {
      if(sibling->getColor() + sibling->getRight()->getColor() == 2 && sibling->getLeft()->getColor() == 0 && current->getValue() < parent->getValue()) {
        parent->setRight(sibling->getLeft());
        sibling->getLeft()->setParent(parent);
        if(sibling->getLeft()->getRight() != NULL) {
          sibling->getLeft()->getRight()->setParent(sibling);
          sibling->setLeft(sibling->getLeft()->getRight());
        }
        parent->getRight()->setRight(sibling);
        sibling->setParent(parent->getRight());
        sibling->setColor(0);
        sibling->getParent()->setColor(1);
      }
     // case 5 but with NULL children
    } else if(sibling->getRight() == NULL && sibling->getLeft() != NULL) {
      if(sibling->getColor() == 1 && sibling->getLeft()->getColor() == 0 && current->getValue() < parent->getValue()) {
        parent->setRight(sibling->getLeft());
        sibling->getLeft()->setParent(parent);
        if(sibling->getLeft()->getRight() != NULL) {
          sibling->getLeft()->getRight()->setParent(sibling);
          sibling->setLeft(sibling->getLeft()->getRight());
        }
        parent->getRight()->setRight(sibling);
        sibling->setParent(parent->getRight());
        sibling->setColor(0);
        sibling->getParent()->setColor(1);
      }
    }
    // case 6
    if(sibling->getRight() != NULL) {
      if(sibling->getColor() == 1 && sibling->getRight()->getColor() == 0 && current->getValue() < parent->getValue()){
        if(parent->getParent() == NULL) {
          sibling->setParent(NULL);
          treeRoot = sibling;
        } else {
	        if(parent->getValue() < parent->getParent()->getValue()) {
            parent->getParent()->setLeft(sibling); 
          } else {
            parent->getParent()->setRight(sibling);
          }
          sibling->setParent(parent->getParent());
        }
        if(sibling->getLeft() != NULL) {
          sibling->getLeft()->setParent(parent);
          parent->setRight(sibling->getLeft());
        } else {
          parent->setRight(NULL);
        }
        parent->setParent(sibling);
        sibling->setLeft(parent);
        int color = sibling->getColor();
        sibling->setColor(parent->getColor());
	      sibling->getRight()->setColor(1);
        parent->setColor(color);
      }
    }
  }
}

void fixTreeDeleteRight(Node* &current, Node* &treeRoot) {
  Node* parent = NULL;
  if(current->getParent() != NULL) {
    parent = current->getParent(); 
  }
  Node* sibling = NULL;
  if(parent != NULL) {
    if(parent->getLeft() != NULL) {
      sibling = current->getParent()->getLeft(); 
    }
  }
  // case 1
  if(parent == NULL) {
    return;
  }
  if(sibling != NULL) {
    // case 2
    if(sibling->getColor() == 0) {
      if(sibling->getLeft() != NULL) {
        parent->setLeft(sibling->getRight());
        sibling->getRight()->setParent(parent);
      }
      sibling->setParent(parent->getParent());
      if(sibling->getValue() < parent->getParent()->getValue()) {
        parent->getParent()->setLeft(sibling); 
      } else {
        parent->getParent()->setRight(sibling); 
      }
      sibling->setRight(parent);
      parent->setParent(sibling);
      int color = parent->getColor();
      parent->setColor(sibling->getColor());
      sibling->setColor(color);
      fixTreeDeleteRight(current, treeRoot);
      // case 3
    } else if(sibling->getColor() + parent->getColor() == 2 && sibling->getRight() != NULL && sibling->getLeft() != NULL) {
      if(sibling->getRight()->getColor() == 1 && sibling->getLeft()->getColor() == 1) {
	      sibling->setColor(0);
	      fixTreeDeleteRight(parent, treeRoot);
      }
    }
    // case 3 but with NULL children
    if(sibling->getColor() + parent->getColor() == 2 && sibling->getRight() == NULL && sibling->getLeft() == NULL) {
      sibling->setColor(0);
      fixTreeDeleteRight(parent, treeRoot);
    }
    // case 4
    if(sibling->getLeft() != NULL && sibling->getRight() != NULL) {
      if(parent->getColor() == 0 && sibling->getColor() + sibling->getLeft()->getColor() + sibling->getRight()->getColor() == 3) {
        parent->setColor(1);
        sibling->setColor(0);
	      return;
      }      
    }
    // case 4 but with null children
    if(sibling->getLeft() == NULL && sibling->getRight() == NULL && parent->getColor() == 0 && sibling->getColor() == 1) {
      parent->setColor(1);
      sibling->setColor(0);
      return;
    }
    // case 5
    if(sibling->getRight() != NULL && sibling->getLeft() != NULL) {
      if(sibling->getColor() + sibling->getLeft()->getColor() == 2 && sibling->getRight()->getColor() == 0 && current->getValue() >= parent->getValue()) { 
        parent->setLeft(sibling->getRight());
        sibling->getRight()->setParent(parent);
        if(sibling->getRight()->getLeft() != NULL) {
          sibling->getRight()->getLeft()->setParent(sibling);
          sibling->setRight(sibling->getRight()->getLeft());
        }
        parent->getLeft()->setLeft(sibling); 
        sibling->setParent(parent->getLeft());
        sibling->setColor(0);
        sibling->getParent()->setColor(1);
	fixTreeDeleteRight(current, treeRoot);
      }
     // case 5 but with NULL left child
    } else if(sibling->getLeft() == NULL && sibling->getRight() != NULL) {
      if(sibling->getColor() == 1 && sibling->getRight()->getColor() == 0 && current->getValue() >= parent->getValue()) {
        parent->setLeft(sibling->getRight());
        sibling->getRight()->setParent(parent);
        if(sibling->getRight()->getLeft() != NULL) {
          sibling->getRight()->getLeft()->setParent(sibling);
          sibling->setRight(sibling->getRight()->getLeft());
        }
        parent->getLeft()->setLeft(sibling);
        sibling->setParent(parent->getLeft());
        sibling->setColor(0);
        sibling->getParent()->setColor(1);
	fixTreeDeleteRight(current, treeRoot);
      }
    }
    // case 6
    if(sibling->getLeft() != NULL) {
      if(sibling->getColor() == 1 && sibling->getLeft()->getColor() == 0 && current->getValue() >= parent->getValue()){
        if(parent->getParent() == NULL) {
          sibling->setParent(NULL);
          treeRoot = sibling;
        } else {
	        if(parent->getValue() < parent->getParent()->getValue()) {
            parent->getParent()->setLeft(sibling); 
          } else {
            parent->getParent()->setRight(sibling);
          }
          sibling->setParent(parent->getParent());
        }
        if(sibling->getRight() != NULL) {
          sibling->getRight()->setParent(parent);
          parent->setLeft(sibling->getRight());
        } else {
          parent->setLeft(NULL);
        }
        parent->setParent(sibling);
        sibling->setRight(parent);
        int color = sibling->getColor();
        sibling->setColor(parent->getColor());
	      sibling->getLeft()->setColor(1);
        parent->setColor(color);
      }
    }
  }
}

void remove(Node* &inputNode, int value, Node* &treeRoot) {
  // Value match found
  int traversalCounter = 0;
  if(inputNode->getValue() == value) {
    Node* current = inputNode;
    // Value is red
    if(inputNode->getColor() == 0) {
      // Node has two children
      if(inputNode->getLeft() != NULL && inputNode->getRight() != NULL) {
        current = inputNode->getLeft();
	      int traversalCounter = 0;
        while(current->getRight() != NULL) {
          current = current->getRight();
	        traversalCounter++;
        }
        // IOS has left child
        if(current->getLeft() != NULL) {
          if(current->getColor() != current->getLeft()->getColor()) {
      	    if(traversalCounter > 0) {
      	      current->getParent()->setRight(current->getLeft());
      	    } else {
      	      current->getParent()->setLeft(current->getLeft());
      	    }
            current->getLeft()->setColor(1);
            current->getLeft()->setParent(current->getParent());
	          inputNode->setValue(current->getValue());
            delete current;
            return;
          }
        // IOS is red
        } else if(current->getColor() == 0) {
      	  if(traversalCounter > 0) {
      	    current->getParent()->setRight(NULL);
      	  } else {
      	    current->getParent()->setLeft(NULL);
      	  } 
      	  inputNode->setValue(current->getValue());
      	  delete current;
      	  return;
      	}
        if(traversalCounter == 0) {
          fixTreeDeleteLeft(current, treeRoot);
        } else {
          fixTreeDeleteRight(current, treeRoot);
        }
        Node* tempNode = treeRoot;
        while(tempNode->getValue() != value) {
          if(value < tempNode->getValue()) {
            tempNode = tempNode->getLeft();
          } else {
            tempNode = tempNode->getRight();
          }
        }
	      tempNode->setValue(current->getValue());
        if(traversalCounter == 0) {
          if(current->getLeft() != NULL) {
            current->getParent()->setLeft(current->getLeft());
            current->getLeft()->setParent(current->getParent());
          } else {
            current->getParent()->setLeft(NULL);
          }
        } else {
          if(current->getLeft() != NULL) {
            current->getParent()->setRight(current->getLeft());
            current->getLeft()->setParent(current->getParent());
          } else {
            current->getParent()->setRight(NULL);
          }
        }
        delete current;
        current = NULL;
      } else if(inputNode->getLeft() != NULL && inputNode->getRight() == NULL) { 
      	int traversalCounter = 0;
      	current = inputNode->getLeft();
        while(current->getRight() != NULL) {
      	  current = current->getRight();
      	  traversalCounter++;
      	}
        inputNode->setValue(current->getValue());
        /*if(current->getColor() == 1) {
          inputNode->setColor(1); 
	       }*/
        // inorder successor has left child
        if(current->getLeft() != NULL) {
      	  if(traversalCounter > 0) {
      	    current->getParent()->setRight(current->getLeft());
      	  } else {
      	    current->getParent()->setLeft(current->getLeft());
      	  }
      	  current->getLeft()->setParent(current->getParent());
      	  current->getLeft()->setColor(1-inputNode->getColor());
        } else {
      	  if(traversalCounter > 0) {
      	    current->getParent()->setRight(NULL);
      	  } else {
      	    current->getParent()->setLeft(NULL);
      	  }
        }
        delete current;
        current = NULL;
        return;
        // node has a right child
      } else if(inputNode->getRight() != NULL && inputNode->getLeft() == NULL) {
        if(inputNode->getParent() != NULL) {
          if(inputNode->getValue() < inputNode->getParent()->getValue()) {
            inputNode->getParent()->setLeft(inputNode->getRight());
          } else {
            inputNode->getParent()->setRight(inputNode->getRight());
          }
          inputNode->getRight()->setParent(inputNode->getParent());
        } else {
          treeRoot = inputNode->getRight();
          inputNode->setParent(NULL);
        }
        delete inputNode;
	     // node has no children
      } else if(inputNode->getRight() == NULL && inputNode->getLeft() == NULL) {
        if(inputNode->getParent() != NULL) {
          if(inputNode->getParent()->getValue() <= inputNode->getValue()) {
            inputNode->getParent()->setRight(NULL);
          } else {
            inputNode->getParent()->setLeft(NULL);
          }
        } else {
          treeRoot = NULL;
        }
        delete inputNode;
        inputNode = NULL;
      }
      // value is black
    } else {
      // node has right child
      if(current->getLeft() == NULL && current->getRight() != NULL) {
        if(current->getColor() == 0) {
          current->getRight()->setColor(1);
          current->getRight()->setParent(current->getParent());
          if(current->getValue() < current->getParent()->getValue()) {
            current->getParent()->setLeft(current->getRight()); 
          } else {
            current->getParent()->setRight(current->getRight()); 
          }
          delete current;
        } else if(current->getRight()->getColor() == 0) {
      	  if(current->getParent() != NULL) {
      	    if(current->getValue() < current->getParent()->getValue()) {
      	      current->getParent()->setLeft(current->getRight());
      	    } else {
      	      current->getParent()->setRight(current->getRight());
      	    }
      	    current->getRight()->setColor(1);
      	    current->getRight()->setParent(current->getParent());
      	  } else {
      	    current->getRight()->setParent(NULL);
      	    treeRoot = current->getRight();
      	    current->getRight()->setColor(1);
      	  }
      	  delete current;
      	  current = NULL;
      	} else {
          fixTreeDeleteRight(current, treeRoot);
        }
        // node has left child
      } else if(current->getRight() == NULL && current->getLeft() != NULL) {
        if(current->getColor() == 0) {
          current->getLeft()->setColor(1);
          current->getLeft()->setParent(current->getParent());
          if(current->getValue() < current->getParent()->getValue()) {
            current->getParent()->setLeft(current->getLeft()); 
          } else {
            current->getParent()->setRight(current->getLeft()); 
          }
          delete current;
        } else if(current->getLeft()->getColor() == 0) {
      	  if(current->getParent() != NULL) {
      	    if(current->getValue() < current->getParent()->getValue()) {
      	      current->getParent()->setLeft(current->getLeft());
      	    } else {
      	      current->getParent()->setRight(current->getLeft());
      	    }
      	    current->getLeft()->setColor(1);
      	    current->getLeft()->setParent(current->getParent());
      	  } else {
      	    current->getLeft()->setParent(NULL);
      	    treeRoot = current->getLeft();
      	    current->getLeft()->setColor(1);
      	  }
      	  delete current;
      	  current = NULL;
      	} else {
          fixTreeDeleteLeft(current, treeRoot);
        }
        // node has no children
      } else if(current->getRight() == NULL && current->getLeft() == NULL) {
        if(current->getParent() == NULL) {
          delete inputNode;
          treeRoot = NULL;
          return;
        } else {
          if(current->getValue() < current->getParent()->getValue()) {
            fixTreeDeleteLeft(current, treeRoot);
	    if(current->getValue() < current->getParent()->getValue()) {
	      if(current->getLeft() != NULL) {	
		current->getParent()->setLeft(current->getLeft());
		current->getLeft()->setParent(current->getParent());
	      } else {
		current->getParent()->setLeft(NULL);
	      }
	    } else {
	      if(current->getLeft() != NULL) {
		current->getParent()->setRight(current->getLeft());
		current->getLeft()->setParent(current->getParent());
	      } else {
		current->getParent()->setRight(NULL);
	      }
	    }
	    delete current;
	    current = NULL;
	    return;
          } else {
            fixTreeDeleteRight(current, treeRoot);
	    cout << current->getValue() << endl;
            if(current->getValue() >= current->getParent()->getValue()) {
	      if(current->getRight() != NULL) {	
		current->getParent()->setRight(current->getRight());
		current->getRight()->setParent(current->getParent());
	      } else {
		current->getParent()->setRight(NULL);
	      }
	    } else {
	      if(current->getRight() != NULL) {
		current->getParent()->setLeft(current->getRight());
		current->getRight()->setParent(current->getParent());
	      } else {
		current->getParent()->setLeft(NULL);
	      }
	    }
	    delete current;
	    current = NULL;
	    return;
          }
        }
        // node has two children
      } else if(inputNode->getLeft() != NULL && inputNode->getRight() != NULL) {
        current = inputNode->getLeft();
	int traversalCounter = 0;
        while(current->getRight() != NULL) {
          current = current->getRight();
	        traversalCounter++;
        }
        // IOS is red
        if(current->getColor() == 0) {
      	  if(traversalCounter > 0) {
      	    current->getParent()->setRight(NULL);
      	  } else {
      	    current->getParent()->setLeft(NULL);
      	  } 
      	  inputNode->setValue(current->getValue());
      	  delete current;
      	  return;
	  // IOS has red left child
      	} else if(current->getLeft() != NULL) {
          if(current->getColor() != current->getLeft()->getColor()) {
      	    if(traversalCounter > 0) {
      	      current->getParent()->setRight(current->getLeft());
      	    } else {
      	      current->getParent()->setLeft(current->getLeft());
      	    }
            current->getLeft()->setColor(1);
            current->getLeft()->setParent(current->getParent());
	    inputNode->setValue(current->getValue());
            delete current;
            return;
          }
	  // IOS has no children
        } else if(traversalCounter == 0) {
          fixTreeDeleteLeft(current, treeRoot);
        } else {
          fixTreeDeleteRight(current, treeRoot);
        }
        Node* tempNode = treeRoot;
        while(tempNode->getValue() != value) {
          if(value < tempNode->getValue()) {
            tempNode = tempNode->getLeft();
          } else {
            tempNode = tempNode->getRight();
          }
        }
	      tempNode->setValue(current->getValue());
        if(traversalCounter == 0) {
          if(current->getLeft() != NULL) {
            current->getParent()->setLeft(current->getLeft());
            current->getLeft()->setParent(current->getParent());
          } else {
            current->getParent()->setLeft(NULL);
          }
        } else {
          if(current->getLeft() != NULL) {
            current->getParent()->setRight(current->getLeft());
            current->getLeft()->setParent(current->getParent());
          } else {
            current->getParent()->setRight(NULL);
          }
        }
        delete current;
        current = NULL;
      }
    }
  // None of the above scenarios apply. Find the appropriate child to examine (if it exists) and then use recursion
  } else {
    if(value >= inputNode->getValue() && inputNode->getRight() != NULL) {
      Node* rightChild = inputNode->getRight();
      remove(rightChild, value, treeRoot); 
    } else if(value >= inputNode->getValue() && inputNode->getRight() == NULL) {
      cout << "Value is not in tree." << endl;
    } else if(value < inputNode->getValue() && inputNode->getLeft() != NULL) {
      Node* leftChild = inputNode->getLeft();
      remove(leftChild, value, treeRoot);
    } else if(value < inputNode->getValue() && inputNode->getLeft() == NULL) {
      cout << "Value is not in tree." << endl;
    }
  } 
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
