//
//  main.cpp
//  Warriors2
//
//  Created by David Slakter on 2/15/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Warrior{

public:

    Warrior(const string& name, const string& weaponName, int weaponHealth): warriorName(name), warriorWeapon(weaponName, weaponHealth) {}
    
    string getName() const{
        return warriorName;
    }
    string getWeaponName() const{
        return warriorWeapon.getName();
    }
    int getWeaponHealth() const{
        return warriorWeapon.getHealth();
    }
    void changeWeaponHealth(int newHealth){
        warriorWeapon.changeHealth(newHealth);
    }
    
private:

    class Weapon{
    public:
    
        Weapon(const string& name, int health): name(name), health(health) {}
        
        void changeHealth(int newHealth){
            health = newHealth;
        }
        
        int getHealth() const{
            return health;
        }
        
        string getName() const{
            return name;
        }
    private:
        string name;
        int health;
    };
    
    Weapon warriorWeapon;
    string warriorName;
    
};

void battle(Warrior& warrior1, Warrior& warrior2){
     //both warriors are dead
    if (warrior1.getWeaponHealth() == 0 && warrior2.getWeaponHealth() == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    
    //one warrior is dead
    else if (warrior1.getWeaponHealth() == 0){
        cout << "He's dead, " << warrior2.getName() << endl;
    }
    else if (warrior2.getWeaponHealth() == 0){
        cout << "He's dead, " << warrior1.getName() << endl;
    }
    
    //one warrior wins and the other's health is subtracted
    else if (warrior1.getWeaponHealth() > warrior2.getWeaponHealth()){
        warrior1.changeWeaponHealth(warrior1.getWeaponHealth() - warrior2.getWeaponHealth());
        warrior2.changeWeaponHealth(0);
        
        cout << warrior1.getName() << " defeats " << warrior2.getName() << endl;
    }
    else if (warrior2.getWeaponHealth() > warrior1.getWeaponHealth()){
        warrior2.changeWeaponHealth(warrior2.getWeaponHealth() - warrior1.getWeaponHealth());
        warrior1.changeWeaponHealth(0);
        
        cout << warrior2.getName() << " defeats " << warrior1.getName() << endl;
    }
    
    //both warriors have the same health
    else{
        warrior1.changeWeaponHealth(0);
        warrior2.changeWeaponHealth(0);
        
        cout << "Mutual Annihilation: " << warrior1.getName() << " and " << warrior2.getName() << " die at each other's hands" << endl;
    }
}

size_t findWarrior(const vector<Warrior>& warriors, const string& name) {
    for (int i = 0; i < warriors.size(); ++i){
        if (warriors[i].getName() == name){
            return i;
        }
    }
    return warriors.size();
}

void printStatus(const vector<Warrior>& warriors){
    
    cout << "There are: " << warriors.size() << " warriors" << endl;
    
    for (const Warrior& warrior: warriors){
        cout << "Warrior: " << warrior.getName() << ", weapon: " << warrior.getWeaponName() << ", strength: " << warrior.getWeaponHealth() << endl;
     }
}

int main() {
    const string FILENAME = "warriors.txt";
    ifstream fightLog(FILENAME); // reads file
    if (!fightLog) {
        cerr << "failed to open file\n"; //prints error
        exit(1);
    }
    
    string nextWord;
    vector<Warrior> warriors;
    
    //reads through each word until the end of the file
    while(fightLog >> nextWord){
        if (nextWord == "Warrior"){
            string warriorName;
            string weaponName;
            int health;
       
            //set the next three words to 'health', 'warriorName' and 'weaponName'
            fightLog >> warriorName;
            fightLog >> weaponName;
            fightLog >> health;
            
            Warrior warrior(warriorName, weaponName, health);
            warriors.push_back(warrior);
            
        }
        else if (nextWord == "Battle"){
           
            string warriorName1;
            string warriorName2;
            
            //get the two warrior names
            fightLog >> warriorName1;
            fightLog >> warriorName2;
           
            size_t warrior1Ind = findWarrior(warriors, warriorName1);
            size_t warrior2Ind = findWarrior(warriors, warriorName2);
           
            cout << warriors[warrior1Ind].getName() << " battles " << warriors[warrior2Ind].getName() << endl;
           
            battle(warriors[warrior1Ind], warriors[warrior2Ind]);
            
        }
        else{
            printStatus(warriors);
        }
    }
    
    
    fightLog.close(); //close the file
}
