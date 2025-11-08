#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"
#include <memory>
#include <cmath>

template <Scalar T>
class Rectangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1, p2, p3, p4;

public:
    Rectangle();
    Rectangle(Point<T> a, Point<T> b, Point<T> c, Point<T> d);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    virtual void output(std::ostream& os) const override;
    virtual void input(std::istream& is) override;
    virtual Point<T> getCentroid() const override;
    virtual double calculateArea() const override;
    virtual operator double() const override;
    virtual bool operator==(const Figure<T>& otherFig) const override;
    virtual bool operator!=(const Figure<T>& otherFig) const override;
    virtual bool checkValidity() const override;
  
    ~Rectangle() = default;
};
 
// Конструктор по умолчанию
template <Scalar T>
Rectangle<T>::Rectangle() 
    : p1(std::make_unique<Point<T>>(T(0), T(0))),
      p2(std::make_unique<Point<T>>(T(2), T(0))),
      p3(std::make_unique<Point<T>>(T(2), T(1))),
      p4(std::make_unique<Point<T>>(T(0), T(1))) {}

// Конструктор с параметрами
template <Scalar T>
Rectangle<T>::Rectangle(Point<T> a, Point<T> b, Point<T> c, Point<T> d)
    : p1(std::make_unique<Point<T>>(a)),
      p2(std::make_unique<Point<T>>(b)),
      p3(std::make_unique<Point<T>>(c)),
      p4(std::make_unique<Point<T>>(d)) {}

// Конструктор копирования
template <Scalar T>
Rectangle<T>::Rectangle(const Rectangle& other)
    : p1(std::make_unique<Point<T>>(*other.p1)),
      p2(std::make_unique<Point<T>>(*other.p2)),
      p3(std::make_unique<Point<T>>(*other.p3)),
      p4(std::make_unique<Point<T>>(*other.p4)) {}

// Конструктор перемещения
template <Scalar T>
Rectangle<T>::Rectangle(Rectangle&& other) noexcept
    : p1(std::move(other.p1)),
      p2(std::move(other.p2)),
      p3(std::move(other.p3)),
      p4(std::move(other.p4)) {}

// Оператор присваивания копированием
template <Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle& other) {
    if (this != &other) {
        p1 = std::make_unique<Point<T>>(*other.p1);
        p2 = std::make_unique<Point<T>>(*other.p2);
        p3 = std::make_unique<Point<T>>(*other.p3);
        p4 = std::make_unique<Point<T>>(*other.p4);
    }
    return *this;
}

// Оператор присваивания перемещением
template <Scalar T>
Rectangle<T>& Rectangle<T>::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
    }
    return *this;
}

// Вывод в поток
template <Scalar T>
void Rectangle<T>::output(std::ostream& os) const {
    os << "Rectangle: " << *p1 << ", " << *p2 << ", " << *p3 << ", " << *p4;
}

// Ввод из потока
template <Scalar T>
void Rectangle<T>::input(std::istream& is) {
    Point<T> a, b, c, d;
    if (is.rdbuf() == std::cin.rdbuf()) {
        std::cout << "Input 4 rectangle vertices (x y format, separated by spaces):\n";
    }
    is >> a >> b >> c >> d;
    
    p1 = std::make_unique<Point<T>>(a);
    p2 = std::make_unique<Point<T>>(b);
    p3 = std::make_unique<Point<T>>(c);
    p4 = std::make_unique<Point<T>>(d);
    
    if (!checkValidity()) {
        throw std::invalid_argument("Invalid rectangle vertices provided!");
    }
}

// Центроид
template <Scalar T>
Point<T> Rectangle<T>::getCentroid() const {
    T x = (p1->getX() + p2->getX() + p3->getX() + p4->getX()) / 4;
    T y = (p1->getY() + p2->getY() + p3->getY() + p4->getY()) / 4;
    return Point<T>(x, y);
}

// Площадь
template <Scalar T>
double Rectangle<T>::calculateArea() const {
    // Вычисляем длины смежных сторон
    double side1 = std::sqrt(
        std::pow(p2->getX() - p1->getX(), 2) + 
        std::pow(p2->getY() - p1->getY(), 2)
    );
    double side2 = std::sqrt(
        std::pow(p4->getX() - p1->getX(), 2) + 
        std::pow(p4->getY() - p1->getY(), 2)
    );
    return side1 * side2;
}

// Оператор приведения к double
template <Scalar T>
Rectangle<T>::operator double() const {
    return calculateArea();
}

// Оператор сравнения
template <Scalar T>
bool Rectangle<T>::operator==(const Figure<T>& otherFig) const {
    const Rectangle* otherRect = dynamic_cast<const Rectangle*>(&otherFig);
    if (!otherRect) return false;
    
    // Проверяем все возможные циклические сдвиги вершин
    const Point<T>* thisPoints[] = {p1.get(), p2.get(), p3.get(), p4.get()};
    const Point<T>* otherPoints[] = {
        otherRect->p1.get(), otherRect->p2.get(), 
        otherRect->p3.get(), otherRect->p4.get()
    };
    
    for (int offset = 0; offset < 4; ++offset) {
        bool isMatch = true;
        for (int i = 0; i < 4; ++i) {
            int shiftedIndex = (i + offset) % 4;
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
bool Rectangle<T>::operator!=(const Figure<T>& otherFig) const {
    return !(*this == otherFig);
}

// Проверка валидности
template <Scalar T>
bool Rectangle<T>::checkValidity() const {
    // Проверка на уникальность точек
    const Point<T>* points[] = {p1.get(), p2.get(), p3.get(), p4.get()};
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (*points[i] == *points[j]) {
                return false;
            }
        }
    }
    
    // Вычисляем длины всех сторон
    double sides[4];
    sides[0] = std::sqrt(std::pow(p2->getX() - p1->getX(), 2) + std::pow(p2->getY() - p1->getY(), 2));
    sides[1] = std::sqrt(std::pow(p3->getX() - p2->getX(), 2) + std::pow(p3->getY() - p2->getY(), 2));
    sides[2] = std::sqrt(std::pow(p4->getX() - p3->getX(), 2) + std::pow(p4->getY() - p3->getY(), 2));
    sides[3] = std::sqrt(std::pow(p1->getX() - p4->getX(), 2) + std::pow(p1->getY() - p4->getY(), 2));
    
    // Проверяем противоположные стороны на равенство
    if (std::abs(sides[0] - sides[2]) > EPS || std::abs(sides[1] - sides[3]) > EPS) {
        return false;
    }
    
    // Проверка прямых углов через скалярное произведение
    double dot1 = (p2->getX() - p1->getX()) * (p4->getX() - p1->getX()) + 
                  (p2->getY() - p1->getY()) * (p4->getY() - p1->getY());
    
    return std::abs(dot1) < EPS; // Скалярное произведение должно быть близко к 0 для прямого угла
}

#endif