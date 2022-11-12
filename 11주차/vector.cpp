#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    // 크기가 3이고 전부 0으로 초기화된 vector선언
    vector<int> v(3);
    vector<int>::iterator it;
    // 벡터의 사이즈 반환. : 원소의 개수
    cout << "size of v: " << v.size() << endl;
    // 벡터의 capacity 반환 : 들어갈 수 있는 크기
    cout << "capacity of v: " << v.capacity() << endl;
    cout << "elements of v: ";
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl << endl;
    // 각 원소 1,2,3으로 입력
    for (int i = 0; i < v.size(); ++i) {
        v[i] = i + 1;
    }
    // 벡터 뒤에 10부터 14까지 순차적을 채워넣음
    for (int i = 10; i < 15; ++i) {
        v.push_back(i);
    }
    cout << "--- After push_back ---" << endl;
    cout << "size of v: " << v.size() << endl;
    // capacity가 8이 아니라 12가 나온 이유는
    // 정확하게 8일 경우 원소를 추가할 때마다 capacity를
    // 늘려줘여하는데 이는 낭비이므로 넉넉하게 늘려준 거 같다
    cout << "capacity of v: " << v.capacity() << endl;
    cout << "elements of v: ";
    for (it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl << endl;
    // 벡터의 뒤 원소 2개 제거
    v.pop_back();
    v.pop_back();
    cout << "--- After pop_back ---" << endl;
    cout << "size of v: " << v.size() << endl;
    cout << "capacity of v: " << v.capacity() << endl;
    cout << "elements of v: ";
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
    return 0;
}
