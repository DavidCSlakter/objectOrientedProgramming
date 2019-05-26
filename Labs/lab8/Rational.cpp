//
//  Rational.cpp
//  Warriors5
//
//  Created by David Slakter on 3/23/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include "Rational.hpp"
using namespace std;

namespace CS2124 {
    
    int greatestCommonDivisor(int x, int y) {
        while (y != 0) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        return x;
    }
    
    ostream& operator<<(ostream& os, const Rational fraction){
        os << fraction.numerator << "/" << fraction.denominator << endl;
        return os;
    }
    istream& operator>>(istream& is, Rational& fraction){
        int top;
        char delim;
        int bottom;
        is >> top;
        is >> delim;
        is >> bottom;
      
        if (bottom < 0){
            top*=-1;
            bottom*=-1;
        }
        int GCD = greatestCommonDivisor(top, bottom);
        top /= GCD;
        bottom /= GCD;
        fraction.numerator = top;
        fraction.denominator = bottom;
        return is;
    }
    
    Rational::Rational(): numerator(0), denominator(0){}
    
    Rational::Rational(int top): numerator(top), denominator(1){}
    
    Rational::Rational(int top, int bottom) {
        if (bottom < 0){
            top*=-1;
            bottom*=-1;
        }
        int GCD = greatestCommonDivisor(top, bottom);
        top /= GCD;
        bottom /= GCD;
        numerator = top;
        denominator = bottom;
    }
    
   Rational& Rational::operator+=(const Rational& rhs){
        if (denominator != rhs.denominator){
            int tempNumer = rhs.numerator * denominator;
        
            numerator *= rhs.denominator;
            numerator += tempNumer;
            denominator *= rhs.denominator;
            
            int GCD = greatestCommonDivisor(numerator, denominator);
            numerator /= GCD;
            denominator /= GCD;
        }
        else{
            numerator += rhs.numerator;
        }
        return *this;
    }
    
     //++c1
    Rational& Rational::operator++() {
        numerator += denominator;
   
        return *this;
    }
    
    //c1++
    Rational Rational::operator++(int){ //return copy because it is a local variable
    
        Rational result(*this);
        numerator += denominator;
        
        return result;
    }
    
    Rational::operator bool() const { //otherwise ambiguities exist
        return numerator != 0;
    }
    
    void normalize(Rational& rational){
            int GCD = greatestCommonDivisor(rational.numerator, rational.denominator);
            rational.numerator /= GCD;
            rational.denominator /= GCD;
    }
    
    bool operator!=(const Rational& lhs, const Rational& rhs){
        return !(lhs == rhs);
    }
    
    Rational operator+(const Rational& lhs, const Rational& rhs){
        Rational result(lhs);
        result += rhs;
        return result;
    }
    
    Rational& operator--(Rational& frac) {
        frac += -1;
        normalize(frac);
        return frac;
        
    }
    
    Rational operator--(Rational& frac, int){ //return copy because it is a local variable

        Rational result(frac);
        frac += -1;
        normalize(frac);
        return result;
    }
    
    bool operator==(const Rational& lhs, const Rational& rhs){
        if(lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator){
            return true;
        }
        else{
            return false;
            
        }
    }

}
