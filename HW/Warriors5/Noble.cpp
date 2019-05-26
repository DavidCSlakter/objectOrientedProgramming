//
//  Noble.cpp
//  Warriors5
//
//  Created by David Slakter on 3/20/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include "Noble.h"
#include "Warrior.h"
#include <stdio.h>

using namespace std;

namespace WarriorCraft {
    Noble::Noble(const std::string& hisName): name(hisName),
    isAlive(true), armyStrength(0){}
    
    void Noble::battle(Noble& opponent){
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
    
    bool Noble::hire(Warrior& warrior){
        //check if the warrior can be hired
        if (!warrior.isHired() && isAlive && (warrior.getStrength() > 0)){
            army.push_back(&warrior);
            armyStrength += warrior.getStrength();
            warrior.setHired(true, this);
            return true;
        }
        cout << "HIRE FAILED" << endl;
        return false;
    }
    
    bool Noble::fire(Warrior& warrior){
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
                    warrior.setHired(false, nullptr);
                    return true;
                }
           }
           
           //warrior not found -> return false
           return false;
        }
        cout << "FIRE FAILED" << endl;
        return false;
    }
    
    bool Noble::removeRunaway(Warrior& warrior){
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
                    
                    cout << warrior.getName() <<
                    " flees in terror, abandoning his lord, "
                    << name << endl;
                    
                    armyStrength -= warrior.getStrength();
                    warrior.setHired(false, nullptr);
                    return true;
                }
           }
           
           //warrior not found -> return false
           return false;
        }
        cout << "Tarzan Failed to flee!" << endl;
        return false;
    }
    
    ostream& operator<<(ostream& os, const Noble& noble){
        os << noble.name << " has an army of " << noble.army.size() << endl;
        
        for (size_t i = 0; i < noble.army.size(); ++i){
        
            os << "\t" << noble.army[i]->getName() << ": " <<
            noble.army[i]->getStrength() << endl;
            
        }
        return os;
    }
    
    
}
