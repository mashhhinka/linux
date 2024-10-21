
// ComplexNumber.h
#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <cmath>
#include <iostream>

class ComplexNumber {
private:
    double real;
    double imag;

public:
    // Constructors
    ComplexNumber();
    ComplexNumber(double r, double i);

    // Getter methods
    double getReal() const;
    double getImag() const;

    // Basic operations
    ComplexNumber operator+(const ComplexNumber& other) const;
    ComplexNumber operator-(const ComplexNumber& other) const;
    ComplexNumber operator*(double constant) const;

    // Absolute value
    double abs() const;

    // Friend function for output
    friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& cn);
};

#endif // COMPLEXNUMBER_H
