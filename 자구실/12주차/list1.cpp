#include <iostream>
#include <list>
using namespace std;
int main(void) {
    double myDoubles[] = {12.15, 2.72,  73.0,  12.77, 3.14,
                          12.77, 73.35, 72.25, 15.3,  72.25};

    // myDoubles의 주소 처음과 끝으로 stl list 초기화
    list<double> myList(myDoubles, myDoubles + 10);
    list<double>::iterator it;
    cout << ">> nodes of myList: ";
    // list는 iterator를 이용해 각 원소에 접근한다
    for (it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "<< myList.push_front(1.4);" << endl;
    // 맨 앞에 1.4 추가
    myList.push_front(1.4);
    cout << "<< myList.push_back(1.4);" << endl;
    // 맨 뒤에 1.4 추가
    myList.push_back(1.4);
    cout << ">> nodes of myList: ";
    for (it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "<< myList.sort();" << endl;
    // myList 오름차순으로 정렬
    myList.sort();
    cout << ">> nodes of myList: ";
    for (it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    // myList의 중복된 원소를 제거
    myList.unique();
    cout << ">> nodes of myList: ";
    for (it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
