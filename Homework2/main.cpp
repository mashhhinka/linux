// main.cpp
#include <iostream>
#include "ComplexNumber.h"
#include "sort_complex.h"

int main() {
    // Define the number of ComplexNumbers
    const int SIZE = 5;

    // Create an array of ComplexNumbers
    ComplexNumber complexArr[SIZE] = {
        ComplexNumber(140,54),    
        ComplexNumber(67,5),   
        ComplexNumber(1, 8),   
         
        
    };

    // Display original array
    std::cout << "Original Complex Numbers:\n";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << complexArr[i] << " | Absolute Value: " << complexArr[i].abs() << "\n";
    }

    // Sort the array
    sortComplexNumbers(complexArr, SIZE);

    // Display sorted array
    std::cout << "\nSorted Complex Numbers (by absolute value):\n";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << complexArr[i] << " | Absolute Value: " << complexArr[i].abs() << "\n";
    }

    return 0;
}
