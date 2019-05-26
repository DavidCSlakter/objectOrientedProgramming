//
//  Noble.cpp
//  class10
//
//  Created by David Slakter on 4/6/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include "Noble.hpp"
#include "Protector.hpp"
#include <iostream>

using namespace std;

namespace WarriorCraft2 {

  Noble::Noble(const string& name, const int power) :
    name(name), strength(power), isAlive(true) {}
    
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
            else if (strength > opponent.strength){
            
               this->armyFightSpeech();
               opponent.armyFightSpeech();
               
               cout << name << " defeats " << opponent.name << endl;
               
               opponent.isAlive = false;
               
               double ratio = 1 - (opponent.strength/(double)strength);
               strength = 0;
               opponent.strength = 0;
               this->resetArmy(ratio);
               opponent.resetArmy(0);
            
            }
            else if (strength < opponent.strength){
            
               this->armyFightSpeech();
               opponent.armyFightSpeech();
            
               cout << opponent.name << " defeats " << name << endl;
               
               isAlive = false;
               
               double ratio = 1 - (strength/(double)opponent.strength);
               strength = 0;
               opponent.strength = 0;
               this->resetArmy(0);
               opponent.resetArmy(ratio);
               
            }
      
            //both warriors have the same health
            else{
                opponent.isAlive = false;
                isAlive = false;
            
                this->resetArmy(0);
                opponent.resetArmy(0);

                cout << "Mutual Annihilation: " << name << " and " <<
                opponent.name << " die at each other's hands" << endl;
            }
    }
    
    
    
    //Knight
    Knight::Knight(const std::string& name, const int power) :
    Noble(name, power) {}
    
    
    //Lord method declarations
    Lord::Lord(const string& name): Noble(name, 0) {}
    
    //output operator returns the lord's name
    ostream& operator<<(ostream& os, const Lord& lord){
        os << lord.Noble::name;
        return os;
    }

    bool Lord::hires(Protector& protector){
            //check if the warrior can be hired
            if (!protector.isHired() && Noble::isAlive &&
            (protector.getStrength() > 0)){
                //hire succeded
                army.push_back(&protector);
                Noble::strength += protector.getStrength();
                protector.setHired(true, this);
                return true;
            }
            //hire failed
            cout << "HIRE FAILED" << endl;
            return false;
    }

    //set the new strength of all the protectors in the army
    void Lord::resetArmy(const double ratio) {
        for(size_t i = 0; i < army.size(); ++i){
            army[i]->setStrength(ratio*army[i]->getStrength());
            strength += army[i]->getStrength();
        }
    }
    void Lord::armyFightSpeech() const {
        for (Protector* protector: army){
            protector->fightSpeech();
        }
    }

    bool Lord::removeRunaway(Protector& protector){
        if(protector.isHired() && isAlive && (protector.getStrength() > 0)){
        
            //find the warrior
           for(size_t i = 0; i < army.size(); ++i){
                if (army[i]->getName() == protector.getName()){
                    
                    //move the warrior to the front
                    for(size_t j = i; j < army.size() - 1; ++j){
                        army[j] = army[j + 1];
                    }
                    //remove the warrior
                    army.pop_back();
                    
                    cout << protector.getName() <<
                    " flees in terror, abandoning his lord, "
                    << name << endl;
                    
                    strength -= protector.getStrength();
                    protector.setHired(false, nullptr);
                    return true;
                }
           }
           
           //warrior not found -> return false
           return false;
        }
        cout << protector.getName() << " Failed to flee!" << endl;
        return false;
    }


}
