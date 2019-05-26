/*
	testRational.cpp
	CS2124
	Implement the class Rational, so that the following program works.
 */

 //
//#include <iostream>
//
//using namespace std;
//
//
//int greatestCommonDivisor(int x, int y) {
//    while (y != 0) {
//        int temp = x % y;
//        x = y;
//        y = temp;
//    }
//    return x;
//}
//
//
//class Rational {
//public:
//    friend bool operator==(const Rational& lhs, const Rational& rhs);
//
//    friend void normalize(Rational& rational);
//
//        /***************** Input/Output**************/
//    friend ostream& operator<<(ostream& os, const Rational fraction){
//        os << fraction.numerator << "/" << fraction.denominator << endl;
//        return os;
//    }
//    friend istream& operator>>(istream& is, Rational& fraction){
//        int top;
//        char delim;
//        int bottom;
//        is >> top;
//        is >> delim;
//        is >> bottom;
//
//        if (bottom < 0){
//            top*=-1;
//            bottom*=-1;
//        }
//        int GCD = greatestCommonDivisor(top, bottom);
//        top /= GCD;
//        bottom /= GCD;
//        fraction.numerator = top;
//        fraction.denominator = bottom;
//        return is;
//    }
//
//    /***************** Constructors**************/
//    Rational(): numerator(0), denominator(0){}
//
//    Rational(int top): numerator(top), denominator(1){}
//
//    Rational(int top, int bottom) {
//        if (bottom < 0){
//            top*=-1;
//            bottom*=-1;
//        }
//        int GCD = greatestCommonDivisor(top, bottom);
//        top /= GCD;
//        bottom /= GCD;
//        numerator = top;
//        denominator = bottom;
//    }
//
//    /************ Operators *****************/
//    Rational& operator+=(const Rational& rhs){
//        if (denominator != rhs.denominator){
//            int tempNumer = rhs.numerator * denominator;
//
//            numerator *= rhs.denominator;
//            numerator += tempNumer;
//            denominator *= rhs.denominator;
//
//            int GCD = greatestCommonDivisor(numerator, denominator);
//            numerator /= GCD;
//            denominator /= GCD;
//        }
//        else{
//            numerator += rhs.numerator;
//        }
//        return *this;
//    }
//
//    //++c1
//    Rational& operator++() {
//        numerator += denominator;
//        int GCD = greatestCommonDivisor(numerator, denominator);
//        numerator /= GCD;
//        denominator /= GCD;
//
//        return *this;
//    }
//
//    //c1++
//    Rational operator++(int){ //return copy because it is a local variable
//
//        Rational result(*this);
//        numerator += denominator;
//
//        int GCD = greatestCommonDivisor(numerator, denominator);
//        numerator /= GCD;
//        denominator /= GCD;
//
//        return result;
//    }
//
//    explicit operator bool() const { //otherwise ambiguities exist
//        return numerator != 0;
//    }
//
//
//private:
//int numerator;
//int denominator;
//};
//
//
//void normalize(Rational& rational){
//        int GCD = greatestCommonDivisor(rational.numerator, rational.denominator);
//        rational.numerator /= GCD;
//        rational.denominator /= GCD;
//}
//
//Rational operator+(const Rational& lhs, const Rational& rhs){
//    Rational result(lhs);
//    result += rhs;
//    return result;
//}
//
//bool operator==(const Rational& lhs, const Rational& rhs){
//    if(lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator){
//        return true;
//    }
//    else{
//        return false;
//
//    }
//}
//
//bool operator!=(const Rational& lhs, const Rational& rhs){
//    if (lhs == rhs){
//        return false;
//    }
//    else{
//        return true;
//    }
//}
//
////--c1
//Rational& operator--(Rational& frac) {
//    frac += -1;
//    normalize(frac);
//    return frac;
//
//}
////c1--
//Rational operator--(Rational& frac, int){ //return copy because it is a local variable
//
//    Rational result(frac);
//    frac += -1;
//    normalize(frac);
//    return result;
//}
//
//int main() {
//    Rational twoThirds(2,3);
//    cout << twoThirds << endl;
//
//    Rational a, b;
//    cout << "Input two rational numbers.\n";
//    cout << "a: ";
//    cin >> a;
//    cout << "b: ";
//    cin >> b;
//    Rational one(1);
//
//    cout << "a = " << a << endl;
//    cout << "b = " << b << endl;
//    cout << "one = " << one << endl;
//    cout << "a += b: " << (a += b) << endl;    // Implement as member
//    cout << "a = " << a << endl;
//
//    // Implement as non-member, but not a friend
//    cout << "a + one: " << (a + one) << endl;
//    cout << "a == one: " << boolalpha << (a == one) << endl;
//
//    // How does this manage to work?
//    // It does NOT require writing another == operator.
//    cout << "1 == one: " << boolalpha << (1 == one) << endl;
//
//   // Do not implement as friend.
//    cout << "a != one: " << boolalpha << (a != one) << endl;
//
//    cout << "a = " << a << endl;
//    cout << "++a = " << (++a) << endl;
//    cout << "a = " << a << endl;
//    cout << "a++ = " << (a++) << endl;
//    cout << "a = " << a << endl;
//    cout << "--a = " << (--a) << endl;
//    cout << "a = " << a << endl;
//    cout << "a-- = " << (a--) << endl;
//    cout << "a = " << a << endl;
//
//    cout << "++ ++a = " << (++ ++a) << endl;
//    cout << "a = " << a << endl;
//    cout << "-- --a = " << (-- --a) << endl;
//    cout << "a = " << a << endl;
//
//    cout << "a++ ++ = " << (a++ ++) << endl;
//    cout << "a = " << a << endl;
//
//    // Even though the above example, (a++ ++), compiled, the
//    // following shouldn't.
//    // But some compiler vendors might let it...  Is your compiler
//    // doing the right thing?
//    // cout << "a-- -- = " << (a-- --) << endl;
//    // cout << "a = " << a << endl;
//
//
//    if (Rational(1)) {
//        cout << "1 is true" << endl;
//    } else {
//        cout << "1 is false" << endl;
//    }
//    if (Rational(0)) {
//        cout << "0 is true" << endl;
//    } else {
//        cout << "0 is false" << endl;
//   }
//}

#include "Rational.hpp"

using namespace std;
using namespace CS2124;

int main() {
    Rational twoThirds(2,3);
    cout << twoThirds << endl;
    
    Rational a, b;
    cout << "Input two rational numbers.\n";
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    Rational one(1);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (one == 1) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    // cout << "a-- -- = " << (a-- --) << endl;
    // cout << "a = " << a << endl;


    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 
}
