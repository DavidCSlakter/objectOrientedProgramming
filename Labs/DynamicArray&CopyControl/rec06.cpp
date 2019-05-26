//
//  main.cpp
//  DynamicArray&CopyControl
//
//  Created by David Slakter on 3/2/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <string>
#include <iostream>
using namespace std;


class Position {
//
public://
    Position(const string& aTitle, double aSalary)
    : title(aTitle), salary(aSalary) {}
    
    /*********get methods ***********/
    const string& getTitle() const { return title; }
    
    double getSalary() const { return salary; }
    
    /********set methods************/
    void changeSalaryTo(double d) { salary = d; }
    
    /********other public methods*********/
    friend ostream& operator<<(ostream& os, const Position& pos){
         os << '[' << pos.title << ',' << pos.salary << ']';
        return os;
    }
    
private:
    string title;
    double salary;
}; // class Position

class Entry {
public:
    Entry(const string& aName, unsigned aRoom, unsigned aPhone,
      Position& aPosition)
    : name(aName), room(aRoom), phone(aPhone), pos(&aPosition) {
    }
    
    friend ostream& operator<<(ostream& os, const Entry& entry){
        os << entry.name << ' ' << entry.room << ' ' << entry.phone << ", " << *entry.pos << endl;
        
        return os;
    }
    
    /*********** get methods *************/
    const string& getName() const { return name; }
    
    const unsigned& getPhone() const { return phone; }
    
    const unsigned& getRoom() const { return room; }
    
    Position* getPos() const { return pos; }

    
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
public:
    
    Directory(): capacity(2){
        entries = new Entry*[capacity];
    }
    
    //copy constructor
    Directory(const Directory& rhs){
        cout << "entered the copy constructor" << endl;
        size = rhs.size;
        capacity = rhs.capacity;
        entries = new Entry*[capacity];
        
        for (size_t ind = 0; ind < size; ++ind){
        
            Entry* newEntry = new Entry(*rhs.entries[ind]);
            
            entries[ind] = newEntry;
        }
    }
    
    //destructor
    ~Directory(){
        cout << "entered the deconstructor" << endl;
        for (size_t ind = 0; ind < size; ++ind){
            delete entries[ind];
        }
        delete[] entries;
    }
    
    //assignment operator
    Directory& operator=(const Directory& rhs){
    
        cout << "Entered the assignment operator" << endl;
        
        if (this != &rhs){ //check for self-assignment
        
            for (size_t ind = 0; ind < size; ++ind){
            delete entries[ind];
            }
            delete[] entries;
        
            size = rhs.size;
            capacity = rhs.capacity;
            entries = new Entry*[capacity];
        
            for (size_t ind = 0; ind < size; ++ind){
               
                Entry* newEntry = new Entry(*rhs.entries[ind]);
                
                entries[ind] = newEntry;
            }
        }
        return *this;
    }
    
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity){
            
           capacity *= 2;
        
            Entry** NewEntries;
            NewEntries = new Entry*[capacity];
            
            for (size_t ind = 0; ind < size; ++ind){
                NewEntries[ind] = entries[ind];
            }
            delete[] entries;
            
            entries = NewEntries;
            
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add
    
    int operator[](const string& name) const{
        for(size_t ind = 0; ind < size; ++ind){

            if (entries[ind]->getName() == name){
                return entries[ind]->getPhone();
            }
        }
        cout << "Could not find entry with name: " << name << endl;
        return 00000;
    }
    
 
    friend ostream& operator<<(ostream& os, const Directory& direc){
        for (size_t i = 0; i < direc.size; ++i) {
            os << *direc.entries[i];
        }
        
        return os;
    }


private:
    Entry** entries = nullptr;
    size_t size = 0;
    size_t capacity = 0;
}; // class Directory

void doNothing(Directory dir) { cout << dir; }

int main() {
//    const int x =  21;
//    cosnt int *p = &21; //cant take the address of literal, doesnt have a spot in memory
    
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
    
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d;

    Directory d2 = d;    // What function is being used?? - copy constructor
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d2;

    cout << "Calling doNothing\n";
    doNothing(d2); //copy constructor
    cout << "Back from doNothing\n";

    Directory d3; //assignment operator
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;
    
} // main

