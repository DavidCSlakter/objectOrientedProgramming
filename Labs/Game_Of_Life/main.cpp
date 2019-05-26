//
//  main.cpp
//  Game_Of_Life
//
//  Created by David Slakter on 1/26/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


vector<vector<int>> readFileAndPrint(string fileName) {

    ifstream initialGen(fileName); // reads file
    if (!initialGen) {
        cerr << "failed to open file\n"; //prints error
        exit(1);
    }

    cout << "==================================" << endl;
    cout << "Initial world" << endl;
    
    vector<vector<int>> graph;
    vector<int> falseLine;
    string line;
    
    for (int i = 0; i < 22; ++i){
        falseLine.push_back(0);
    }
    
    graph.push_back(falseLine);
    
    while (getline(initialGen, line)) {
        vector<int> lineBool;
        lineBool.push_back(0);
        
        for (char& c: line){

            if (c == '-'){
                c = ' ';
                lineBool.push_back(0);
            }
            else{
                lineBool.push_back(1);
            }
            cout << c;
        }

        cout << endl;
        
        lineBool.push_back(0);
        graph.push_back(lineBool);
    }
    
    graph.push_back(falseLine);
    
    return graph;
}

vector<vector<int>> printAndReturnGeneration(const int& generation, const vector<vector<int>>& graph) {
    cout << "==================================" << endl;
    cout << "Generation: " << generation << endl;
    vector<string> line;
    
    vector<vector<int>> newGraph = graph;
    
    for (size_t i = 1; i < graph[0].size() - 14; ++i){
        for (size_t j = 1; j < graph.size() + 7; ++j){
        
            int n1 = graph[i - 1][j];
            int n2 = graph[i + 1][j];
            int n3 = graph[i][j + 1];
            int n4 = graph[i][j - 1];
            int n5 = graph[i + 1][j + 1];
            int n6 = graph[i + 1][j - 1];
            int n7 = graph[i - 1][j + 1];
            int n8 = graph[i - 1][j - 1];
            
            int nSum = n1 + n2 + n3 + n4 + n5 + n6 + n7 + n8;
            
          //  cout << i << ' ' << j << endl;
            
            if (graph[i][j] == 1){
                if (nSum == 2 || nSum == 3){
                    newGraph[i][j] = 1;
                }
                else{
                    newGraph[i][j] = 0;
                }
            }
            else{
                if (nSum == 3){
                    newGraph[i][j] = 1;
                }
                else{
                    newGraph[i][j] = 0;
                }
                
            }
        }
    }
    
    for (const vector<int>& line: newGraph){
        for (int i: line){
             if (i == 1){
                cout << '*';
             }
             else{
                cout << ' ';
             }
        }
        cout << endl;
    }
    
    return newGraph;
    
}

int main() {
    const int GENERATIONS = 10;
    string fileName = "life.txt";
    vector<vector<int>> graph = readFileAndPrint(fileName);
    vector<vector<int>> newGraph = printAndReturnGeneration(1, graph);
    
    for (int i = 2; i <= GENERATIONS; ++i){
        newGraph = printAndReturnGeneration(i, newGraph);
    }

}


