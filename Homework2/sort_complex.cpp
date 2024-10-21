// sort_complex.cpp
#include "sort_complex.h"

// Function to sort using Selection Sort based on absolute value
void sortComplexNumbers(ComplexNumber arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        // Assume the minimum is the first element
        int min_idx = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j].abs() < arr[min_idx].abs()) {
                min_idx = j;
            }
        }
        // Swap if a smaller element was found
        if (min_idx != i) {
            ComplexNumber temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}
