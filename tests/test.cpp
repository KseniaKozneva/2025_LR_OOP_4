#include <gtest/gtest.h>
#include <sstream>
#include <memory>
#include "../include/figure.h"
#include "../include/square.h"
#include "../include/rectangle.h"
#include "../include/triangle.h"
#include "../include/array.h"
#include "../include/points.h"
 
// Тесты для класса Point
TEST(PointTest, ParameterConstructor) {
    Point<int> p(3, 4);
    EXPECT_EQ(p.getX(), 3);
    EXPECT_EQ(p.getY(), 4);
}
  
TEST(PointFloatTest, ParameterConstructor) {
    Point<float> p(3.5f, 4.2f);
    EXPECT_FLOAT_EQ(p.getX(), 3.5f);
    EXPECT_FLOAT_EQ(p.getY(), 4.2f);
}

// Тесты для класса Square
TEST(SquareTest, DefaultConstructor) {
    Square<int> s;
    Point<int> centroid = s.getCentroid();
    EXPECT_EQ(centroid.getX(), 0);
    EXPECT_EQ(centroid.getY(), 0);
}

TEST(SquareTest, AreaCalculation) {
    Square<int> s(
        Point<int>(0, 0),
        Point<int>(2, 0),
        Point<int>(2, 2),
        Point<int>(0, 2)
    );
    EXPECT_NEAR(static_cast<double>(s), 4.0, 0.001);
}

TEST(SquareTest, ValidityCheck) {
    Square<int> validSquare(
        Point<int>(0, 0),
        Point<int>(2, 0),
        Point<int>(2, 2),
        Point<int>(0, 2)
    );
    EXPECT_TRUE(validSquare.checkValidity());
}

// Тесты для класса Square с float
TEST(SquareFloatTest, DefaultConstructor) {
    Square<float> s;
    Point<float> centroid = s.getCentroid();
    EXPECT_FLOAT_EQ(centroid.getX(), 0.5f);
    EXPECT_FLOAT_EQ(centroid.getY(), 0.5f);
}

TEST(SquareFloatTest, AreaCalculation) {
    Square<float> s(
        Point<float>(0.0f, 0.0f),
        Point<float>(2.5f, 0.0f),
        Point<float>(2.5f, 2.5f),
        Point<float>(0.0f, 2.5f)
    );
    EXPECT_NEAR(static_cast<double>(s), 6.25, 0.001);
}

TEST(SquareFloatTest, ValidityCheck) {
    Square<float> validSquare(
        Point<float>(1.0f, 1.0f),
        Point<float>(3.5f, 1.0f),
        Point<float>(3.5f, 3.5f),
        Point<float>(1.0f, 3.5f)
    );
    EXPECT_TRUE(validSquare.checkValidity());
}

// Тесты для класса Rectangle
TEST(RectangleTest, DefaultConstructor) {
    Rectangle<int> r;
    Point<int> centroid = r.getCentroid();
    EXPECT_EQ(centroid.getX(), 1);
    EXPECT_EQ(centroid.getY(), 0);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle<int> r(
        Point<int>(0, 0),
        Point<int>(4, 0),
        Point<int>(4, 2),
        Point<int>(0, 2)
    );
    EXPECT_NEAR(static_cast<double>(r), 8.0, 0.001);
}

// Тесты для класса Rectangle с float
TEST(RectangleFloatTest, DefaultConstructor) {
    Rectangle<float> r;
    Point<float> centroid = r.getCentroid();
    EXPECT_FLOAT_EQ(centroid.getX(), 1.0f);
    EXPECT_FLOAT_EQ(centroid.getY(), 0.5f);
}

TEST(RectangleFloatTest, AreaCalculation) {
    Rectangle<float> r(
        Point<float>(0.0f, 0.0f),
        Point<float>(4.5f, 0.0f),
        Point<float>(4.5f, 2.5f),
        Point<float>(0.0f, 2.5f)
    );
    EXPECT_NEAR(static_cast<double>(r), 11.25, 0.001);
}

// Тесты для класса Triangle
TEST(TriangleTest, DefaultConstructor) {
    Triangle<int> t;
    Point<int> centroid = t.getCentroid();
    EXPECT_EQ(centroid.getX(), 0);
    EXPECT_EQ(centroid.getY(), 0);
}

TEST(TriangleTest, AreaCalculation) {
    Triangle<int> t(
        Point<int>(0, 0),
        Point<int>(3, 0),
        Point<int>(0, 4)
    );
    EXPECT_NEAR(static_cast<double>(t), 6.0, 0.001);
}

TEST(TriangleTest, InvalidTriangle) {
    Triangle<int> invalidTriangle(
        Point<int>(0, 0),
        Point<int>(1, 1),
        Point<int>(2, 2)
    );
    EXPECT_FALSE(invalidTriangle.checkValidity());
}

// Тесты для класса Triangle с float
TEST(TriangleFloatTest, DefaultConstructor) {
    Triangle<float> t;
    Point<float> centroid = t.getCentroid();
    EXPECT_FLOAT_EQ(centroid.getX(), 0.33333334f);
    EXPECT_FLOAT_EQ(centroid.getY(), 0.33333334f);
}

TEST(TriangleFloatTest, AreaCalculation) {
    Triangle<float> t(
        Point<float>(0.0f, 0.0f),
        Point<float>(3.5f, 0.0f),
        Point<float>(0.0f, 4.2f)
    );
    EXPECT_NEAR(static_cast<double>(t), 7.35, 0.001);
}

TEST(TriangleFloatTest, InvalidTriangle) {
    Triangle<float> invalidTriangle(
        Point<float>(0.0f, 0.0f),
        Point<float>(1.1f, 1.1f),
        Point<float>(2.2f, 2.2f)
    );
    EXPECT_FALSE(invalidTriangle.checkValidity());
}

// Тесты для класса FigureArray
TEST(FigureArrayTest, DefaultConstructor) {
    FigureArray<int> array;
    EXPECT_EQ(array.size(), 0);
}

TEST(FigureArrayTest, AddFigures) {
    FigureArray<int> array;
    
    auto square = std::make_shared<Square<int>>(
        Point<int>(0, 0),
        Point<int>(2, 0),
        Point<int>(2, 2),
        Point<int>(0, 2)
    );
    
    array.add(square);
    EXPECT_EQ(array.size(), 1);
}

TEST(FigureArrayTest, EraseFigure) {
    FigureArray<int> array;
    
    auto square1 = std::make_shared<Square<int>>(
        Point<int>(0, 0),
        Point<int>(2, 0),
        Point<int>(2, 2),
        Point<int>(0, 2)
    );
    
    auto square2 = std::make_shared<Square<int>>(
        Point<int>(1, 1),
        Point<int>(3, 1),
        Point<int>(3, 3),
        Point<int>(1, 3)
    );
    
    array.add(square1);
    array.add(square2);
    
    EXPECT_EQ(array.size(), 2);
    array.erase(0);
    EXPECT_EQ(array.size(), 1);
}

TEST(FigureArrayTest, TotalArea) {
    FigureArray<int> array;
    
    auto square1 = std::make_shared<Square<int>>(
        Point<int>(0, 0),
        Point<int>(2, 0),
        Point<int>(2, 2),
        Point<int>(0, 2)
    );
    
    auto square2 = std::make_shared<Square<int>>(
        Point<int>(1, 1),
        Point<int>(3, 1),
        Point<int>(3, 3),
        Point<int>(1, 3)
    );
    
    array.add(square1);
    array.add(square2);
    
    double totalArea = array.computeTotalArea();
    EXPECT_NEAR(totalArea, 8.0, 0.001);
}

// Тесты для класса FigureArray с float
TEST(FigureArrayFloatTest, AddFigures) {
    FigureArray<float> array;
    
    auto square = std::make_shared<Square<float>>(
        Point<float>(0.0f, 0.0f),
        Point<float>(2.5f, 0.0f),
        Point<float>(2.5f, 2.5f),
        Point<float>(0.0f, 2.5f)
    );
    
    array.add(square);
    EXPECT_EQ(array.size(), 1);
}

TEST(FigureArrayFloatTest, TotalArea) {
    FigureArray<float> array;
    
    auto square1 = std::make_shared<Square<float>>(
        Point<float>(0.0f, 0.0f),
        Point<float>(2.5f, 0.0f),
        Point<float>(2.5f, 2.5f),
        Point<float>(0.0f, 2.5f)
    );
    
    auto triangle = std::make_shared<Triangle<float>>(
        Point<float>(0.0f, 0.0f),
        Point<float>(3.0f, 0.0f),
        Point<float>(0.0f, 4.0f)
    );
    
    array.add(square1);
    array.add(triangle);
    
    double totalArea = array.computeTotalArea();
    EXPECT_NEAR(totalArea, 12.25, 0.001);
}

TEST(FigureArrayFloatTest, MixedFigures) {
    FigureArray<float> array;
    
    auto square = std::make_shared<Square<float>>(
        Point<float>(1.0f, 1.0f),
        Point<float>(3.0f, 1.0f),
        Point<float>(3.0f, 3.0f),
        Point<float>(1.0f, 3.0f)
    );
    
    auto rectangle = std::make_shared<Rectangle<float>>(
        Point<float>(0.0f, 0.0f),
        Point<float>(5.0f, 0.0f),
        Point<float>(5.0f, 2.0f),
        Point<float>(0.0f, 2.0f)
    );
    
    auto triangle = std::make_shared<Triangle<float>>(
        Point<float>(0.0f, 0.0f),
        Point<float>(4.0f, 0.0f),
        Point<float>(0.0f, 3.0f)
    );
    
    array.add(square);
    array.add(rectangle);
    array.add(triangle);
    
    EXPECT_EQ(array.size(), 3);
    double totalArea = array.computeTotalArea();
    EXPECT_NEAR(totalArea, 20.0, 0.001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}