#include <iostream>
#include <stddef.h>

using namespace std;

class Node {
  public:
    typedef double value_type;

    // 노드 생성 및 초기화
    Node(const value_type &init_data = value_type(), Node *init_fore = NULL,
         Node *init_back = NULL) {
        data = init_data;
        link_fore = init_fore;
        link_back = init_back;
    }
    value_type data;
    Node *link_fore;
    Node *link_back;
};

class Dll {
  public:
    // 생성자 : head 와 tail 노드를 초기화하고 서로 link한다
    Dll() {
        head = new Node;
        tail = new Node;
        head->link_fore = tail;
        tail->link_back = head;
    }
    ~Dll() {
        while (!isEmpty())
            removeFront();
        delete head;
        delete tail;
    }
    // DLL이 비어있으면 true
    bool isEmpty() { return (head->link_fore == tail); }

    // DLL 앞에 노드 추가
    void addFront(const int &e) { add(head, e); }

    // DLL 뒤에 노드 추가
    void addBack(const int &e) { add(tail->link_back, e); }

    // 특정 위치에 노드 추가
    void add(Node *v, const int &e) {
        Node *u = new Node(e, v->link_fore, v);
        Node *w = v->link_fore;
        w->link_back = u;
        v->link_fore = u;
    }
    // 각각 맨 앞과 맨 뒤 노드 삭제
    void removeFront() { remove(head->link_fore); }
    void removeBack() { remove(tail->link_back); }
    // 특정 위치의 노드 삭제
    void remove(Node *v) {
        if (isEmpty())
            return;
        Node *u = v->link_back;
        Node *w = v->link_fore;
        u->link_fore = w;
        w->link_back = u;
        delete v;
    }
    // 특정 원소를 가진 노드 삭제
    void remove(int e) {
        if (isEmpty())
            return;
        Node *temp = head->link_fore;
        while (temp->link_fore != NULL) {
            if (temp->data == e) {
                remove(temp);
                return;
            }
            temp = temp->link_fore;
        }
    }

    void print() {
        Node *temp = head->link_fore;
        while (temp->link_fore != NULL) {
            cout << temp->data << " ";
            temp = temp->link_fore;
        }
        cout << endl;
    }

  private:
    Node *head;
    Node *tail;
};
