//
//  main.cpp
//  MineSweeper2
//
//  Created by David Slakter on 2/9/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Minesweeper{
private:

    const int GRAPH_SIZE = 10;
    
    struct tile{
        int value = 0;
        bool isVisible = false;
        
        bool hasBomb(){
            return (value == -1);
        }
    };
   
    vector<vector<tile>> tileGraph;
    
    
    void populateGraph(){
        
        //seed random generator
        srand(time(0));
        
        //set the blank tiles and bombs, add extra row and column for border
        for (int i = 0; i <= GRAPH_SIZE + 1; ++i){
            vector<tile> tilerow;
        
            for(int j = 0; j <= GRAPH_SIZE + 1; ++j){
                tile newTile;
                
                //check if tile is within the graph size
                if(i <= GRAPH_SIZE && j <= GRAPH_SIZE && i > 0 && j > 0){
                    
                    int random = rand() % 10; //random number between 0 and 9 inclusive
                    if (random == 0){
                        newTile.value = -1; //set tile as a bomb
                    }

                }
                //add to tilerow
                tilerow.push_back(newTile);
                
            }
            tileGraph.push_back(tilerow);
        }
        
        //set the tile values depending on surrounding bombs
        for (int i = 1; i <= GRAPH_SIZE; ++i){
            for(int j = 1; j <= GRAPH_SIZE; ++j){
                if (tileGraph[i][j].value == 0){
                
                    int n1 = tileGraph[i+1][j].value;
                    int n2 = tileGraph[i-1][j].value;
                    int n3 = tileGraph[i][j + 1].value;
                    int n4 = tileGraph[i][j - 1].value;
                    int n5 = tileGraph[i + 1][j + 1].value;
                    int n6 = tileGraph[i - 1][j - 1].value;
                    int n7 = tileGraph[i + 1][j - 1].value;
                    int n8 = tileGraph[i - 1][j + 1].value;
                    
                    int nSum = 0;
                    if (n1 == -1){
                        nSum++;
                    }
                    if (n2 == -1){
                        nSum++;
                    }
                    if (n3 == -1){
                        nSum++;
                    }
                    if (n4 == -1){
                        nSum++;
                    }
                    if (n5 == -1){
                        nSum++;
                    }
                    if (n6 == -1){
                        nSum++;
                    }
                    if (n7 == -1){
                        nSum++;
                    }
                    if (n8 == -1){
                        nSum++;
                    }
                    
                    tileGraph[i][j].value = nSum;
                }
            }
        }
    }
    
    void remove(int row, int col){

        tile aTile = tileGraph[row][col];
        if(aTile.isVisible == false){
            tileGraph[row][col].isVisible = true;
            if (tileGraph[row][col].value == 0){
                if (row > 0 && row <= GRAPH_SIZE && col > 0 && col <= GRAPH_SIZE){
        
                    remove(row + 1, col);
                    remove(row - 1, col);
                    remove(row, col - 1);
                    remove(row, col + 1);
                    remove(row + 1, col + 1);
                    remove(row - 1, col - 1);
                    remove(row - 1, col + 1);
                    remove(row + 1, col - 1);
                }
            }
        }
    }
    
    
    
    
public:
    Minesweeper(){
        populateGraph();
    }
    
    bool done(){
        for (int i = 1; i <= GRAPH_SIZE; ++i){
            for(int j = 1; j <= GRAPH_SIZE; ++j){
                if (tileGraph[i][j].isVisible == false){
                    if (tileGraph[i][j].value != -1){
                        return false;
                    }
                   
                }
            }
        }
        return true;
    }
    
    bool validRow(int row){
        if (row < tileGraph.size()){
            return true;
        }
        return false;
    }
    
    bool isVisible(int row, int col){
        if (tileGraph[row][col].isVisible){
            return true;
        }
        return false;
    }
    
    bool play(int selected_row, int selected_col){
    
        if (tileGraph[selected_row][selected_col].value == -1){
            return false; //returns false if selected tile is a bomb
        }
        else{
            remove(selected_row, selected_col);
            return true;
        }
    }

    void display(bool showBombs){
        for (int i = 1; i <= GRAPH_SIZE; ++i){
            
            for(int j = 1; j <= GRAPH_SIZE; ++j){
            
                if (tileGraph[i][j].isVisible){
                    cout << tileGraph[i][j].value << "\t";
                }
                else{
                   if (showBombs && tileGraph[i][j].value == -1){
                        cout << -1 << "\t";
                   }
                   else{
                        cout << "x" << "\t";
                    }
                }
            }
            cout << endl;
        }
    }
};


int main() {
    Minesweeper sweeper;
    // Continue until only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display board without bombs

        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if (!sweeper.validRow(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); // Final board with bombs shown
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
}
