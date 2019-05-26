//
//  Noble.hpp
//  Warriors5
//
//  Created by David Slakter on 3/20/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#ifndef Noble_h
#define Noble_h
#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
  
  class Warrior;
  
  class Noble {
    friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
  public:
    Noble(const std::string& hisName);
    
    /********* get Methods *******/
    std::string getName() const {
        return name;
    }
    
    /******** Set Methods ********/
    void battle(Noble& opponent);
    
    bool hire(Warrior& warrior);
    
    bool fire(Warrior& warrior);
    
    bool removeRunaway(Warrior& warrior);
    
  private:
    std::string name;
    bool isAlive;
    int armyStrength;
    std::vector<Warrior*> army;
  };
}

#endif /* Noble_h */
