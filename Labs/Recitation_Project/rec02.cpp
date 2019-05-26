//
//  main.cpp
//  Recitation_Project
//
//  Created by David Slakter on 2/2/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Molecule {
    vector<string> variations;
    int carbons;
    int hydrogens;
};

Molecule makeMolecule(int carbons, int hydrogens, string name){
    Molecule molecule;
    molecule.carbons = carbons;
    molecule.hydrogens = hydrogens;
    molecule.variations.push_back(name);
    
    return molecule;
}

size_t findMoleculeGroup(int carbons, int hydrogens, const vector<Molecule>& hydrocarbons){
    for (size_t i = 0; i < hydrocarbons.size(); ++i){
        if ((carbons == hydrocarbons[i].carbons) && (hydrogens == hydrocarbons[i].hydrogens)){
            return i;
        }
    }
    return hydrocarbons.size();
}

void printHydrocarbons(const vector<Molecule>& hydrocarbons, int maxCarbons){
    
    for (int i = 0; i <= maxCarbons; i++){
        for (const Molecule& molecule: hydrocarbons){
        
            if (molecule.carbons == i){
                cout << 'C' << molecule.carbons << 'H' << molecule.hydrogens << ' ';
                
                for (const string& variation: molecule.variations){
                    cout << variation << ' ';
                }
                cout << endl;
            }
            
        }
        
    }
}

int main() {
    string fileName = "ChemFormulae.txt";
    ifstream formulae(fileName); // reads file
    if (!formulae) {
        cerr << "failed to open file\n"; //prints error
        exit(1);
    }
    
    string name;
    vector<Molecule> hydrocarbons;
    int maxCarbon = 0;
    
    while(formulae >> name){
    
        char tempChar;
        formulae >> tempChar;
        int carbons;
        formulae >> carbons;
        formulae >> tempChar;
        int hydrogens;
        formulae >> hydrogens;
        
        maxCarbon = max(maxCarbon,carbons);
        size_t groupInd = findMoleculeGroup(carbons, hydrogens, hydrocarbons);
        
        if (groupInd == hydrocarbons.size()){
            Molecule molecule = makeMolecule(carbons, hydrogens, name);
            hydrocarbons.push_back(molecule);
        }
        else{
            hydrocarbons[groupInd].variations.push_back(name);
        }
        
    }
    
    formulae.close();
    
    printHydrocarbons(hydrocarbons,maxCarbon);
    
}
