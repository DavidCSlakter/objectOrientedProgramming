//
//  main.cpp
//  Warriors6
//
//  Created by David Slakter on 4/4/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "Noble.hpp"
#include "Protector.hpp"
using namespace std;
using namespace WarriorCraft2;

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    Knight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    Knight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}
