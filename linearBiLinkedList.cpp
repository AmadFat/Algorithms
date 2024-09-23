#include <iostream>

template<typename T>
struct linkedListNode {
    using Node = linkedListNode<T>;
    T item;
    Node* prev;
    Node* next;

    linkedListNode(): item(T()), prev(nullptr), next(nullptr) {}
    linkedListNode(T item): item(item), prev(nullptr), next(nullptr) {}
    linkedListNode(Node* prev, Node*next): item(T()), prev(prev), next(next) {}
};

template<typename T>
using Node = linkedListNode<T>;

template<typename T>
struct biLinkedList {
    using bilist = biLinkedList<T>;
    Node<T>* head = new Node<T>();
    Node<T>* tail = new Node<T>();
    biLinkedList() { head->next = tail; tail->prev = head; }

    void push_back(T item) {
        Node<T>* pnewnode = new Node<T>(item);
        pnewnode->prev = tail->prev;
        tail->prev = pnewnode;
        pnewnode->prev->next = pnewnode;
        pnewnode->next = tail;
    }

    void push_front(T item) {
        Node<T>* pnewnode = new Node<T>(item);
        pnewnode->next = head->next;
        head->next = pnewnode;
        pnewnode->next->prev = pnewnode;
        pnewnode->prev = head;
    }

    T pop_back() {
        Node<T>* ppnode = tail->prev;
        T item = ppnode->item;
        tail->prev = tail->prev->prev;
        delete ppnode;
        return item;
    }

    T pop_front() {
        Node<T>* ppnode = head->next;
        T item = ppnode->item;
        head->next = head->next->next;
        delete ppnode;
        return item;
    }

    size_t search_back(T item) {
        size_t cnt = 0;
        Node<T>* ptr = tail->prev;
        while (ptr != nullptr) {
            cnt ++;
            if (ptr->item == item) return cnt;
            ptr = ptr->prev;
        }
        return 0;
    }

    size_t search_front(T item) {
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
        size_t szfr = 0, szbk = 0;
        Node<T>* pfr = head->next;
        Node<T>* pbk = tail->prev;
        while (pfr->next != nullptr) { szfr ++; pfr = pfr->next; }
        while (pbk->prev != nullptr) { szbk ++; pbk = pbk->prev; }
        if (szfr == szbk) return szfr;
        std::cout << "assertion fail: the bidirectional link has collapsed.";
        return 0;
    }

    void print_front() {
        Node<T>* ptr = head->next;
        while (ptr->next != nullptr) {
            std::cout << ptr->item << " ";
            ptr = ptr->next;
        }
        std::cout << std::endl;
    }

    void print_back() {
        Node<T>* ptr = tail->prev;
        while (ptr->prev != nullptr) {
            std::cout << ptr->item << " ";
            ptr = ptr->prev;
        }
        std::cout << std::endl;
    }
};

// template<typename T>
// using bList = biLinkedList<T>;

int main() {
    biLinkedList<int> blist;
    blist.push_front(1);
    blist.print_front();
    blist.print_back();
    std::cout << "size of blist: " << blist.size() << std::endl;
    blist.push_back(2);
    blist.print_front();
    blist.print_back();
    std::cout << "size of blist: " << blist.size() << std::endl;
    return 0;
}