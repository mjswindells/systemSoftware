#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(int argc, char const *argv[]) {
    string str1 = "Hello World!";
    cout << "str1: " << str1 << endl; // str1: Hello World!
    string::reverse_iterator rit;
    cout << "str1 (reverse): "; // str1 (reverse): !dlroW olleH
    for (rit = str1.rbegin(); rit != str1.rend(); ++rit) {
        cout << *rit;
    }
    cout << endl << endl;
    string str2 = "Bonjour!";
    cout << "str2: " << str2 << endl << endl; // str2: Bonjour!
    str1.swap(str2);
    cout << "--- After swap ---" << endl;
    cout << "str1: " << str1 << endl; // str1: Bonjour!
    cout << "str2: " << str2 << endl; // str2: Hello World!
    return 0;
}
