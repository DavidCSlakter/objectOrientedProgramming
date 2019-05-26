//
//  main.cpp
//  Warriors3
//
//  Created by David Slakter on 2/21/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//
//  This program defines a noble and a warrior class. Each noble controls
//  an army which contains pointers to warrior objects.

#include <iostream>
#include <string>
#include <vector>


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
    
    string getName() const {
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
           
           double ratio = opponent.armyStrength/armyStrength;
           armyStrength = 0;
           opponent.armyStrength = 0;
           for(size_t i = 0; i < army.size(); ++i){
               army[i]->setStrength(ratio*army[i]->getStrength());
               armyStrength += army[i]->getStrength();
           }
        
        }
        else if (opponent.armyStrength > armyStrength){
        
           cout << opponent.name << " defeats " << name << endl;
           
           isAlive = false;
           
           double ratio = armyStrength/opponent.armyStrength;
           armyStrength = 0;
           opponent.armyStrength = 0;
           for(size_t i = 0; i < opponent.army.size(); ++i){
               opponent.army[i]->setStrength(
               ratio*opponent.army[i]->getStrength());
               
               opponent.armyStrength +=
               opponent.army[i]->getStrength();
           }
        }
    
        //both warriors have the same health
        else{
            opponent.isAlive = false;
            isAlive = false;
            
            armyStrength = 0;
            opponent.armyStrength = 0;
        
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


int main() {

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    

    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();
    
    art.fire(cheetah);
    art.display();
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
    
}


