#include "queue.cpp"

int main() {
    Queue q;
    Queue p;
    q.push(3);
    q.push(5);
    q.push(6);
    q.push(7);

    p.push(10);
    p.push(11);
    p.push(12);
    p.push(13);

    cout << "push 3 , 5 , 6 , 7 후 q : ";
    q.print();
    cout << "push 10 , 11 , 12 , 13 후 p : ";
    p.print();
    cout << endl;

    q.swap(p);

    cout << "swap 후 q :";
    q.print();
    cout << "swap 후 p :";
    p.print();
    cout << endl;

    q.pop();
    q.pop();
    cout << "pop 두번 후 q : ";
    q.print();
    cout << endl;
    cout << "size of q : " << q.size() << endl;
    cout << "size of p : " << p.size() << endl << endl;

    cout << "front(q) : " << q.front() << endl;
    cout << "back(q) : " << q.back() << endl << endl;

    cout << "empty(q) : " << q.empty() << endl;
    q.pop();
    q.pop();
    cout << "pop 두번 후 q : ";
    q.print();
    // 이 때 q는 비어있다
    cout << "empty(q) : " << q.empty() << endl << endl;
}
