//
//  hw01.cpp
//  Hw1: Caesar Cypher
//
//  Created by David Slakter on 1/27/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//
//  This program reads from a file called "encrypted.txt" and prints out a decrypted message to the standard output.


#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

/*
 character: the current character in the string that needs to be decrpyted.
 steps: How many steps the file specifies in order to decrpyt.
 
 return: returns the decrypted character.
*/
char decryptCharacter(char character, int steps) {
    
    //determine if character needs to be decrpyted
    if (isupper(character) || character == ' ' || character == '.'){
        return character; //return the original character
    }
    else{
    
        //the character is lowercase, use "steps" to decrpyt and return result
        int tempChar = character - steps;
        if(tempChar < 'a'){
            int remainder = character - 'a';
            character =  '{' - steps + remainder;
            return character;
        }
        else{
            return character - steps;
        }
        
    }
}

/*
input: a line of text that needs to be decrypted.
lines: set of total lines in the message.
steps:  How many steps the file specifies in order to decrpyt.
*/
void decryptString(string input, vector<string>& lines, int steps){
    
    //decrypt each character in the string and replace old character
    for (int i = 0; i < input.length(); ++i) {
        input[i] = decryptCharacter(input[i], steps);
    }
    //add the decrpyted line to the end of the vector
    lines.push_back(input);
}

int main() {

    const string fileName = "encrypted.txt";
    ifstream cypher(fileName); // reads file
    if (!cypher) {
        cerr << "failed to open file\n"; //prints error
        exit(1);
    }
    
    int steps;
    cypher >> steps;
    
    string line;
    vector<string> lines;
    
    //read the file line by line.
    while (getline(cypher, line)){
        decryptString(line, lines, steps);
    }
    
    //print the output of the decrpyted lines in reverse order.
    while(!lines.empty()){
        string firstLine = lines.back();
        lines.pop_back();
        cout << firstLine << endl;
    }
  
}


