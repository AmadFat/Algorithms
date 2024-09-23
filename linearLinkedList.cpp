#include <iostream>

template<typename T>
struct linkedListNode {
    using Node = linkedListNode<T>;
    T item;
    Node* next;

    linkedListNode() : item(T()), next(nullptr) {}
    linkedListNode(T item) : item(item), next(nullptr) {}
};

template<typename T>
using Node = linkedListNode<T>;

template<typename T>
struct linkedList {
    using List = linkedList<T>;
    Node<T>* head;
    linkedList(): head(new Node<T>()) {}

    void push_back(T item) {
        Node<T>* pnewnode = new Node<T>(item);
        if (head->next == nullptr) { head->next = pnewnode; return; }
        Node<T>* ptr = head->next;
        while (ptr->next != nullptr) ptr = ptr->next;
        ptr->next = pnewnode;
    }

    void push_front(T item) {
        Node<T>* pnewnode = new Node<T>(item);
        pnewnode->next = head->next;
        head->next = pnewnode;
    }

    T pop() {
        Node<T>* ppnode = head->next;
        T item = ppnode->item;
        head->next = head->next->next;
        delete ppnode;
        return item;
    }

    // in order to return 0 as EOF, we need head node
    size_t search(T item) {
        size_t cnt = 0;
        Node<T>* ptr = head->next;
        while (ptr != nullptr) {
            cnt ++;
            if (ptr->item == item) return cnt;
            ptr = ptr->next;
        }
        return 0;
    }

    size_t size() {
        size_t sz = 0;
        Node<T>* ptr = head->next;
        while (ptr != nullptr) {
            sz ++;
            ptr = ptr->next;
        }
        return sz;
    }

    void insert(T item, int idx) {
        size_t cnt = 0;
        Node<T>* pnewnode = new Node<T>(item);
        Node<T>* ptr = head;
        if (idx < 1 or size()+1 < idx) return;
        while (ptr != nullptr) {
            cnt ++;
            if (cnt == idx) {
                if (cnt == size()+1)
                    ptr->next = pnewnode;
                else {
                    pnewnode->next = ptr->next;
                    ptr->next = pnewnode;
                }
            }
            ptr = ptr->next;
        }
    }

    void remove(int idx) {
        size_t cnt = 0;
        Node<T>* ptr = head;
        if (idx < 1 or idx > size()) return;
        while (ptr != nullptr) {
            cnt ++; // cnt == tgt rm node idx == ptr->next idx
            if (cnt == idx) {
                if (cnt == size()) {
                    delete ptr->next;
                    ptr->next = nullptr;
                }
                else {
                    Node<T>* rmnode = ptr->next;
                    ptr->next = ptr->next->next;
                    delete rmnode;
                }
            }
            ptr = ptr->next;
        }
    }

    void print() {
        Node<T>* ptr = head->next;
        while (ptr != nullptr) {
            std::cout << ptr->item << " ";
            ptr = ptr->next;
        }
        std::cout << std::endl;
    }

    ~linkedList() {
        while (head) {
            Node<T>* rmnode = head;
            head = head->next;
            delete rmnode;
        }
    }
};


int main() {
    linkedList<int> list;

   std::cout << "this is an empty list: ";
   list.print();

    // 插入一些元素
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    std::cout << "this is a filled list: ";
    list.print();

    int tgt1 = 3, tgt2 = 6;
    std::cout << tgt1 << " in list? " << list.search(tgt1) << std::endl;
    std::cout << tgt2 << " in list? " << list.search(tgt2) << std::endl;


    std::cout << "size of the list: " << list.size() << std::endl;

    list.remove(5);
    std::cout << "list after removing: ";
    list.print();

    std::cout << "size of the list: " << list.size() << std::endl;

    list.insert(666, 3);
    std::cout << "list after insertion: ";
    list.print();

    std::cout << "size of the list: " << list.size() << std::endl;

    std::cout << "this a popping: " << list.pop() << std::endl;
    std::cout << "list after popping: ";
    list.print();
    return 0;
}