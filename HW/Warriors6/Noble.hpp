//
//  Noble.hpp
//  class10
//
//  Created by David Slakter on 4/6/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#ifndef Noble_hpp
#define Noble_hpp

#include <stdio.h>
#include <string>
#include <vector>

namespace WarriorCraft2 {

    class Protector;

    class Noble{
    public:
        Noble(const std::string& name, const int power);
        
         void battle(Noble& opponent);
        
         virtual void armyFightSpeech() const {}
        
         virtual void resetArmy(const double ratio) {}
    protected:
        std::string name;
        int strength;
        bool isAlive;
    };
    
    class Lord: public Noble{
    public:
        friend std::ostream& operator<<(std::ostream& os,
        const Lord& lord);
        
        Lord(const std::string& name);
        
        void armyFightSpeech() const;
        void resetArmy(const double ratio);
        bool hires(Protector& protector);
        bool removeRunaway(Protector& protector);
    private:
        std::vector<Protector*> army;
    };
    
    class Knight: public Noble{
    public:
        Knight(const std::string& name, const int power);

    };

}

#endif /* Noble_hpp */


