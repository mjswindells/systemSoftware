#include "DLL.cpp"

int main(void) {
    Dll *dll = new Dll();

    dll->addBack(32);
    dll->addBack(2);
    dll->addBack(3);
    dll->addBack(1);
    dll->addFront(6);
    dll->addFront(7);

    cout << "노드 추가 후 결과  : ";
    dll->print(); // 7 6 32 2 3 1

    dll->remove(32);
    dll->removeFront();
    dll->removeBack();

    cout << "노드 삭제 후 결과  : ";
    dll->print(); // 6 2 3
    cout << "isEmpty ? " << dll->isEmpty() << endl;

    dll->removeBack();
    dll->removeBack();
    dll->removeBack();
    cout << "전부 삭제 후 결과  : ";
    dll->print();
    cout << "isEmpty ? " << dll->isEmpty() << endl << endl;
    return 0;
}
