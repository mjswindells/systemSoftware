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
        // 현재 노드와 다음 노드를 연결하는 노드 생성 B라 하자
        Node *u = new Node(e, v->link_fore, v);
        // w는 현재 노드의 다음 것 C라 하자
        Node *w = v->link_fore;
        // C의 전 노드를 B로 설정
        w->link_back = u;
        // A의 다음 노드를 B로 설정
        v->link_fore = u;
    }
    // 각각 맨 앞과 맨 뒤 노드 삭제
    void removeFront() { remove(head->link_fore); }
    void removeBack() { remove(tail->link_back); }
    // 특정 위치의 노드 삭제
    void remove(Node *v) {
        // 비어 있으면 리턴
        if (isEmpty())
            return;
        Node *u = v->link_back;
        Node *w = v->link_fore;
        if (u != NULL)
            u->link_fore = w;
        if (w != NULL)
            w->link_back = u;
        delete v;
    }
    // 특정 원소를 가진 노드를 하나 삭제
    // 원소를 가진 노드가 없다면 아무 일도 안 일어남
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

    // Head의 데이터 반환
    int getHead() { return head->link_fore->data; }
    // Tail의 데이터 반환
    int getTail() { return tail->link_back->data; }

    // Head 노드 반환
    Node *getFront() { return head; }
    // Tail 노드 반환
    Node *getBack() { return tail; }

    // Dll 전체 데이터 print
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
