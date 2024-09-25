#include <iostream>
#include <string>
#include <vector>

template<typename T>
struct binaryTreeNode {
    using Node = binaryTreeNode<T>;
    T item;
    size_t height;
    size_t depth;
    Node* parent;
    Node* left;
    Node* right;
    binaryTreeNode(T item):
        item(item), height(0), depth(0), parent(nullptr), left(nullptr), right(nullptr)
        {}
    
    void app_left(Node* child) { left = child; child->parent = this; update_tree(child); }
    void app_right(Node* child) { right = child; child->parent = this; update_tree(child); }
    void update_tree(Node* child) {
        if (child->parent) {
            child->depth = child->parent->depth + 1;
            child->parent->height = child->parent->height > child->height+1 ? child->parent->height : child->height+1;
            update_tree(child->parent);
        }
        
    }

    void print() {
        std::cout << item << " ";
        if (left != nullptr) std::cout << left->item << " ";
        if (right != nullptr) std::cout << right->item << " ";
        std::cout << std::endl;
    }
};

template<typename T>
using Node = binaryTreeNode<T>;

template<typename T>
struct binaryTree {
    Node<T>* root;
    binaryTree(): root(nullptr) {}
    binaryTree(Node<T>* node): root(node) {}

    void preord_traversal() { preord_traversal(root); }

    void preord_traversal(Node<T>* pnode) {
        if (pnode && pnode->left) preord_traversal(pnode->left);
        if (pnode) std::cout << "item: " << pnode->item << "  height: " << pnode->height << "  depth: " << pnode->depth << std::endl;
        if (pnode && pnode->right) preord_traversal(pnode->right);
    }

    void inord_traversal() { inord_traversal(root); }

    void inord_traversal(Node<T>* pnode) {
        if (pnode) std::cout << "item: " << pnode->item << "  height: " << pnode->height << "  depth: " << pnode->depth << std::endl;
        if (pnode && pnode->left) preord_traversal(pnode->left);
        if (pnode && pnode->right) preord_traversal(pnode->right);
    }

    void postord_traversal() { postord_traversal(root); }

    void postord_traversal(Node<T>* pnode) {
        if (pnode && pnode->right) preord_traversal(pnode->right);
        if (pnode) std::cout << "item: " << pnode->item << "  height: " << pnode->height << "  depth: " << pnode->depth << std::endl;
        if (pnode && pnode->left) preord_traversal(pnode->left);
    }

    void preord_stack(std::vector<Node<T>*>& pst) { preord_stack(pst, root); }

    void preord_stack(std::vector<Node<T>*>& pst, Node<T>* pnode) {
        if (pnode && pnode->left) preord_stack(pst, pnode->left);
        if (pnode) pst.push_back(pnode);
        if (pnode && pnode->right) preord_stack(pst, pnode->right);
    }

    void print() {
        std::vector<Node<int>*> pst;
        preord_stack(pst);
        clc();
        for (int i = 0; i < pst.size(); i ++) {
            if (pst[i]->parent && pst[i]->parent->left==pst[i]) {
                gotoxy(2*pst[i]->depth, 2*i+2);
                std::cout << "/";
            }
            if (pst[i]->parent && pst[i]->parent->right==pst[i]) {
                gotoxy(2*pst[i]->depth, 2*i);
                std::cout << "\\";
            }
            gotoxy(2*pst[i]->depth+1, 2*i+1);
            std::cout << pst[i]->item;
        }
    }

    void gotoxy(size_t x, size_t y) { std::cout << "\033[" << std::to_string(x) << ";" << std::to_string(y) << "H"; }

    void clc() { std::cout << "\033[2J\033[1;1H"; }
};



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

    std::cout << "this is a PreOrder Traversal:" << std::endl;
    tree.preord_traversal();
    std::cout << "this is a InOrder Traversal:" << std::endl;
    tree.inord_traversal();
    std::cout << "this is a PostOrder Traversal:" << std::endl;
    tree.postord_traversal();
    std::cout << "this is root item: " << tree.root->item;
    return 0;
}