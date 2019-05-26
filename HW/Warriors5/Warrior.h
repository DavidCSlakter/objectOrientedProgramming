//
//  Warrior.hpp
//  Warriors5
//
//  Created by David Slakter on 3/20/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#ifndef Warrior_h
#define Warrior_h
#include <iostream>
#include <string>


namespace WarriorCraft {
   class Noble;
   
   class Warrior{
    public:
        Warrior(const std::string& hisName, int hisStrength);
       
         /******** Get Methods ********/
    
        bool isHired() const;
        std::string getName() const;
        int getStrength() const;
    
        /********* Set Methods ********/
    
        void setStrength(int newStrength);
        void setHired(bool isHired, Noble* noble);
        void runaway();
       
    private:
        std::string name;
        int strength;
        bool hired;
        Noble* leader;
   };
}

#endif /* Warrior_h */
