#pragma once
#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

class Mystring
{
private:
    char *str;     // Указатель на строку
    int length;    // Длина строки
    int *refCount; // Счётчик ссылок

    // Создаёт новый буфер и копирует туда данные
    void allocateAndCopy(const char *source, int len);

    // Отделяет буфер при copy-on-write
    void detach();

public:
    // Конструкторы и деструктор
    Mystring();                      // по умолчанию
    Mystring(const char *input);     // из C-строки
    Mystring(const Mystring &other); // копирования
    ~Mystring();                     // деструктор

    // Операторы
    Mystring &operator=(const Mystring &other);  // присваивание
    Mystring operator+(const Mystring &other);   // конкатенация
    Mystring &operator+=(const Mystring &other); // добавление к себе

    bool operator==(const Mystring &other) const; // равенство
    bool operator!=(const Mystring &other) const; // неравенство
    bool operator<(const Mystring &other) const;  // меньше
    bool operator>(const Mystring &other) const;  // больше
    bool operator<=(const Mystring &other) const; // меньше или равно
    bool operator>=(const Mystring &other) const; // больше или равно

    char &operator[](int index);             // доступ по индексу (с изменением)
    const char &operator[](int index) const; // доступ по индексу (только чтение)

    // Методы
    int Length() const;        // длина строки
    void Print() const;        // вывод в консоль
    int CountRef() const;      // количество ссылок
    void Clear();              // очистка строки
    const char *c_str() const; // получить C-строку
};
