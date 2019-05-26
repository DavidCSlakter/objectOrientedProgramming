//
//  main.cpp
//  lab10
//
//  Created by David Slakter on 4/6/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Instrument{
public:
    virtual void makeSound() const = 0;
    
    virtual void play() const = 0;
private:
};

void Instrument::makeSound() const{
    cout << "to make a sound...";
}

class MILL {
public:
    void receiveInstr(Instrument& instr){
    //    instr.makeSound();
        Instrument* instrPointer = &instr;
        bool inserted = false;
        for (size_t i = 0; i < instruments.size(); ++i){
            if (instruments[i] == nullptr){
                instruments[i] = instrPointer;
                inserted = true;
                break;
            }
        }
        if (!inserted){
            instruments.push_back(instrPointer);
        }
    }
    
    void dailyTestPlay() const {
        for (Instrument* instr: instruments){
            if (instr != nullptr){
                instr->makeSound();
            }
        }
    }
    
    Instrument* loanOut() {
        size_t ind = 0;
        while (instruments[ind] == nullptr || ind == instruments.size()){
            ind++;
        }
        if (ind == instruments.size()){
            return nullptr;
        }
        else{
            Instrument* iPointer = instruments[ind];
            instruments[ind] = nullptr;
            return iPointer;
        }
    }
private:
    vector<Instrument*> instruments;
};

class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }
    
    void PlayInstr() const{
        if (instr != nullptr){
            instr->play();
        }
        else{
            cerr << "\nI have no intrument" << endl;
        }
    }

private:
    Instrument* instr;
};

class Orch {
public:
    void addPlayer(Musician& player){
        if (players.size() < 25){
            Musician* playerPointer = &player;
            players.push_back(playerPointer);
        }
        else{
            cout << "max orchastra size reached" << endl;
        }
    }
    void play() const{
        for (const Musician* player: players){
            player->PlayInstr();
        }
    }
private:
    vector<Musician*> players;
};


class Percussion: public Instrument{
public:
    void makeSound() const {
        Instrument::makeSound();
        cout << " hit me!" << endl;
    }
};

class Drum: public Percussion{
public:
    void play() const{
        cout << "Boom";
    }
};
class Cymbal: public Percussion{
public:
    void play() const{
        cout << "Crash";
    }
};

class Brass: public Instrument{
public:
    Brass(const int mSize): mouthpiece(mSize) {}
    void makeSound() const {
        Instrument::makeSound();
        cout << " blow on mouthpiece of size "
        << mouthpiece << endl;
    }
    
private:
    int mouthpiece;
};
class Trombone: public Brass{
public:
    Trombone(const int size): Brass(size) {}
    
    void play() const{
        cout << "Blat";
    }
};

class Trumpet: public Brass{
public:
    Trumpet(const int size): Brass(size) {}
    
    void play() const {
        cout << "Toot";
    }
};


class StringIntr: public Instrument{
public:
    StringIntr(const int pitch): pitch(pitch) {}
    
    void makeSound() const{
        Instrument::makeSound();
        cout << " bow a string with pitch "
        << pitch << endl;
    }
    
private:
    int pitch;
};

class Cello: public StringIntr{
public:
    Cello(const int pitch): StringIntr(pitch) {}
    
    void play() const{
        cout << "Squawk";
    }

};

class Violin: public StringIntr{
public:
    Violin(const int pitch): StringIntr(pitch) {}
    
    void play() const{
        cout << "Screech";
    }

};



// PART ONE
int main() {
//
//    cout << "Define some instruments ----------------------------------------\n";
//     Drum drum;
//     Cello cello(673);
//     Cymbal cymbal;
//     Trombone tbone(4);
//     Trumpet trpt(12) ;
//     Violin violin(567) ;
//
//    // // use the debugger to look at the mill
//     cout << "Define the MILL ------------------------------------------------\n";
//     MILL mill;
//
//     cout << "Put the instruments into the MILL ------------------------------\n";
//     mill.receiveInstr(trpt);
//     mill.receiveInstr(violin);
//     mill.receiveInstr(tbone);
//     mill.receiveInstr(drum);
//     mill.receiveInstr(cello);
//     mill.receiveInstr(cymbal);
//
//     cout << "Daily test -----------------------------------------------------\n";
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//     cout << endl;
//
//     cout << "Define some Musicians-------------------------------------------\n";
//     Musician harpo;
//     Musician groucho;
//
//     cout << "TESTING: groucho.acceptInstr(mill.loanOut());-----------------------\n";
//     groucho.testPlay();
//     cout << endl;
//     groucho.acceptInstr(mill.loanOut());
//     cout << endl;
//     groucho.testPlay();
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//
//     cout << endl << endl;
//
//     groucho.testPlay();
//     cout << endl;
//     mill.receiveInstr(*groucho.giveBackInstr());
//     harpo.acceptInstr(mill.loanOut());
//     groucho.acceptInstr(mill.loanOut());
//     cout << endl;
//     groucho.testPlay();
//     cout << endl;
//     harpo.testPlay();
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//
//     cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ----------\n";
//
//     // fifth
//     mill.receiveInstr(*groucho.giveBackInstr());
//     cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
//     mill.receiveInstr(*harpo.giveBackInstr());
//
//
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//     cout << endl;
//
//     cout << endl;



// The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "\norch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "\norch performs\n";
    orch.play();
    
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "\norch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "\norch performs\n";
    orch.play();
}


