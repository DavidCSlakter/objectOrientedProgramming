//
//  Polynomial.hpp
//  ObjectOrientedProgramming
//
//  Created by David Slakter on 5/2/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#ifndef Polynomial_hpp
#define Polynomial_hpp

#include <iostream>
#include <vector>
#include <math.h>

class Polynomial{
public:
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
    
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    
    Polynomial& operator+=(const Polynomial& rhs);
    
    Polynomial(const std::vector<int>& c = {});
    
    Polynomial(const Polynomial& p);
    
    ~Polynomial();
    
    Polynomial& operator=(const Polynomial& rhs);
    int evaluate(int val);
    
private:

    struct Node;
    
    void listAddHead(Node* headPtr, int data);
    void listAddTail(Node* headPtr, int data);

    Node* coefficients;
    int degree;
};

bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
#endif /* Polynomial_hpp */
