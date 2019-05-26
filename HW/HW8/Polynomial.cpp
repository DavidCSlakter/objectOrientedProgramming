//
//  Polynomial.cpp
//  ObjectOrientedProgramming
//
//  Created by David Slakter on 5/2/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include "Polynomial.hpp"

using namespace std;

/*Node definition for the linked list; includes a next and prev
Node pointer that is initialized to nullptr and a int object
that is initialized to zero*/
struct Polynomial::Node {
    Node(int data = 0, Node* next = nullptr, Node* prev = nullptr)
    : data(data), next(next), prev(prev) {}
    
    int data;
    Node* next;
    Node* prev;
};

/*Adds a Polynomial and sets the result equal to the first
argument*/
Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    Node* p1 = coefficients->next;
    Node* p2 = rhs.coefficients->next;
    
    while (p1 && p2) {
        p1->data += p2->data;
        p1 = p1->next;
        p2 = p2->next;
    }
    if(p2) {
        while (p2) {
            listAddTail(coefficients, p2->data);
            p2 = p2->next;
        }
        degree = rhs.degree;
    }
    
    return *this;
}

/*Constructor for Polynomial; takes a vector that is initialized
defaultly to empty*/
Polynomial::Polynomial(const vector<int>& c): degree(0) {
    
    //creates a blank Node as the header
    coefficients = new Node();
    
    //Adds the vector contents to the linked list
    //in reverse order
    for (int i: c){
        ++degree;
        listAddHead(coefficients, i);
    }
    --degree;
}

//Copy Constructor; copys the linked list and
//degree of Another Polynomial object
Polynomial::Polynomial(const Polynomial& p){
    
    Node* curr = p.coefficients->next;
    coefficients = new Node();

    while(curr){
        listAddTail(coefficients, curr->data);
        curr = curr->next;
    }
    
    degree = p.degree;
}

//Deconstructor; Deletes all the allocated Nodes
//on the linked list
Polynomial::~Polynomial(){
    
    Node* last = coefficients->next;
    
    while(last != nullptr){
        last = last->next;
    }
    while(last){
        delete last;
        last = last->prev;
            
    }
}

//Assignment Operator
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if(this != &rhs){
        
        //delete
        Node* last = coefficients->next;
        
        while(last != nullptr){
            last = last->next;
        }
        while(last){
            delete last;
            last = last->prev;
        }
            
        //copy
        Node* curr = rhs.coefficients->next;
        coefficients = new Node();
    
        while(curr){
            listAddTail(coefficients, curr->data);
            curr = curr->next;
        }
        
        degree = rhs.degree;
            
    }
    return *this;
}

/*Evaluates the polynomial at a given value*/
int Polynomial::evaluate(int val) {
    int sum = 0;
    Node* curr = coefficients->next;
    
    sum += curr->data;
    
    for(int e = 1; degree >= e; ++e){
        curr = curr->next;
        sum += curr->data*pow(val, e);
    }
    return sum;
}

//Adds a new Node to the first of the list
void Polynomial::listAddHead(Node* headPtr, int data) {
    
    if (headPtr->next != nullptr){
        Node* second = headPtr->next;
        headPtr->next = new Node(data);
            
        headPtr->next->next = second;
        second->prev = headPtr->next;
    }
    else{
        headPtr->next = new Node(data);
        headPtr->next->prev = headPtr;
    }
}

//Adds a new node to the end of the list
void Polynomial::listAddTail(Node* headPtr, int data) {
    Node* last = headPtr;
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = new Node(data);
    last->next->prev = last;
}

//Overrides the addition operator for the polynomial class;
//creates and returns a copy of the added polynomials
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial result(lhs);
    result += rhs;
    return result;
}

//Output operator for polynomials
//outputs in the form of AX^2 + BX + C
ostream& operator<<(ostream& os, const Polynomial& rhs){

    if (rhs.coefficients->next == nullptr){
        os << "0";
    }
    else{
        Polynomial::Node* p = rhs.coefficients->next;
        
        while(p->next != nullptr){
            p = p->next;
        }
        
        for(int count = rhs.degree; count > 0; --count){
            if (p->data != 0){
                if(count == 1){
                    os << p->data << "x" << " + ";
                }
                else{
                    os << p->data << "x^" << count << " + ";
                }
            }
            p = p->prev;
        }
        os << p->data;
        os << endl;
    }
    
    return os;
}

//Equality operator; checks if each node in the compared polynomial
//linked lists contain the same data.
bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    
    Polynomial::Node* curr1 = lhs.coefficients;
    Polynomial::Node* curr2 = rhs.coefficients;
    
    while(curr1 && curr2){
        if(curr1->data != curr2->data){
            return false;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    if(curr1 || curr2){
        return false;
    }
    else{
        return true;
    }
}

//Non-equal operator implemented as a non-member, non-friend
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}



