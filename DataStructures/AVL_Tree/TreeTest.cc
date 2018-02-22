#include <iostream>
#include "AVL_Tree.h"

using namespace std;

class TestItem : public AVL_Tree<TestItem>::Node {
  public:
    TestItem(int n){ value = n; }
    void setValue(int n) { value = n; }
    int getValue() { return value; }
};

//#define SINGLE_RIGHT_ROTATE_TEST
//#define SINGLE_LEFT_ROTATE_TEST
//#define DOUBLE_RIGHT_ROTATE_TEST
//#define DOUBLE_LEFT_ROTATE_TEST
#define POP_MINIMUM_TEST

int main() {
  #ifdef SINGLE_RIGHT_ROTATE_TEST
  {
    cout << endl;
    cout << "Single Right Rotate Test:" << endl;

    AVL_Tree<TestItem>* tree = new AVL_Tree<TestItem>();
    tree->insertItem(new TestItem(6));
    tree->insertItem(new TestItem(7));
    tree->insertItem(new TestItem(8));

    int* d;
    int size = tree->getContent(d);
    for(int i = 0; i < size; i++) {
      cout << "d[" << i << "] = "<< d[i] << endl;
    }
    cout << endl;
  }
  #endif

  #ifdef SINGLE_LEFT_ROTATE_TEST
  {
    cout << endl;
    cout << "Single Left Rotate Test:" << endl;

    AVL_Tree<TestItem>* tree = new AVL_Tree<TestItem>();
    tree->insertItem(new TestItem(6));
    tree->insertItem(new TestItem(5));
    tree->insertItem(new TestItem(4));

    int* d;
    int size = tree->getContent(d);
    for(int i = 0; i < size; i++) {
      cout << "d[" << i << "] = "<< d[i] << endl;
    }
    cout << endl;
  }
  #endif

  #ifdef DOUBLE_RIGHT_ROTATE_TEST
  {
    cout << endl;
    cout << "Double Right Rotate Test:" << endl;

    AVL_Tree<TestItem>* tree = new AVL_Tree<TestItem>();
    tree->insertItem(new TestItem(6));
    tree->insertItem(new TestItem(4));
    tree->insertItem(new TestItem(5));

    int* d;
    int size = tree->getContent(d);
    for(int i = 0; i < size; i++) {
      cout << "d[" << i << "] = "<< d[i] << endl;
    }
    cout << endl;
  }
  #endif

  #ifdef DOUBLE_LEFT_ROTATE_TEST
  {
    cout << endl;
    cout << "Double Left Rotate Test:" << endl;

    AVL_Tree<TestItem>* tree = new AVL_Tree<TestItem>();
    tree->insertItem(new TestItem(6));
    tree->insertItem(new TestItem(8));
    tree->insertItem(new TestItem(7));

    int* d;
    int size = tree->getContent(d);
    for(int i = 0; i < size; i++) {
      cout << "d[" << i << "] = "<< d[i] << endl;
    }
    cout << endl;
  }
  #endif

  #ifdef POP_MINIMUM_TEST
  {
    cout << endl;
    cout << "Poping Minimum Test:" << endl;

    AVL_Tree<TestItem>* tree = new AVL_Tree<TestItem>();
    tree->insertItem(new TestItem(5));
    tree->insertItem(new TestItem(6));
    tree->insertItem(new TestItem(4));
    tree->insertItem(new TestItem(7));

    cout << "Height of the tree before removing: " << tree->height() << endl;
    TestItem* t = tree->popMinimumNode();
    cout << "Height of the tree after removing: " << tree->height() << endl;
    cout << "Value of the poped node: " << t->getValue() << endl;
    int* d;
    int size = tree->getContent(d);
    for(int i = 0; i < size; i++) {
      cout << "d[" << i << "] = "<< d[i] << endl;
    }
    cout << endl;
  }
  #endif
}
