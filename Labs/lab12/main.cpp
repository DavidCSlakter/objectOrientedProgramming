//
//  main.cpp
//  lab12
//
//  Created by David Slakter on 4/20/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
using namespace std;

class DoublyLinkedList{
    
    friend ostream& operator<<(ostream& os,
    const DoublyLinkedList& rhs);
    
    struct Node{
        Node(Node* next = nullptr, Node* prev = nullptr,
        int data = 0):
        next(next), prev(prev), data(data) {}
        
        Node* next;
        Node* prev;
        int data;
    };
    
public:

    class Iterator{
        friend DoublyLinkedList;
    public:
        Iterator(Node* p): p(p){}
    
        bool operator==(const Iterator& rhs){
            return p == rhs.p;
        }
    
        bool operator!=(const Iterator& rhs){
            return p != rhs.p;
        }
    
        Iterator& operator++(){
            if(p!=nullptr){
                p = p->next;
            }
            return *this;
        }
        Iterator& operator--(){
            if(p!=nullptr){
                p = p->prev;
            }
            return *this;
        }
    
        int operator*() const {
            cout << "called const: ";
            return p->data;
        }
    
        int& operator*() {
            return p->data;
        }
        
    
    private:
        Node* p;
    };

    DoublyLinkedList(): listSize(0){
        header = new Node();
        trailer = new Node(nullptr, header);
        header->next = trailer;
    }
    
    void push_back(int value){
        Node* newNode = new Node(trailer, trailer->prev, value);
        Node* temp = trailer->prev;
        trailer->prev = newNode;
        temp->next = newNode;
        ++listSize;
    }
    
    void push_front(int val){
        Node* newNode = new Node(header->next, header, val);
        Node* temp = header->next;
        header->next = newNode;
        temp->prev = newNode;
        ++listSize;
    }
    
    void pop_back(){
        Node* lastNode = trailer->prev;
        trailer->prev = lastNode->prev;
        lastNode->prev->next = lastNode->next;
        delete lastNode;
        listSize--;
    }
    
    void pop_front(){
        Node* firstNode = header->next;
        header->next = firstNode->next;
        firstNode->next->prev = header;
        delete firstNode;
        listSize--;
    }
    
    int& front(){
        return header->next->data;
    }
    
    int& back(){
        return trailer->prev->data;
    }
    
    void clear(){
        Node* curr = header->next;

        while(curr != trailer){
            delete curr;
            curr = curr->next;
        }
        
        header->next = trailer;
        trailer->prev = header;
        listSize = 0;
    }
    
    int operator[](size_t ind) const{
        Node* p = header->next;
        size_t counter = 0;
        
        while(p != trailer){
            if(counter == ind){
                return p->data;
            }
            ++counter;
            p = p->next;
        }
        return trailer->data;
    }
    
    int& operator[](size_t ind){
        Node* p = header->next;
        size_t counter = 0;
        
        while(p != trailer){
            if(counter == ind){
                return p->data;
            }
            ++counter;
            p = p->next;
        }
        return trailer->data;
    }
 
    const Iterator begin() const{
        return Iterator(header->next);
    }

    const Iterator end() const{
        return Iterator(trailer);
    }
    
    Iterator insert(const Iterator& iter, int value){
        Node* newNode = new Node(iter.p, iter.p->prev, value);
        Node* temp = iter.p->prev;
        iter.p->prev = newNode;
        temp->next = newNode;
        ++listSize;
        
        return Iterator(newNode);
    }
    
    Iterator erase(const Iterator& iter){
        Node* result = iter.p->next;
        iter.p->prev->next = iter.p->next;
        iter.p->next->prev = iter.p->prev;
        delete iter.p;
        --listSize;
        return Iterator(result);
    }
    
    size_t size() const{
        return listSize;
    }
    
    DoublyLinkedList& operator=(const DoublyLinkedList& rhs){
    
        if (this != &rhs){
        
            //delete
            clear();
            delete header;
            delete trailer;
            
            //copy
            header = new Node(rhs.header);
            trailer = new Node(rhs.trailer);
            header->next = trailer;
            trailer->prev = header;
            for(int x: rhs){
                push_back(x);
            }
        }
        
        //return
        return *this;
    }
    
    ~DoublyLinkedList(){
        cout << "~List()" << endl;
        clear();
        delete header;
        delete trailer;
    }
    
    DoublyLinkedList(DoublyLinkedList& rhs){
    
        cout << "list(list)" << endl;
        //listSize = rhs.size();
        header = new Node(rhs.header);
        trailer = new Node(rhs.trailer);
        header->next = trailer;
        trailer->prev = header;
        for(int x: rhs){
            push_back(x);
        }
    }
    
private:
    int listSize;
    Node* header;
    Node* trailer;

};


ostream& operator<<(ostream& os, const DoublyLinkedList& rhs){
    DoublyLinkedList::Node* header = rhs.header->next;
        
    while(header != rhs.trailer){
        os << header->data << ' ';
        header = header->next;
    }
    os << endl;
    return os;
}


void printListInfo(DoublyLinkedList& myList) {
    cout << "size: " << myList.size()
    << ", front: " << myList.front()
    << ", back(): " << myList.back()
    << ", list: " << myList << endl;
}

// Task 8
void doNothing(DoublyLinkedList aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}


//bonus task
void testConst(DoublyLinkedList& dll){

    cout << "begin: " << *dll.begin();
    cout << endl;
}
int main() {
    // Task 1
    cout << "\n------Task One------\n";
    DoublyLinkedList myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";
    
    // Task2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";
    
    // Task3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";
    
    // Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (DoublyLinkedList::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
    << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    DoublyLinkedList listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
    
    
    testConst(listTwo);
}
