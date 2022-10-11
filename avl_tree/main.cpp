#include <iostream>
#include "avl_tree.h"

using namespace std;

int main() {

    AVLTree<int,int> tree;

    tree[1] = 20;
    tree[2] = 30;

    tree.size();

//    cout << tree[1] << endl;
//    cout << tree[2] << endl;

    return 0;
}
