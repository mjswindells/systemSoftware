#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main(int argc, char const *argv[]) {
    // 크기가 2이고 전부 100인 벡터
    vector<int> myVector(2, 100);
    // 빈 스택 생성
    stack<int> myStack1;
    // int형이고 데이터를 벡터형식으로 담는 스택 생성
    stack<int, vector<int>> myStack2(myVector);
    // stack1 은 사이즈 0이다.
    cout << "Size of myStack1: " << myStack1.size() << endl;
    if (myStack1.empty() == 1) {
        cout << "myStack1 is empty" << endl;
    }
    // stack2는 사이즈 2 에 전부 100
    cout << "Size of myStack2: " << myStack2.size() << endl;
    cout << "Top of myStack2: " << myStack2.top() << endl;
    cout << endl;
    // 빈 스택에 차례로 1 2 3 을 추가한다
    myStack1.push(1);
    myStack1.push(2);
    myStack1.push(3);
    cout << "--- After push ---" << endl;
    // 사이즈는 3이 되고 맨 위에는 3이 올라가 있다
    cout << "Size of myStack1: " << myStack1.size() << endl;
    cout << "Top of myStack1 : " << myStack1.top() << endl;
    cout << endl;
    // 각 스택의 맨위 원소 하나씩 제거
    myStack1.pop();
    myStack2.pop();
    cout << "--- After pop ---" << endl;
    // stack1은 사이즈 2 top : 2
    // stack2는 사이즈 1 top : 100
    cout << "Size of myStack1: " << myStack1.size() << endl;
    cout << "Top of myStack1: " << myStack1.top() << endl;
    cout << "Size of myStack2: " << myStack2.size() << endl;
    cout << "Top of myStack2: " << myStack2.top() << endl;
    return 0;
}
