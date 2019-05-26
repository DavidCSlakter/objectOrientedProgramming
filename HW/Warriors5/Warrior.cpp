//
//  Warrior.cpp
//  Warriors5
//
//  Created by David Slakter on 3/20/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include "Warrior.h"
#include "Noble.h"
#include <stdio.h>

using namespace std;

namespace WarriorCraft {
    //warrior constructor
    Warrior::Warrior(const string& hisName,
    int hisStrength):name(hisName), strength(hisStrength),
    hired(false){}
    
    /******** Get Methods ********/
    
    bool Warrior::isHired() const{
        return hired;
    }
    
    string Warrior::getName() const {
        return name;
    }
    
    int Warrior::getStrength() const {
        return strength;
    }
    
    /********* Set Methods ********/
    
    void Warrior::setStrength(int newStrength){
        strength = newStrength;
    }
    
    void Warrior::setHired(bool isHired,  Noble* noble){
        hired = isHired;
        leader = noble;
    }
    
    void Warrior::runaway(){
        leader->removeRunaway(*this);
    }
}
