#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"
#include <memory>
#include <cmath>

template <Scalar T>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1, p2, p3;

public:
    Triangle();
    Triangle(Point<T> a, Point<T> b, Point<T> c);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;
    Triangle& operator=(const Triangle& other);
    Triangle& operator=(Triangle&& other) noexcept;

    virtual void output(std::ostream& os) const override;
    virtual void input(std::istream& is) override;
    virtual Point<T> getCentroid() const override;
    virtual double calculateArea() const override;
    virtual operator double() const override;
    virtual bool operator==(const Figure<T>& otherFig) const override;
    virtual bool operator!=(const Figure<T>& otherFig) const override;
    virtual bool checkValidity() const override;
 
    ~Triangle() = default;
};

// Конструктор по умолчанию
template <Scalar T>
Triangle<T>::Triangle() 
    : p1(std::make_unique<Point<T>>(T(0), T(0))),
      p2(std::make_unique<Point<T>>(T(1), T(0))),
      p3(std::make_unique<Point<T>>(T(0), T(1))) {}

// Конструктор с параметрами
template <Scalar T>
Triangle<T>::Triangle(Point<T> a, Point<T> b, Point<T> c)
    : p1(std::make_unique<Point<T>>(a)),
      p2(std::make_unique<Point<T>>(b)),
      p3(std::make_unique<Point<T>>(c)) {}

// Конструктор копирования
template <Scalar T>
Triangle<T>::Triangle(const Triangle& other)
    : p1(std::make_unique<Point<T>>(*other.p1)),
      p2(std::make_unique<Point<T>>(*other.p2)),
      p3(std::make_unique<Point<T>>(*other.p3)) {}

// Конструктор перемещения
template <Scalar T>
Triangle<T>::Triangle(Triangle&& other) noexcept
    : p1(std::move(other.p1)),
      p2(std::move(other.p2)),
      p3(std::move(other.p3)) {}

// Оператор присваивания копированием
template <Scalar T>
Triangle<T>& Triangle<T>::operator=(const Triangle& other) {
    if (this != &other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
    }
    return *this;
}

// Оператор присваивания перемещением
template <Scalar T>
Triangle<T>& Triangle<T>::operator=(Triangle&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
    }
    return *this;
}

// Вывод в поток
template <Scalar T>
void Triangle<T>::output(std::ostream& os) const {
    os << "Triangle: " << *p1 << ", " << *p2 << ", " << *p3;
}

// Ввод из потока
template <Scalar T>
void Triangle<T>::input(std::istream& is) {
    Point<T> a, b, c;
    if (is.rdbuf() == std::cin.rdbuf()) {
        std::cout << "Input 3 triangle vertices (x y format, separated by spaces):\n";
    }
    is >> a >> b >> c;
    
    p1 = std::make_unique<Point<T>>(a);
    p2 = std::make_unique<Point<T>>(b);
    p3 = std::make_unique<Point<T>>(c);
    
    if (!checkValidity()) {
        throw std::invalid_argument("Invalid triangle vertices provided!");
    }
}

// Центроид
template <Scalar T>
Point<T> Triangle<T>::getCentroid() const {
    T x = (p1->getX() + p2->getX() + p3->getX()) / 3;
    T y = (p1->getY() + p2->getY() + p3->getY()) / 3;
    return Point<T>(x, y);
}

// Площадь (формула Герона)
template <Scalar T>
double Triangle<T>::calculateArea() const {
    double a = std::sqrt(std::pow(p2->getX() - p1->getX(), 2) + std::pow(p2->getY() - p1->getY(), 2));
    double b = std::sqrt(std::pow(p3->getX() - p2->getX(), 2) + std::pow(p3->getY() - p2->getY(), 2));
    double c = std::sqrt(std::pow(p1->getX() - p3->getX(), 2) + std::pow(p1->getY() - p3->getY(), 2));
    
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

// Оператор приведения к double
template <Scalar T>
Triangle<T>::operator double() const {
    return calculateArea();
}

// Оператор сравнения
template <Scalar T>
bool Triangle<T>::operator==(const Figure<T>& otherFig) const {
    const Triangle* otherTri = dynamic_cast<const Triangle*>(&otherFig);
    if (!otherTri) return false;
    
    // Проверяем все возможные циклические сдвиги вершин
    const Point<T>* thisPoints[] = {p1.get(), p2.get(), p3.get()};
    const Point<T>* otherPoints[] = {
        otherTri->p1.get(), otherTri->p2.get(), otherTri->p3.get()
    };
    
    for (int offset = 0; offset < 3; ++offset) {
        bool isMatch = true;
        for (int i = 0; i < 3; ++i) {
            int shiftedIndex = (i + offset) % 3;
            if (!(*thisPoints[i] == *otherPoints[shiftedIndex])) {
                isMatch = false;
                break;
            }
        }
        if (isMatch) return true;
    }
    return false;
}

// Оператор неравенства
template <Scalar T>
bool Triangle<T>::operator!=(const Figure<T>& otherFig) const {
    return !(*this == otherFig);
}

// Проверка валидности
template <Scalar T>
bool Triangle<T>::checkValidity() const {
    // Проверка на уникальность точек
    const Point<T>* points[] = {p1.get(), p2.get(), p3.get()};
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            if (*points[i] == *points[j]) {
                return false;
            }
        }
    }
    
    // Проверка что точки не лежат на одной прямой
    double area = calculateArea();
    return area > EPS; // Площадь должна быть положительной
}

#endif