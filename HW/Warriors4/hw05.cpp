//
//  main.cpp
//  Warriors4
//
//  Created by David Slakter on 3/1/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*
Class which holds the methods and member properties of a Warrior
name: name of the warrior
strength: strength of the warrior
hired: bool value that represents if the warrior is hired or not
*/
class Warrior{
public:
    
    //warrior constructor
    Warrior(const string& hisName, int hisStrength):
    name(hisName), strength(hisStrength), hired(false){}
    
    /******** Get Methods ********/
    
    bool isHired() const{
        return hired;
    }
    
    string getName() const{
        return name;
    }
    
    int getStrength() const {
        return strength;
    }
    
    /********* Set Methods ********/
    
    void setStrength(int newStrength){
        strength = newStrength;
    }
    
    void setHired(bool isHired){
        hired = isHired;
    }

private:
    /***** Member Variables *********/
    string name;
    int strength;
    bool hired;
};


/*
class which holds the methods and properties of a noble
name: name of the noble
isAlive: bool that represents if the noble is alive
armyStrength: the combined army strength of the noble
army: vector of pointors to warrior objects which represent
the army controlled by the noble
*/
class Noble{

public:

    Noble(const string& hisName): name(hisName),
    isAlive(true), armyStrength(0){}

    
    //displays the army size and stats of each warrior in
    //the noble's army
    void display() const {
        cout << name << " has an army of " << army.size() << endl;
        
        for (size_t i = 0; i < army.size(); ++i){
        
            cout << "\t" << army[i]->getName() << ": " <<
            army[i]->getStrength() << endl;
            
        }
    }
    
    /******get methods*********/
    string getName() const{
        return name;
    }
    vector<Warrior*> getArmy() const{
        return army;
    }
    
    size_t findWarrior(const string& warriorName) const {

        for (size_t j = 0; j < army.size(); ++j){
            if (warriorName == army[j]->getName()){
                return j;
            }
        }
        return army.size();
    }
    
    //called when a noble declares battle on another noble
    void battle(Noble& opponent){
        cout << name << " battles " << opponent.name << endl;
        
        //both warriors are dead
        if (!isAlive && !opponent.isAlive){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    
        //one warrior is dead
        else if (!isAlive){
            cout << "He's dead, " << opponent.name << endl;
        }
        else if (!opponent.isAlive){
            cout << "He's dead, " << name << endl;
        }
    
        //one warrior wins and the other's army health is reduced
        else if (armyStrength > opponent.armyStrength){
        
           cout << name << " defeats " << opponent.name << endl;
           
           opponent.isAlive = false;
           
           double ratio = 1 - (opponent.armyStrength/(double)armyStrength);
           armyStrength = 0;
           opponent.armyStrength = 0;
           for(size_t i = 0; i < army.size(); ++i){
               army[i]->setStrength(ratio*army[i]->getStrength());
               armyStrength += army[i]->getStrength();
           }
           for (size_t j = 0; j < opponent.army.size(); ++j){
                opponent.army[j]->setStrength(0);
           }
        
        }
        else if (opponent.armyStrength > armyStrength){
        
           cout << opponent.name << " defeats " << name << endl;
           
           isAlive = false;
           
           double ratio = 1 - (armyStrength/(double)opponent.armyStrength);
           armyStrength = 0;
           opponent.armyStrength = 0;
           for(size_t i = 0; i < opponent.army.size(); ++i){
               opponent.army[i]->setStrength(
               ratio*opponent.army[i]->getStrength());
               
               opponent.armyStrength +=
               opponent.army[i]->getStrength();
           }
           for (size_t j = 0; j < army.size(); ++j){
                army[j]->setStrength(0);
           }
        }
    
        //both warriors have the same health
        else{
            opponent.isAlive = false;
            isAlive = false;
            
            armyStrength = 0;
            opponent.armyStrength = 0;
            
            for (size_t i = 0; i < army.size(); ++i){
                army[i]->setStrength(0);
            }
            for(size_t j = 0; j < opponent.army.size(); ++j){
                opponent.army[j]->setStrength(0);
            }
        
            cout << "Mutual Annihilation: " << name << " and " <<
            opponent.name << " die at each other's hands" << endl;
        }
    }
    
    bool hire(Warrior& warrior){
        //check if the warrior can be hired
        if (!warrior.isHired() && isAlive && (warrior.getStrength() > 0)){
            army.push_back(&warrior);
            armyStrength += warrior.getStrength();
            warrior.setHired(true);
            return true;
        }
        cout << "HIRE FAILED" << endl;
        return false;
    }
    
    bool fire(Warrior& warrior){
        if(warrior.isHired() && isAlive && (warrior.getStrength() > 0)){
        
            //find the warrior
           for(size_t i = 0; i < army.size(); ++i){
                if (army[i]->getName() == warrior.getName()){
                    
                    //move the warrior to the front
                    for(size_t j = i; j < army.size() - 1; ++j){
                        army[j] = army[j + 1];
                    }
                    //remove the warrior
                    army.pop_back();
                    
                    cout << warrior.getName() << ", you're fired! -- "
                    << name << endl;
                    
                    armyStrength -= warrior.getStrength();
                    warrior.setHired(false);
                    return true;
                }
           }
           
           //warrior not found -> return false
           return false;
        }
        cout << "FIRE FAILED" << endl;
        return false;
    }
private:
    string name;
    bool isAlive;
    int armyStrength;
    vector<Warrior*> army;
};

size_t findNoble(const string& nobleName, const vector<Noble*>& nobles) {
    for(size_t i = 0; i < nobles.size(); ++i){
        if (nobleName == nobles[i]->getName()){
            return i;
        }
    }
    return nobles.size();
}
size_t findWarrior(const string& warriorName, const vector<Warrior*>& warriors) {
    for(size_t i = 0; i < warriors.size(); ++i){
        if (warriorName == warriors[i]->getName()){
            return i;
        }
    }
    return warriors.size();
}

bool findWarriorInNobles(const string& warriorName, const vector<Noble*>& nobles){

    for(size_t i = 0; i < nobles.size(); ++i){
        for (size_t j = 0; j < nobles[i]->getArmy().size(); ++j){
            if (warriorName == nobles[i]->getArmy()[j]->getName()){
                return true;
            }
        }
    }
    
    //did not find the warrior
    return false;
}


int main() {

    const string FILENAME = "nobleWarriors.txt";
    ifstream fightLog(FILENAME); // reads file
    if (!fightLog) {
        cerr << "failed to open file\n"; //prints error
        exit(1);
    }
    
    string nextWord;
    
    //holds all the nobles
    vector<Noble*> nobles;
    
    //holds all out-of-work warriors
    vector<Warrior*> availableWarriors;

    
    //reads through each word until the end of the file
    while(fightLog >> nextWord){
        
        if (nextWord == "Warrior"){
        
            string wName;
            int wHealth;
            
            fightLog >> wName;
            fightLog >> wHealth;
            
            //see if warrior with name already exists
            if (findWarriorInNobles(wName, nobles) || (findWarrior(wName, availableWarriors) != availableWarriors.size())){
                //warrior was found
                cout << "Sorry " << wName << " you already exist!" << endl;
            }
            else{
                Warrior* warrior = new Warrior(wName, wHealth);
                availableWarriors.push_back(warrior);
            }
            
        }
        else if (nextWord == "Noble"){
        
            string nName;
            fightLog >> nName;
            
            //check if noble with name exists
            if(findNoble(nName, nobles) != nobles.size()){
                cout << "Sorry " << nName << " you already exist!" << endl;
            }
            else{
                 Noble* noble = new Noble(nName);
                 nobles.push_back(noble);
            }
        }
        else if (nextWord == "Hire"){
        
            string nName;
            string wName;
            
            fightLog >> nName;
            fightLog >> wName;
            
            
            size_t nIndex = findNoble(nName, nobles);
            size_t wIndex = findWarrior(wName, availableWarriors);
            
            if (nIndex == nobles.size()){
                cout << "Could not hire: The noble " << nName << " does not exist" << endl;
            }
            else if (wIndex == availableWarriors.size()){
                cout << "Could not hire: The warrior " << wName << " is not available" << endl;
            }
            else{
                nobles[nIndex]->hire(*availableWarriors[wIndex]);
                //remove from availableWarriors vector
                
                //move the warrior to the front
                for(size_t j = wIndex; j < availableWarriors.size() - 1; ++j){
                        availableWarriors[j] = availableWarriors[j + 1];
                }
                //remove the warrior
                availableWarriors.pop_back();
                
            }
        
        }
        else if (nextWord == "Fire"){
        
            string nName;
            string wName;
            
            fightLog >> nName;
            fightLog >> wName;
            
            size_t nIndex = findNoble(nName, nobles);
            size_t wIndex = nobles[nIndex]->findWarrior(wName);
            
            if (nIndex == nobles.size()) {
                cout << "Could not fire: the noble " << nName << " does not exist" << endl;
            }
            else if (wIndex == nobles[nIndex]->getArmy().size()){
                cout << "Could not fire: the warrior " << wName << " was not found in the noble " << nName << endl;
            }
            else{
                availableWarriors.push_back(nobles[nIndex]->getArmy()[wIndex]);
                nobles[nIndex]->fire(*nobles[nIndex]->getArmy()[wIndex]);
            }
            
        
        }
        else if (nextWord == "Battle"){
        
            string n1Name;
            string n2Name;
            
            fightLog >> n1Name;
            fightLog >> n2Name;
            
            //find if both nobles exist
            size_t n1Index = findNoble(n1Name, nobles);
            size_t n2Index = findNoble(n2Name, nobles);
            
            if (n1Index == nobles.size()){
                cout << "could not battle: " << n1Name << " does not exist" << endl;
            }
            else if (n2Index == nobles.size()){
                cout << "could not battle: " << n2Name << " does not exist" << endl;
            }
            else{
                nobles[n1Index]->battle(*nobles[n2Index]);
            }
           
        }
        else if (nextWord == "Clear"){
            for (size_t i = 0; i < nobles.size(); ++i){
                delete nobles[i];
                nobles.clear();
                
            }
            for (size_t j = 0; j < availableWarriors.size(); ++j){
                delete availableWarriors[j];
                availableWarriors.clear();
            }
        }
        else{
           //print status
           cout << "Status" << endl;
           cout << "======" << endl;
           
           cout << "Nobles: " << endl;
           
           if (nobles.size() == 0){
                cout << "NONE" << endl;
           }
           else{
           
                for(size_t i = 0; i < nobles.size(); ++i){
                    nobles[i]->display();
                }
           }
           
           cout << "Unemployed Warriors: " << endl;
           
           if (availableWarriors.size() == 0){
                cout << "NONE" << endl;
           }
           else{
                for (size_t j = 0; j < availableWarriors.size(); ++j){
                    cout << availableWarriors[j]->getName() << ": " << availableWarriors[j]->getStrength() << endl;
                }
           }
        }
    }
    
    
    fightLog.close(); //close the file
  
}

