#include <iostream>
#include <memory>
#include "include/array.h"
#include "include/square.h"
#include "include/rectangle.h"
#include "include/triangle.h"

int main() {
    try {
        // Create array for storing figures with double type
        FigureArray<double> figureArray;

        std::cout << "=== ADDING FIGURES TO ARRAY ===" << std::endl;

        // Add squares
        auto square1 = std::make_shared<Square<double>>(
            Point<double>(0, 0),
            Point<double>(2, 0),
            Point<double>(2, 2),
            Point<double>(0, 2)
        );
        figureArray.add(square1);

        auto square2 = std::make_shared<Square<double>>(
            Point<double>(1, 1),
            Point<double>(3, 1),
            Point<double>(3, 3),
            Point<double>(1, 3)
        );
        figureArray.add(square2);

        // Add rectangles
        auto rectangle1 = std::make_shared<Rectangle<double>>(
            Point<double>(0, 0),
            Point<double>(4, 0),
            Point<double>(4, 1),
            Point<double>(0, 1)
        );
        figureArray.add(rectangle1);

        auto rectangle2 = std::make_shared<Rectangle<double>>(
            Point<double>(2, 2),
            Point<double>(6, 2),
            Point<double>(6, 4),
            Point<double>(2, 4)
        );
        figureArray.add(rectangle2);

        // Add triangles
        auto triangle1 = std::make_shared<Triangle<double>>(
            Point<double>(0, 0),
            Point<double>(3, 0),
            Point<double>(0, 4)
        );
        figureArray.add(triangle1);

        auto triangle2 = std::make_shared<Triangle<double>>(
            Point<double>(1, 1),
            Point<double>(5, 1),
            Point<double>(3, 5)
        );
        figureArray.add(triangle2);

        std::cout << "\n=== FIGURE INFORMATION ===" << std::endl;
        
        // Display all figures
        std::cout << "\n--- All Figures ---" << std::endl;
        for (size_t i = 0; i < figureArray.size(); ++i) {
            std::cout << i << ": " << figureArray[i] << std::endl;
        }

        // Display areas
        std::cout << "\n--- Figure Areas ---" << std::endl;
        figureArray.displayAreas();

        // Display centroids
        std::cout << "\n--- Figure Centroids ---" << std::endl;
        figureArray.displayCentroids();

        // Total area
        std::cout << "\n--- Total Area ---" << std::endl;
        std::cout << "Total area of all figures: " << figureArray.computeTotalArea() << std::endl;

        // Array size
        std::cout << "\n--- Array Information ---" << std::endl;
        std::cout << "Number of figures in array: " << figureArray.size() << std::endl;

        std::cout << "\n=== TESTING ARRAY OPERATIONS ===" << std::endl;

        // Test element access
        std::cout << "\n--- Element Access ---" << std::endl;
        std::cout << "First figure: " << figureArray[0] << std::endl;
        std::cout << "Area of first figure: " << static_cast<double>(figureArray[0]) << std::endl;

        // Demonstrate erase function
        std::cout << "\n=== DEMONSTRATING ERASE FUNCTION ===" << std::endl;
        
        std::cout << "Array state before deletion:" << std::endl;
        for (size_t i = 0; i < figureArray.size(); ++i) {
            std::cout << i << ": " << figureArray[i] << " | Area = " << static_cast<double>(figureArray[i]) << std::endl;
        }
        
        // Delete several figures
        std::cout << "\nDeleting figure at index 1 (second square)" << std::endl;
        figureArray.erase(1);
        
        std::cout << "Array state after deleting index 1:" << std::endl;
        for (size_t i = 0; i < figureArray.size(); ++i) {
            std::cout << i << ": " << figureArray[i] << " | Area = " << static_cast<double>(figureArray[i]) << std::endl;
        }
        
        std::cout << "\nDeleting figure at index 2 (now second rectangle)" << std::endl;
        figureArray.erase(2);
        
        std::cout << "Array state after deleting index 2:" << std::endl;
        for (size_t i = 0; i < figureArray.size(); ++i) {
            std::cout << i << ": " << figureArray[i] << " | Area = " << static_cast<double>(figureArray[i]) << std::endl;
        }

        // Total area after deletion
        std::cout << "\n--- Total Area After Deletions ---" << std::endl;
        std::cout << "Total area: " << figureArray.computeTotalArea() << std::endl;
        std::cout << "Number of figures after deletions: " << figureArray.size() << std::endl;

        // Attempt to delete non-existent index (should throw exception)
        std::cout << "\n--- Attempting to Delete Non-existent Index ---" << std::endl;
        try {
            figureArray.erase(10); // This index should be invalid
        } catch (const std::out_of_range& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
            std::cout << "This is expected behavior!" << std::endl;
        }

        std::cout << "\n=== TESTING DIFFERENT DATA TYPES ===" << std::endl;

        // Test with float type
        FigureArray<float> floatArray;
        
        auto floatSquare = std::make_shared<Square<float>>(
            Point<float>(0.5f, 0.5f),
            Point<float>(2.5f, 0.5f),
            Point<float>(2.5f, 2.5f),
            Point<float>(0.5f, 2.5f)
        );
        floatArray.add(floatSquare);

        auto floatTriangle = std::make_shared<Triangle<float>>(
            Point<float>(0.0f, 0.0f),
            Point<float>(2.0f, 0.0f),
            Point<float>(1.0f, 1.732f)  // Equilateral triangle
        );
        floatArray.add(floatTriangle);

        std::cout << "Float array - number of figures: " << floatArray.size() << std::endl;
        
        // Demonstrate erase for float array
        std::cout << "Demonstrating erase for float array:" << std::endl;
        floatArray.displayAreas();
        std::cout << "Deleting first figure..." << std::endl;
        floatArray.erase(0);
        std::cout << "Number of figures after deletion: " << floatArray.size() << std::endl;
        floatArray.displayAreas();

        // Test with int type
        FigureArray<int> intArray;
        
        auto intSquare = std::make_shared<Square<int>>(
            Point<int>(0, 0),
            Point<int>(3, 0),
            Point<int>(3, 3),
            Point<int>(0, 3)
        );
        intArray.add(intSquare);

        auto intRectangle = std::make_shared<Rectangle<int>>(
            Point<int>(0, 0),
            Point<int>(5, 0),
            Point<int>(5, 2),
            Point<int>(0, 2)
        );
        intArray.add(intRectangle);

        std::cout << "\nInt array - number of figures: " << intArray.size() << std::endl;
        intArray.displayAreas();

        std::cout << "\n=== TESTING MOVE OPERATIONS ===" << std::endl;

        // Test move constructor
        FigureArray<double> movedArray(std::move(figureArray));
        std::cout << "Moved array - number of figures: " << movedArray.size() << std::endl;
        std::cout << "Original array after move - number of figures: " << figureArray.size() << std::endl;

        std::cout << "\n=== PROGRAM SUCCESSFULLY COMPLETED ===" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
   
    return 0;
}