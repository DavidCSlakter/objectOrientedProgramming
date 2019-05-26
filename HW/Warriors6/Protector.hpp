//
//  Protector.hpp
//  class10
//
//  Created by David Slakter on 4/6/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#ifndef Protector_hpp
#define Protector_hpp

#include <stdio.h>
#include <string>
#include <vector>

namespace WarriorCraft2 {
     class Lord;

     class Protector{
    public:
        Protector(const std::string& name, const int power);
        void setHired(const bool newHired, Lord* newLeader);
        int getStrength() const;
        const std::string& getName() const;
        void setStrength(const int newStrength);
        bool isHired() const;
        void runaway();
        
        //every protector must have a speech when they fight
        virtual void fightSpeech() const = 0;
    protected:
        Lord* getleader() const;
    private:
        bool hired;
        int strength;
        Lord* leader;
        std::string name;
    };
    
    class Warrior: public Protector{
    public:
    protected:
        Warrior(const std::string& name, const int power);
    
        virtual void fightSpeech() const = 0;
    };

    class Wizard: public Protector{
    public:
        Wizard(const std::string& name, const int power);
        void fightSpeech() const;
    };

    class Swordsman: public Warrior{
    public:
        Swordsman(const std::string& name, const int power);
        void fightSpeech() const;
    };

    class Archer: public Warrior{
    public:
        Archer(const std::string& name, const int power);
        void fightSpeech() const;
    };

}

#endif /* Protector_hpp */
