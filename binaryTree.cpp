#include <iostream>
#include "binaryTree.h"
using namespace Trees;

template <typename T>
void print_pst(std::vector<Node<T>*>& pst) {
    for (int i = 0; i < pst.size(); i ++)
        std::cout << pst[i]->item << " ";
    std::cout << std::endl;
}

int main() {
    binaryTree<int> tree(new Node<int> (1));
    tree.root->app_left(new Node<int> (2));
    tree.root->app_right(new Node<int> (3));
    tree.root->left->app_left(new Node<int> (4));
    tree.root->left->app_right(new Node<int> (5));
    tree.root->right->app_left(new Node<int> (6));
    tree.root->right->app_right(new Node<int> (7));
    tree.root->right->right->app_right(new Node<int> (8));

    tree.print();
    std::cout << std::endl;

    std::vector<Node<int>*> pst;

    std::cout << "this is a PreOrder Traversal:" << std::endl;
    pst.clear();
    tree.preord_stack(pst);
    print_pst(pst);
    
    std::cout << "this is a InOrder Traversal:" << std::endl;
    pst.clear();
    tree.inord_stack(pst);
    print_pst(pst);

    std::cout << "this is a PostOrder Traversal:" << std::endl;
    pst.clear();
    tree.postord_stack(pst);
    print_pst(pst);
    return 0;
}