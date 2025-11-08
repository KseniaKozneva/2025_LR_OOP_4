#ifndef FIGUREARRAY_H
#define FIGUREARRAY_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include "figure.h"
  
// Шаблонный класс FigureArray
template <typename T>
class FigureArray {
private:
    size_t _size;
    size_t _capacity;
    std::unique_ptr<std::shared_ptr<Figure<T>>[]> _array;

    void reallocate(size_t newCapacity) {
        auto newArray = std::make_unique<std::shared_ptr<Figure<T>>[]>(newCapacity);
        for (size_t i = 0; i < _size; ++i) {
            newArray[i] = std::move(_array[i]);
        }
        _array = std::move(newArray);
        _capacity = newCapacity;
    }

public:
    FigureArray() : _size(0), _capacity(4) {
        _array = std::make_unique<std::shared_ptr<Figure<T>>[]>(_capacity);
    }

    // Конструктор копирования - УДАЛЕН, т.к. unique_ptr нельзя копировать
    FigureArray(const FigureArray& other) = delete;

    // Конструктор перемещения
    FigureArray(FigureArray&& other) noexcept 
        : _size(other._size), _capacity(other._capacity), _array(std::move(other._array)) {
        other._size = 0;
        other._capacity = 0;
    }

    // Оператор присваивания копированием - УДАЛЕН
    FigureArray& operator=(const FigureArray& other) = delete;

    // Оператор присваивания перемещением
    FigureArray& operator=(FigureArray&& other) noexcept {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            _array = std::move(other._array);
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // Добавление через shared_ptr
    void add(std::shared_ptr<Figure<T>> figure) {
        if (_size >= _capacity) {
            reallocate(_capacity * 2);
        }
        _array[_size++] = std::move(figure);
    }

    // Операторы доступа
    Figure<T>& operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of bounds");
        return *_array[index];
    }

    const Figure<T>& operator[](size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of bounds");
        return *_array[index];
    }

    void erase(size_t index) {
        if (index >= _size) throw std::out_of_range("Index invalid");
        
        for (size_t i = index + 1; i < _size; ++i) {
            _array[i - 1] = std::move(_array[i]);
        }
        _array[--_size].reset();
    }

    size_t size() const { return _size; }

    void displayAreas() const {
        std::cout << std::fixed << std::setprecision(2);
        for (size_t i = 0; i < _size; ++i) {
            std::cout << i << ": " << *_array[i]
                      << " | Area = " << static_cast<double>(*_array[i]) << std::endl;
        }
    }

    void displayCentroids() const {
        for (size_t i = 0; i < _size; ++i) {
            Point<T> centroid = _array[i]->getCentroid();
            std::cout << i << ": Centroid = (" << centroid.getX() 
                      << ", " << centroid.getY() << ")" << std::endl;
        }
    }

    double computeTotalArea() const {
        double total = 0.0;
        for (size_t i = 0; i < _size; ++i) {
            total += static_cast<double>(*_array[i]);
        }
        return total;
    }
}; 

#endif