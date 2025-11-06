#ifndef POINTS_H
#define POINTS_H

#include <iostream>
#include <cmath>
#include <concepts>

// Константа для сравнения чисел с плавающей точкой
const double EPS = 1e-6;
inline const double PI = 3.14159265358979323846;

// Концепт для проверки, что тип T является скалярным
template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

// Шаблонный класс Point
template <Scalar T>
class Point {
protected:
    T _x;  
    T _y;  
    
public:
    Point();
    Point(T x, T y);
    Point(const Point& other);
    Point(Point&& other) noexcept;

    T getX() const;
    T getY() const;

    Point& operator=(const Point& other);
    Point& operator=(Point&& other) noexcept;

    bool operator==(const Point& other) const;
    bool operator<(const Point& other) const;

    std::ostream& print(std::ostream& os) const;

    template <Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Point<U>& point);
    template <Scalar U>
    friend std::istream& operator>>(std::istream& is, Point<U>& point);
};

// Конструктор по умолчанию
template <Scalar T>
Point<T>::Point() : _x(0), _y(0) {}

// Конструктор с параметрами
template <Scalar T>
Point<T>::Point(T x, T y) : _x(x), _y(y) {}

// Конструктор копирования
template <Scalar T>
Point<T>::Point(const Point& other) : _x(other._x), _y(other._y) {}

// Конструктор перемещения
template <Scalar T>
Point<T>::Point(Point&& other) noexcept : _x(std::move(other._x)), _y(std::move(other._y)) {}

// Метод для получения значения координаты X
template <Scalar T>
T Point<T>::getX() const {
    return _x;
}

// Метод для получения значения координаты Y
template <Scalar T>
T Point<T>::getY() const {
    return _y;
}

// Оператор присваивания копированием
template <Scalar T>
Point<T>& Point<T>::operator=(const Point& other) {
    if (this != &other) {
        _x = other._x;
        _y = other._y;
    }
    return *this;
}

// Оператор присваивания перемещением
template <Scalar T>
Point<T>& Point<T>::operator=(Point&& other) noexcept {
    if (this != &other) {
        _x = std::move(other._x);
        _y = std::move(other._y);
    }
    return *this;
}

// Оператор сравнения - равенство
template <Scalar T>
bool Point<T>::operator==(const Point& other) const {
    return std::abs(_x - other._x) < EPS && std::abs(_y - other._y) < EPS;
}

// Оператор сравнения - "меньше"
template <Scalar T>
bool Point<T>::operator<(const Point& other) const {
    return _x < other._x || (_x == other._x && _y < other._y);
}

// Метод для вывода координат в поток
template <Scalar T>
std::ostream& Point<T>::print(std::ostream& os) const {
    return os << "(" << _x << ", " << _y << ")";
}

template <Scalar U>
std::ostream& operator<<(std::ostream& os, const Point<U>& point) {
    return os << "(" << point._x << ", " << point._y << ")";
}

template <Scalar U>
std::istream& operator>>(std::istream& is, Point<U>& point) {
    return is >> point._x >> point._y;
}

#endif