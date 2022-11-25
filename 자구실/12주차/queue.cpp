#include <iostream>
#include <list>
#include <queue>
using namespace std;
int main(int argc, char const *argv[]) {
    list<int> myList(2, 100);
    queue<int> myQueue1;
    queue<int, list<int>> myQueue2(myList);
    cout << "Size of myQueue1 : " << myQueue1.size() << endl;
    if (myQueue1.empty() == 1) {
        cout << "myQueue1 is empty" << endl << endl;
    }
    // queue2의 사이즈는 2 앞에 원소 100 뒤에 원소 100
    cout << "Size of myQueue2 : " << myQueue2.size() << endl;
    cout << "Front of myQueue2 : " << myQueue2.front() << endl;
    cout << "Back of myQueue2 : " << myQueue2.back() << endl;
    cout << endl;
    // 비어있는 queue1에 1 2 3 을 차례로 넣는다
    // queue2에는 200 추가
    myQueue1.push(1);
    myQueue1.push(2);
    myQueue1.push(3);
    myQueue2.push(200);
    cout << "--- After push ---" << endl;
    // queue1의 사이즈 3 맨 앞 원소 1 맨 뒤 원소 3
    // queue2의 사이즈 3 맨 앞 원소 100 맨 뒤 원소 200
    cout << "Size of myQueue1 : " << myQueue1.size() << endl;
    cout << "Front of myQueue1 : " << myQueue1.front() << endl;
    cout << "Back of myQueue1 : " << myQueue1.back() << endl << endl;
    cout << "Size of myQueue2 : " << myQueue2.size() << endl;
    cout << "Front of myQueue2 : " << myQueue2.front() << endl;
    cout << "Back of myQueue2 : " << myQueue2.back() << endl;
    cout << endl;
    // queue1 앞에 원소 2개 제거, queue2 맨 앞 원소 1개 제거
    myQueue1.pop();
    myQueue2.pop();
    myQueue2.pop();
    cout << "--- After pop ---" << endl;
    // queue1 사이즈 2 맨 앞 2 맨 뒤 3
    // queue2 사이즈 1 맨 앞 == 맨 뒤 == 200
    cout << "Size of myQueue1 : " << myQueue1.size() << endl;
    cout << "Front of myQueue1 : " << myQueue1.front() << endl;
    cout << "Back of myQueue1 : " << myQueue1.back() << endl << endl;
    cout << "Size of myQueue2 : " << myQueue2.size() << endl;
    cout << "Front of myQueue2 : " << myQueue2.front() << endl;
    cout << "Back of myQueue2 : " << myQueue2.back() << endl;
    return 0;
}
