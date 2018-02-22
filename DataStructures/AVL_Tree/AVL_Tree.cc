#include "AVL_Tree.h"
#include <math.h>

template<typename T>
void AVL_Tree<T>::leftRotate(Node* n) {
  Node* rightLeg = n->rightLeg;
  if(n->parent == 0) {
    root = rightLeg;
  }

  n->rightLeg = rightLeg->leftLeg;
  rightLeg->parent = n->parent;
  n->parent = rightLeg;
  rightLeg->leftLeg = n;
}

template<typename T>
void AVL_Tree<T>::rightRotate(Node* n) {
  Node* leftLeg = n->leftLeg;
  if(n->parent == 0) {
    root = leftLeg;
  }

  n->leftLeg = leftLeg->rightLeg;
  leftLeg->parent = n->parent;
  n->parent = leftLeg;
  leftLeg->rightLeg = n;
}

template<typename T>
void AVL_Tree<T>::leftRightRotate(Node* n) {
  Node* leftLeg = n->leftLeg;
  Node* leftRightLeg = leftLeg->rightLeg;

  leftLeg->rightLeg = leftRightLeg->leftLeg;
  leftLeg->parent = leftRightLeg;
  leftRightLeg->parent = n;
  leftRightLeg->leftLeg = leftLeg;
  rightRotate(n);
}

template<typename T>
void AVL_Tree<T>::rightLeftRotate(Node* n) {
  Node* rightLeg = n->rightLeg;
  Node* rightLeftLeg = rightLeg->leftLeg;

  rightLeg->leftLeg = rightLeftLeg->rightLeg;
  rightLeg->parent = rightLeftLeg;
  rightLeftLeg->parent = n;
  rightLeftLeg->leftLeg = rightLeg;
  leftRotate(n);
}

template<typename T>
int AVL_Tree<T>::height(Node* n) {
  if(n == 0) return 0;
  int rHeight = height(n->rightLeg);
  int lHeight = height(n->leftLeg);
  return 1 + (rHeight > lHeight ? rHeight:lHeight);
}

template<typename T>
T* AVL_Tree<T>::peekAtMinimumNode() const {
  if(root == 0) return 0;
  Node* cur = root;
  while(cur->leftLeg != 0) cur = cur->leftLeg;
  return (T*)cur;
}

template<typename T>
T* AVL_Tree<T>::popMinimumNode() {
  if(root == 0) return 0;
  Node* cur = root;
  while(cur->leftLeg != 0) cur = cur->leftLeg; // go to the left most Node
  cur->parent->leftLeg = cur->rightLeg;
  if(cur->rightLeg != 0) cur->rightLeg->parent = cur->parent;

  cur->rightLeg = 0;
  cur->parent = 0;
  return (T*)cur;
}

template<typename T>
void AVL_Tree<T>::insertItem(const T* item) {
  Node* n = (Node*)item;
  if(root == 0) root = n; // First element

  Node* cur = root;
  while(cur) {
    if((*n) < (*cur)) { // left leg
      if(cur->leftLeg == 0) {
        cur->leftLeg = n;
        n->parent = cur;
        size++;
        return; // ADDED TO LEFT LEG
      }else {
        cur = cur->leftLeg;
        continue; // Continue to look for a spot
      }
    }else { // right leg
      if(cur->rightLeg == 0) {
        cur->rightLeg = n;
        n->parent = cur;
        size++;
        return; // ADDED TO RIGHT LEG
      }else {
        cur = cur->rightLeg;
        continue; // Continue to look for a spot
      }
    }
  }
  return;
}

template<typename T>
int* AVL_Tree<T>::getContent() {
  if(root == 0) return 0;
  int* n = new int[size];
  int index = 0;
}

template<typename T>
void AVL_Tree<T>::inOrder(Node* n, int d[], int* index) {
  if(n->leftLeg != 0) {
    inOrder(n->leftLeg, d, index);
  }

  d[(*index)] = n->value;
  (*index)++;

  if(n->rightLeg != 0) {
    inOrder(n->rightLeg, d, index);
  }
}
