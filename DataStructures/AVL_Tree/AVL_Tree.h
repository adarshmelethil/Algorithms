
#ifndef _AVL_Tree_h_
#define _AVL_Tree_h_

#include <iostream>

using namespace std;

template<typename T>
class AVL_Tree {
  public:
    class Node {
        friend class AVL_Tree<T>;
        int height;
        Node* leftLeg;
        Node* rightLeg;
        Node* parent;
      public:
        int value;
        Node() : leftLeg(0), rightLeg(0), parent(0), value(0) {}
        bool operator < (const Node& n) {
          return (this->value) < (n.value);
        }
        bool operator > (const Node& n) {
          return (this->value) > (n.value);
        }
        bool operator == (const Node& n) {
          return (this->value) == (n.value);
        }
    };

  Node* root;
  int size;

  void singleLeftRotate(Node* n) {
    Node* rightLeg = n->rightLeg;
    if(n->parent == 0) {
      root = rightLeg;
    }

    rightLeg->parent = n->parent;
    n->parent = rightLeg;

    n->rightLeg = rightLeg->leftLeg;
    rightLeg->leftLeg = n;
  }

  void singleRightRotate(Node* n) {
    Node* leftLeg = n->leftLeg;
    if(n->parent == 0) {
      root = leftLeg;
    }

    leftLeg->parent = n->parent;
    n->parent = leftLeg;

    n->leftLeg = leftLeg->rightLeg;
    leftLeg->rightLeg = n;
  }

  void doubleRightRotate(Node* n) {
    Node* leftLeg = n->leftLeg;
    Node* leftRightLeg = n->leftLeg->rightLeg;

    // left rotation
    leftRightLeg->parent = leftLeg->parent;
    leftLeg->parent = leftRightLeg;
    n->leftLeg = leftRightLeg;

    leftLeg->rightLeg = leftRightLeg->leftLeg;
    leftRightLeg->leftLeg = leftLeg;

    // right rotation
    singleRightRotate(n);
  }

  void doubleLeftRotate(Node* n) {
    Node* rightLeg = n->rightLeg;
    Node* rightLeftLeg = n->rightLeg->leftLeg;
    // right rotation
    rightLeftLeg->parent = rightLeg->parent;
    rightLeg->parent = rightLeftLeg;
    n->rightLeg = rightLeftLeg;

    rightLeg->leftLeg = rightLeftLeg->rightLeg;
    rightLeftLeg->rightLeg = rightLeg;

    // left rotation
    singleLeftRotate(n);
  }

  int height(Node* n) {
    if(n == 0) return 0;
    int rHeight = height(n->rightLeg);
    int lHeight = height(n->leftLeg);
    return 1 + (rHeight > lHeight ? rHeight:lHeight);
  }

  void inOrder(Node* n, int d[], int* index) {
    if(n->leftLeg != 0) {
      inOrder(n->leftLeg, d, index);
    }

    d[(*index)] = n->value;
    (*index)++;

    if(n->rightLeg != 0) {
      inOrder(n->rightLeg, d, index);
    }
  }

  void balanceTree(Node* curNode) {
    if(curNode == 0) return;
    int rHeight = height(curNode->rightLeg); // right leg height
    int lHeight = height(curNode->leftLeg);  // left leb height
    int heightDiff = rHeight - lHeight;

    if( heightDiff > 1 || heightDiff < -1) {  // abs(heightDiff) > 1
      if(rHeight > lHeight){     // right leg is heavy
        int rrHeight = height(curNode->rightLeg->rightLeg); // right leg's right leg height
        int rlHeight = height(curNode->rightLeg->leftLeg); // right leg's left leg height
        if(rlHeight > rrHeight) {// left heavy on right sub tree
          doubleLeftRotate(curNode);
        }else {
          singleLeftRotate(curNode);
        }
      }else{                                  // left leg is heavy
        int lrHeight = height(curNode->leftLeg->rightLeg); // left leg's right leg height
        int llHeight = height(curNode->leftLeg->leftLeg); // left leg's left leg height
        if(lrHeight > llHeight) {// right heavy on left sub tree
          doubleRightRotate(curNode);
        }else {
          singleRightRotate(curNode);
        }
      }
    }
    balanceTree(curNode->parent);
    return;
  }

public:
  AVL_Tree() : root(0), size(0){}

  int height(){ return height(root); }

  T* peekAtMinimumNode() const {
    if(root == 0) return 0;
    Node* cur = root;
    while(cur->leftLeg != 0) cur = cur->leftLeg;
    return (T*)cur;
  }

  T* popMinimumNode() {
    if(root == 0) return 0;
    Node* cur = root;
    while(cur->leftLeg != 0) cur = cur->leftLeg; // go to the left most Node
    // remove from tree
    cur->parent->leftLeg = cur->rightLeg;
    if(cur->rightLeg != 0) {
      cur->rightLeg->parent = cur->parent;
    }
    // balance tree
    balanceTree(cur->parent);

    cur->rightLeg = 0;
    cur->parent = 0;
    size--;
    return (T*)cur;
  }

  void insertItem(const T* item) {
    Node* n = (Node*)item;
    if(root == 0) {
      root = n; // First element
      size++;
      return;
    }
    Node* cur = root;
    while(cur) {
      if((*n) < (*cur)) { // left leg
        if(cur->leftLeg == 0) {
          cur->leftLeg = n;
          n->parent = cur;
          size++;
          break; // ADDED TO LEFT LEG
        }else {
          cur = cur->leftLeg;
          continue; // Continue to look for a spot
        }
      }else { // right leg
        if(cur->rightLeg == 0) {
          cur->rightLeg = n;
          n->parent = cur;
          size++;
          break;   // ADDED TO RIGHT LEG
        }else {
          cur = cur->rightLeg;
          continue; // Continue to look for a spot
        }
      }
    }
    balanceTree(cur);
    return;
  }

  int getContent(int*& n) {
    if(root == 0) return 0;
    n = new int[size];
    int index = 0;
    inOrder(root, n, &index);
    return size;
  }

};

#endif // End of _AVL_Tree_h_
