#include "MyString.hpp"
#include <iostream>
using namespace std;

int main() {
    // ✅ Конструкторы
    Mystring s1("Hello");
    Mystring s2("World");
    Mystring s3(s1); // copy constructor

    cout << "s1: "; s1.Print(); cout << endl;
    cout << "s2: "; s2.Print(); cout << endl;
    cout << "s3 (copy of s1): "; s3.Print(); cout << endl;

    // ✅ Присваивание
    s3 = s2;
    cout << "s3 after assignment s2: "; s3.Print(); cout << endl;

    // ✅ Конкатенация
    Mystring s4 = s1 + s2;
    cout << "s4 (s1 + s2): "; s4.Print(); cout << endl;

    s1 += s2;
    cout << "s1 after s1 += s2: "; s1.Print(); cout << endl;

    // ✅ Сравнения
    cout << "s1 == s4 ? " << (s1 == s4) << endl;
    cout << "s1 != s2 ? " << (s1 != s2) << endl;
    cout << "s2 < s1 ? " << (s2 < s1) << endl;
    cout << "s2 > s1 ? " << (s2 > s1) << endl;
    cout << "s2 <= s1 ? " << (s2 <= s1) << endl;
    cout << "s2 >= s1 ? " << (s2 >= s1) << endl;

    // ✅ Доступ по индексу
    cout << "s2[0]: " << s2[0] << endl;
    s2[0] = 'w'; // copy-on-write
    cout << "s2 after modification: "; s2.Print(); cout << endl;

    // ✅ Clear
    s2.Clear();
    cout << "s2 after Clear(): "; s2.Print(); cout << " (length = " << s2.Length() << ")" << endl;

    // ✅ CountRef
    Mystring s5("Test");
    Mystring s6 = s5;
    cout << "s5 CountRef: " << s5.CountRef() << endl;
    cout << "s6 CountRef: " << s6.CountRef() << endl;

    return 0;
}
