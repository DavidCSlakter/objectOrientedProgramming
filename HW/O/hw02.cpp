//
//  hw02.cpp
//  Functions, structs, vectors and file I/O
//
//  Created by David Slakter on 1/31/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//
//  The purpose of this program is to read a list of "warrior" commands from a file.
//  The file controls whether a new warrior is created, when two warriors battle each
//  other, and when the status of the warriors should be printed.


#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Warrior{
    string name;
    int health;
};

/*
creates and returns a instance of the 'Warrior' struct
name -> the name to assign to the new warrior
health -> the health to assign to the new warrior
*/
Warrior createWarrior(const string& name, int health){
    Warrior warrior;
    warrior.name = name;
    warrior.health = health;
    
    return warrior;
}

/*
    Finds and returns the index where a warrior with a certain name is.
    warriors -> a vector that contains the warriors to search through
    name -> the name of the warrior that you are looking for
*/
size_t findWarrior(const vector<Warrior>& warriors, const string& name){
    for (int i = 0; i < warriors.size(); ++i){
        if (warriors[i].name == name){
            return i;
        }
    }
    return warriors.size();
}

/*
    Prints the name and the health of all the warriors created thus far
    warriors -> A vector that contains the warrior objects
*/
void printStatus(const vector<Warrior>& warriors){
    
    cout << "There are: " << warriors.size() << " warriors" << endl;
    
    for (const Warrior& warrior: warriors){
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.health << endl;
     }
}

/*
    executes a battle between two specified warriors, the warrior with the most health wins the battle and
    the other warrior dies
    warrior1/warrior2 -> two warrior objects that are compared and 'fight' against each other
*/
void battle(Warrior& warrior1,  Warrior& warrior2){

    //both warriors are dead
    if (warrior1.health == 0 && warrior2.health == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    
    //one warrior is dead
    else if (warrior1.health == 0){
        cout << "He's dead, " << warrior2.name << endl;
    }
    else if (warrior2.health == 0){
        cout << "He's dead, " << warrior1.name << endl;
    }
    
    //one warrior wins and the other's health is subtracted
    else if (warrior1.health > warrior2.health){
        warrior1.health -= warrior2.health;
        warrior2.health = 0;
        
        cout << warrior1.name << " defeats " << warrior2.name << endl;
    }
    else if (warrior2.health > warrior1.health){
        warrior2.health -= warrior1.health;
        warrior1.health = 0;
        
        cout << warrior2.name << " defeats " << warrior1.name << endl;
    }
    
    //both warriors have the same health
    else{
        warrior1.health = 0;
        warrior2.health = 0;
        
        cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name << " die at each other's hands" << endl;
    }
}

int main() {

    const string FILENAME = "warriors.txt";
    ifstream fightLog(FILENAME); // reads file
    if (!fightLog) {
        cerr << "failed to open file\n"; //prints error
        exit(1);
    }
    
    string nextWord;
    vector<Warrior> warriors;
    
    //reads through each word until the end of the file
    while(fightLog >> nextWord){
        
        if (nextWord == "Warrior"){
            string name;
            int health;
       
            //set the next two words to 'health' and 'name'
            fightLog >> name;
            fightLog >> health;
            
            Warrior warrior = createWarrior(name, health);
            warriors.push_back(warrior);
        
        }
        else if (nextWord == "Battle"){
           
            string warriorName1;
            string warriorName2;
            
            //get the two warrior names
            fightLog >> warriorName1;
            fightLog >> warriorName2;
           
            size_t warrior1Ind = findWarrior(warriors, warriorName1);
            size_t warrior2Ind = findWarrior(warriors, warriorName2);
           
            cout << warriors[warrior1Ind].name << " battles " << warriors[warrior2Ind].name << endl;
           
            battle(warriors[warrior1Ind], warriors[warrior2Ind]);
            
        }
        else{
            printStatus(warriors);
        }
    }
    
    
    fightLog.close(); //close the file
        
}


