// ComplexNumber.cpp
#include "ComplexNumber.h"

// Constructors
ComplexNumber::ComplexNumber() : real(0.0), imag(0.0) {}

ComplexNumber::ComplexNumber(double r, double i) : real(r), imag(i) {}

// Getter methods
double ComplexNumber::getReal() const {
    return real;
}

double ComplexNumber::getImag() const {
    return imag;
}

// Basic operations
ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) const {
    return ComplexNumber(real + other.real, imag + other.imag);
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& other) const {
    return ComplexNumber(real - other.real, imag - other.imag);
}

ComplexNumber ComplexNumber::operator*(double constant) const {
    return ComplexNumber(real * constant, imag * constant);
}

// Absolute value
double ComplexNumber::abs() const {
    return std::sqrt(real * real + imag * imag);
}

// Friend function for output
std::ostream& operator<<(std::ostream& os, const ComplexNumber& cn) {
    os << "(" << cn.real << " " << (cn.imag >= 0 ? "+" : "-") << " " 
       << std::abs(cn.imag) << "i)";
    return os;
}
