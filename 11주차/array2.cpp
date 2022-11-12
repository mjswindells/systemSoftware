#include <array>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    // array 안에 array 선언
    // 4*8 사이즈의 array이고 전부 0으로 초기화
    array<array<int, 8>, 4> arr = {0};
    // arr의 행에 대한 반복자 생성
    array<array<int, 8>, 4>::iterator row;
    // arr의 열에 대한 반복자 생성
    array<int, 8>::iterator col;
    cout << "elements of arr" << endl;
    for (row = arr.begin(); row != arr.end(); ++row) {
        //반복자를 사용할 때에는 포인터로 사용을 해야 값을 가져온다
        for (col = (*row).begin(); col != (*row).end(); ++col) {
            cout << *col << " ";
        }
        cout << endl;
    }
    cout << endl;
    int i = 1;
    // 각 행을 하나의 숫자로 채운다
    // 0번째 행 : 1     1번째 행  : 2 이런식
    for (row = arr.begin(); row != arr.end(); ++row) {
        (*row).fill(i++);
    }
    cout << "value of arr[0][2]: ";
    // arr 첫번째 array의 2번째 원소
    cout << (arr.front())[2] << endl;
    cout << "value of arr[1][3]: ";
    // arr 두번째 array의 3번째 원소
    cout << (arr.at(1)).at(3) << endl;
    cout << "value of arr[2][2]: ";
    // arr의 2,2 원소
    cout << arr[2][2] << endl;
    return 0;
}
