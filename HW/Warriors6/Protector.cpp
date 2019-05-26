//
//  Protector.cpp
//  class10
//
//  Created by David Slakter on 4/6/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include "Protector.hpp"
#include "Noble.hpp"
#include <iostream>
using namespace std;

namespace WarriorCraft2 {
  
    //Protector method declarations
    Protector::Protector(const string& name, const int power) :
        name(name), strength(power), hired(false) {}

    bool Protector::isHired() const{
        return hired;
    }

    int Protector::getStrength() const {
        return strength;
    }

    const string& Protector::getName() const {
        return name;
    }
    Lord* Protector::getleader() const {
        return leader;
    }

    void Protector::setStrength(const int newStrength){
        strength = newStrength;
    }

    void Protector::setHired(const bool newHired, Lord* newLeader) {
        hired = newHired;
        leader = newLeader;
    }

    void Protector::runaway(){
        leader->removeRunaway(*this);
    }
    
    
    //Warrior
    Warrior::Warrior(const string& name, const int power) :
     Protector(name, power) {}


    //Wizard
    Wizard::Wizard(const string& name, const int power) :
     Protector(name, power) {}

    void Wizard::fightSpeech() const{
        cout << "POOF!" << endl;
    }

    //Swordsman
    Swordsman::Swordsman(const string& name, const int power) :
     Warrior(name, power) {}

    void Swordsman::fightSpeech() const{
        cout << "CLANG!  " << Protector::getName()
        << " says: take that in the name of my lord, "
        << *Protector::getleader() << endl;
    }

    //Archer
    Archer::Archer(const string& name, const int power) :
    Warrior(name, power) {}

    void Archer::fightSpeech() const{
        cout << "TWANG!  " << Protector::getName()
        << " says: take that in the name of my lord, "
        << *Protector::getleader() << endl;
    }


}
