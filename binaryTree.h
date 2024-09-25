#include <iostream>
#include <vector>

namespace Trees {
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

        void preord_stack(std::vector<Node<T>*>& pst) { preord_stack(pst, root); }

        void preord_stack(std::vector<Node<T>*>& pst, Node<T>* pnode) {
            if (pnode) pst.push_back(pnode);
            if (pnode && pnode->left) preord_stack(pst, pnode->left);
            if (pnode && pnode->right) preord_stack(pst, pnode->right);
        }

        void inord_stack(std::vector<Node<T>*>& pst) { inord_stack(pst, root); }

        void inord_stack(std::vector<Node<T>*>& pst, Node<T>* pnode) {
            if (pnode && pnode->left) inord_stack(pst, pnode->left);
            if (pnode) pst.push_back(pnode);
            if (pnode && pnode->right) inord_stack(pst, pnode->right);
        }

        void postord_stack(std::vector<Node<T>*>& pst) { postord_stack(pst, root); }

        void postord_stack(std::vector<Node<T>*>& pst, Node<T>* pnode) {
            if (pnode && pnode->left) postord_stack(pst, pnode->left);
            if (pnode && pnode->right) postord_stack(pst, pnode->right);
            if (pnode) pst.push_back(pnode);
        }

        void gotoxy(size_t x, size_t y) { std::cout << "\033[" << std::to_string(x) << ";" << std::to_string(y) << "H"; }

        void clc() { std::cout << "\033[2J\033[1;1H"; }

        void print() {
            std::vector<Node<int>*> pst;
            inord_stack(pst);
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
    };
}