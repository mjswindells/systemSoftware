#include "MyStudent.hpp"
#include <fcntl.h>
#include <iostream>
#include <list>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
int main(void) {
    // 학생들의 정보를 입력받고, 연결 리스트에 저장
    list<Student> stuList;
    while (1) {
        string input;
        cout << "<< ID (input \'q\' to terminate): ";
        // input에 q를 받으면 실행 종료
        cin >> input;
        if (input.compare("q") == 0) {
            cout << ">> Terminate input." << endl;
            break;
        }
        // string을 int로 변환한다
        int id = stoi(input);
        string name = "";
        cout << "<< Name: ";
        cin >> name;
        double score = -1.0;
        cout << "<< Score: ";
        cin >> score;
        // 위에서 입력받은 정보로 Student 생성
        Student stu(id, name, score);
        // List 뒤에 저장
        stuList.push_back(stu);
        cout << ">> Successfully added to list!" << endl;
    }
    // 입력된 학생들의 정보를 저장할 파일 열기
    string filepath = "./StudentList.dat";
    // 없으면 생성 있으면 append
    int fd = open(filepath.c_str(), O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open() error");
        return 1;
    }
    // 학생들의 정보를 파일에 순차적으로 저장하기
    list<Student>::iterator iter;
    for (iter = stuList.begin(); iter != stuList.end(); ++iter) {
        // Student 리스트에 있는 정보 처음부터 끝까지 하나씩 쓰기
        if (write(fd, &(*iter), sizeof(Student)) == -1) {
            perror("write() error");
            return 2;
        }
    }
    close(fd);
    cout << ">> " << stuList.size()
         << " students' info was successfully saved to the " << filepath
         << endl;
    return 0;
}
