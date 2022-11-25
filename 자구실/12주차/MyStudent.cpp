#include "MyStudent.hpp"
#include <string.h>
#include <string>

// 디폴트 생성자
Student::Student() {
    this->id = -1;
    memset(this->name, 0x00, MAX_NAME_LEN + 1);
    this->score = -1.0;
}
// 생성자 : id , 이름 , 점수를 입력받고 초기화
Student::Student(int id, std::string name, double score) {
    this->id = id;
    memcpy(this->name, name.c_str(), MAX_NAME_LEN);
    this->score = score;
}
// 아이디 저장
void Student::setId(int id) { this->id = id; }
// 이름 저장
void Student::setName(std::string name) {
    memcpy(this->name, name.c_str(), MAX_NAME_LEN);
}
// 점수 저장
void Student::setScore(double score) { this->score = score; }
// 각각 id, name, score 반환
int Student::getId(void) { return this->id; }
std::string Student::getName(void) { return std::string(this->name); }
double Student::getScore(void) { return this->score; }
