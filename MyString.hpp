#pragma once
#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

class Mystring
{
private:
    char *str;
    int length;
    int *refCount;
    void allocateAndCopy(const char *source, int len);

    void detach();

public:
    Mystring();
    Mystring(const char *input);
    Mystring(const Mystring &other);
    ~Mystring();

    Mystring &operator=(const Mystring &other);
    Mystring operator+(const Mystring &other);
    Mystring &operator+=(const Mystring &other);

    bool operator==(const Mystring &other) const;
    bool operator!=(const Mystring &other) const;
    bool operator<(const Mystring &other) const;
    bool operator>(const Mystring &other) const;
    bool operator<=(const Mystring &other) const;
    bool operator>=(const Mystring &other) const;

    char &operator[](int index);
    const char &operator[](int index) const;

    int Length() const;
    void Print() const;
    int CountRef() const;
    void Clear();
    const char *c_str() const;

    int Find(char c) const;
    int Find(const Mystring& substr) const;

};
