#include "MyString.hpp"

void Mystring::allocateAndCopy(const char *source, int len)
{
    str = new char[len + 1];
    for (int i = 0; i < len; i++)
    {
        str[i] = source[i];
    }
    str[len] = '\0';
    length = len;
    refCount = new int(1);
}

void Mystring::detach() {
    if (*refCount > 1) {
        (*refCount)--;
        char *newBuf = new char[length + 1];
        for (int i = 0; i < length; i++) {
            newBuf[i] = str[i];
        }
        newBuf[length] = '\0';
        str = newBuf;
        refCount = new int(1);
    }
}


Mystring::Mystring()
{
    str = new char[1];
    str[0] = '\0';
    length = 0;
    refCount = new int(1);
}

Mystring::Mystring(const char *input)
{
    if (input == nullptr)
    {
        str = new char[1];
        str[0] = '\0';
        length = 0;
        refCount = new int(1);
    }
    else
    {
        allocateAndCopy(input, strlen(input));
    }
}

Mystring::Mystring(const Mystring &other)
{
    str = other.str;
    length = other.length;
    refCount = other.refCount;
    (*refCount)++;
}

Mystring::~Mystring()
{
    (*refCount)--;
    if (*refCount == 0)
    {
        delete[] str;
        delete refCount;
    }
}

Mystring &Mystring::operator=(const Mystring &other) {
    if (this != &other) {
        (*refCount)--;
        if (*refCount == 0) {
            delete[] str;
            delete refCount;
        }
        str = other.str;
        length = other.length;
        refCount = other.refCount;
        (*refCount)++;
    }
    return *this;
}


Mystring Mystring::operator+(const Mystring &other)
{
    detach();
    Mystring newStr;
    delete[] newStr.str;

    int thisLength = length;
    int otherLength = other.length;
    newStr.length = thisLength + otherLength;
    newStr.str = new char[newStr.length + 1];

    int i = 0;
    for (; i < thisLength; i++)
    {
        newStr.str[i] = this->str[i];
    }

    for (int j = 0; j < otherLength; j++, i++)
    {
        newStr.str[i] = other.str[j];
    }

    newStr.str[thisLength + otherLength] = '\0';
    delete newStr.refCount;
    newStr.refCount = new int(1);
    return newStr;
}

Mystring &Mystring::operator+=(const Mystring &other)
{
    detach();
    int newLength = length + other.length;
    char *newBuf = new char[newLength + 1];

    int i = 0;
    for (; i < length; i++)
        newBuf[i] = str[i];

    for (int j = 0; j < other.length; j++, i++)
        newBuf[i] = other.str[j];

    newBuf[newLength] = '\0';

    delete[] str;
    str = newBuf;
    length = newLength;
    return *this;
}

bool Mystring::operator==(const Mystring &other) const
{
    if (length != other.length)
        return false;
    for (int i = 0; i < length; i++)
    {
        if (str[i] != other.str[i])
            return false;
    }
    return true;
}

bool Mystring::operator!=(const Mystring &other) const
{
    return !(*this == other);
}

bool Mystring::operator<(const Mystring &other) const
{
    int minLen = length < other.length ? length : other.length;

    for (int i = 0; i < minLen; i++)
    {
        if(str[i] == other.str[i])
            continue;
        return str[i] < other.str[i];
    }
    return length < other.length;
}

bool Mystring::operator>(const Mystring &other) const
{
    return other < *this;
}

bool Mystring::operator<=(const Mystring &other) const
{
    return !(*this > other);
}

bool Mystring::operator>=(const Mystring &other) const
{
    return !(*this < other);
}

char &Mystring::operator[](int index)
{
    if (index < 0 || index >= length)
        throw out_of_range("Index out of range");
    detach();
    return str[index];
}

const char &Mystring::operator[](int index) const
{
    if (index < 0 || index >= length)
        throw out_of_range("Index out of range");
    return str[index];
}

int Mystring::Length() const
{
    return length;
}

void Mystring::Print() const
{
    cout << str;
}

int Mystring::CountRef() const
{
    return *refCount;
}

const char *Mystring::c_str() const
{
    return str;
}

void Mystring::Clear()
{
    detach();
    delete[] str;
    str = new char[1];
    str[0] = '\0';
    length = 0;
}


int Mystring::Find(char c) const
{
    for (int i = 0; i < length; i++)
    {
        if (str[i] == c)
            return i;
    }
    return -1;
}

int Mystring::Find(const Mystring& substr) const
{
    int subLen = substr.length;
    if (subLen == 0) return 0;
    
    for (int i = 0; i <= length - subLen; i++)
    {
        bool found = true;
        for (int j = 0; j < subLen; j++)
        {
            if (str[i + j] != substr.str[j])
            {
                found = false;
                break;
            }
        }
        if (found)
            return i;
    }
    return -1;
}
