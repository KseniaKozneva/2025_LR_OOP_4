#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <memory>
#include "points.h"
 
// Шаблонный абстрактный класс Figure
template <Scalar T>
class Figure {
    template <Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Figure<U>& fig);
    
    template <Scalar U>
    friend std::istream& operator>>(std::istream& is, Figure<U>& fig);

protected:
    Figure() = default;

public:
    virtual ~Figure() = default;
    
    // Виртуальные методы, которые должны быть реализованы в производных классах
    virtual Point<T> getCentroid() const = 0;
    virtual double calculateArea() const = 0;
    virtual operator double() const = 0;
    
    // Методы для ввода/вывода
    virtual void output(std::ostream& os) const = 0;
    virtual void input(std::istream& is) = 0;
    
    // Методы для проверки
    virtual bool checkValidity() const = 0;
    
    // Операторы сравнения
    virtual bool operator==(const Figure<T>& otherFig) const = 0;
    virtual bool operator!=(const Figure<T>& otherFig) const = 0;
};

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
    figure.output(os);
    return os;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& figure) {
    figure.input(is);
    return is;
}

#endif