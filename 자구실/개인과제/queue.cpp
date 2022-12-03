#include "DLL.cpp"

class Queue {

  public:
    int Size;
    Dll *dll;

    Queue() {
        dll = new Dll();
        Size = 0;
    }
    ~Queue() { dll->~Dll(); }

    // 비어있다면 1 아니면 0
    bool empty() { return dll->isEmpty(); }

    // Queue의 사이즈 반환
    size_t size() { return Size; }

    // 앞의 데이터 반환
    int front() { return dll->getHead(); }

    // 뒤의 데이터 반환
    int back() { return dll->getTail(); }

    // 앞에 val을 가지는 노드 추가
    void push(const int val) {
        dll->addBack(val);
        Size++;
    }

    // 맨 앞 노드 제거
    void pop() {
        dll->removeFront();
        Size--;
    }

    // 현재 queue와 x를 바꾼다
    void swap(Queue &x) {
        Queue *temp = new Queue();
        temp->Size = this->Size;
        temp->dll = this->dll;
        Size = x.Size;
        dll = x.dll;
        x.Size = temp->Size;
        x.dll = temp->dll;
    }

    void print() { dll->print(); }
};
