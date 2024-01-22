//
//  Fraction.cpp
//  Fraction
//
//  Created by Laura Zhang on 9/16/22.
//

#include "Fraction.hpp"

#include <numeric>

Fraction::Fraction() {
    _numerator = 0;
    _denominator = 1;
    _real_representation = 0.0;
    _gcd = 1;
    _lcm = 1;
}

Fraction::Fraction(const int numerator, const int denominator) {
    assert((_denominator != 0) && "The denominator should not be 0!");
    
    _gcd = std::gcd(_numerator, _denominator);
    
    _numerator = numerator / _gcd;
    _denominator = denominator / _gcd;
    
    _real_representation = numerator * 1.0 / denominator;
    
    _lcm = std::lcm(_numerator, _denominator);
}

// copy constructor
Fraction::Fraction(const Fraction& f) {
    _numerator = f._numerator;
    _denominator = f._denominator;
    _real_representation = f._real_representation;
    _gcd = f._gcd;
    _lcm = f._lcm;
}

Fraction& Fraction::operator+=(const Fraction& rhs) {
    if (_denominator == rhs._denominator) {
        _numerator += rhs._numerator;
    }
    
    else {
        _numerator = _numerator * rhs._denominator + _denominator * rhs._numerator;
        _denominator *= rhs._denominator;
    }
    
    simplifyFraction(* this);
    
    return * this;
}

Fraction& Fraction::pow(int exponent) {
    _numerator = std::pow(_numerator, exponent);
    _denominator = std::pow(_denominator, exponent);
    return * this;
}

Fraction& Fraction::pow(const Fraction& exponent) {
    _numerator = std::pow(_numerator, exponent._real_representation);
    _denominator = std::pow(_denominator, exponent._real_representation);
    return * this;
}

void Fraction::simplifyFraction(const Fraction& f) {
    _gcd = std::gcd(_numerator, _denominator);
    
    _numerator /= _gcd;
    _denominator /= _gcd;
}
