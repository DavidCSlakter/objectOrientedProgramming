//
//  Rational.hpp
//  Warriors5
//
//  Created by David Slakter on 3/23/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#ifndef Rational_hpp
#define Rational_hpp

#include <iostream>

namespace CS2124 {

    class Rational {
    public:
        friend bool operator==(const Rational& lhs, const Rational& rhs);
        
        friend void normalize(Rational& rational);
        
        /***************** Input/Output**************/
        friend std::ostream& operator<<(std::ostream& os, const Rational fraction);
        friend std::istream& operator>>(std::istream& is, Rational& fraction);
        /***************** Constructors**************/
        Rational();
        
        Rational(int top);
        
        Rational(int top, int bottom);
        
        /************ Operators *****************/
        Rational& operator+=(const Rational& rhs);
        
        //++c1
        Rational& operator++();
        //c1++
        Rational operator++(int);
        
        explicit operator bool() const;
        
        
    private:
        int numerator;
        int denominator;
    };
    
    bool operator!=(const Rational& lhs, const Rational& rhs);
    
    Rational operator+(const Rational& lhs, const Rational& rhs);
    
    Rational& operator--(Rational& frac);
    
    Rational operator--(Rational& frac, int);
    
    int greatestCommonDivisor(int x, int y);
    
}


#endif /* Rational_hpp */
