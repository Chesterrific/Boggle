/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Chester Guinto 
 *
 * Created on February 14, 2017, 3:06 PM
 */

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Dictionary.h"

using namespace std;

const int BOARD_DIMENSIONS = 4;


void BoggleSolverHelper(int row, int col, int letterNum, int &numSol, string currLetter, string currWord, string finalWord, string Board[][BOARD_DIMENSIONS], string BoardCopy[][BOARD_DIMENSIONS],int UsedLetter[][BOARD_DIMENSIONS], Dictionary dictionary, Dictionary &foundWords, bool &end, bool print,ofstream &outfile){
       
    if(end)
        return;
    
    //checks to see if we searched the whole board
    if(row == BOARD_DIMENSIONS && col == BOARD_DIMENSIONS){
        end = true;
        return;
    }
    
    //checks bounds of board
    if(row < 0 || row > BOARD_DIMENSIONS - 1 || col < 0 || col > BOARD_DIMENSIONS - 1)
        return;
    
    if(UsedLetter[row][col] != 0)
        return;
    
    currLetter = Board[row][col];
    //first time through recursion
    if(currWord == "")
        currWord = currLetter;
    //otherwise, adds currLetter to currWord
    else
        currWord = currWord + currLetter;
    
    //checks to see if currWord is a prefix
    if(!dictionary.isPrefix(currWord)){
        return;
    }
    //if word has already been found, return out
    if(foundWords.isWord(currWord))
        return;
    
    //sets letter as used
    UsedLetter[row][col] = letterNum;
    BoardCopy[row][col] = "'" + BoardCopy[row][col] + "'";
    letterNum++;
    
    //checks to see if currWord is a word in dictionary
    if(dictionary.isWord(currWord)){
        foundWords.addWord(currWord);
        finalWord = currWord;
        numSol++;
        outfile <<  "Word #" << numSol << ": " << finalWord << "\r\n";
        //prints out solution for word a.k.a path
        if(print){
            for(int rows = 0; rows < BOARD_DIMENSIONS; rows++){                            
                outfile << "Row " << rows << ": ";
                for(int cols = 0; cols <  BOARD_DIMENSIONS; cols++){
                    outfile << setw(6) << BoardCopy[rows][cols]; 
                }
                outfile << "          ";
                for(int cols = 0; cols < BOARD_DIMENSIONS; cols++){
                    outfile << setw(4) << UsedLetter[rows][cols];
                }
                outfile << "\r\n";
            }
        outfile << "\r\n";
        }
    }
        
    //up
    BoggleSolverHelper(row - 1, col, letterNum, numSol, currLetter, currWord, finalWord, Board, BoardCopy, UsedLetter, dictionary, foundWords, end, print, outfile);
    
    //down
    BoggleSolverHelper(row + 1, col, letterNum, numSol, currLetter, currWord, finalWord, Board, BoardCopy, UsedLetter, dictionary, foundWords, end, print, outfile);
     
    //left
    BoggleSolverHelper(row, col - 1, letterNum, numSol, currLetter, currWord, finalWord, Board, BoardCopy, UsedLetter, dictionary, foundWords, end, print, outfile);
    
    //right
    BoggleSolverHelper(row, col + 1, letterNum, numSol, currLetter, currWord, finalWord, Board, BoardCopy, UsedLetter, dictionary, foundWords, end, print, outfile);
    
    //up-left
    BoggleSolverHelper(row - 1, col - 1, letterNum, numSol, currLetter, currWord, finalWord, Board, BoardCopy, UsedLetter, dictionary, foundWords, end, print, outfile);
    
    //up-right
    BoggleSolverHelper(row - 1, col + 1, letterNum, numSol, currLetter, currWord, finalWord, Board, BoardCopy, UsedLetter, dictionary, foundWords, end, print, outfile);
    
    //down-left
    BoggleSolverHelper(row + 1, col - 1, letterNum, numSol, currLetter, currWord, finalWord, Board, BoardCopy, UsedLetter, dictionary, foundWords, end, print, outfile);
    
    //down-right
    BoggleSolverHelper(row + 1, col + 1, letterNum, numSol, currLetter, currWord, finalWord, Board, BoardCopy, UsedLetter, dictionary, foundWords, end, print, outfile);
    
    //resets letter used to 0 when no other words can be formed on top of currWord    
    UsedLetter[row][col] = 0;
    BoardCopy[row][col] = Board[row][col];
    
    return;
};

void BoggleSolver(string Board[][BOARD_DIMENSIONS], string BoardCopy[][BOARD_DIMENSIONS], Dictionary dictionary, Dictionary &foundWords, ofstream &outfile, bool print){
    int numSol = 0;
    for(int row = 0; row < BOARD_DIMENSIONS; row++){
        for(int col = 0; col < BOARD_DIMENSIONS; col++){
            int UsedLetter[BOARD_DIMENSIONS][BOARD_DIMENSIONS];                         //solution matrix
            //initializing UsedLetter matrix
            for(int rows = 0; rows < BOARD_DIMENSIONS; rows++){
                for(int cols = 0; cols < BOARD_DIMENSIONS; cols++){
                UsedLetter[rows][cols] = 0;
                }
            }
            string currLetter = "";
            string currWord = "";
            string finalWord = "";
            bool end = false;
            int letterNum = 1;
            BoggleSolverHelper(row, col, letterNum, numSol, currLetter, currWord, finalWord, Board, BoardCopy, UsedLetter, dictionary, foundWords, end, print, outfile);
        }
    }
    cout << "# of words found: " << numSol << endl;
};

int main(int argc, char** argv) {

    Dictionary dictionary("dictionary");
    Dictionary foundWords;
    
    string Board[BOARD_DIMENSIONS][BOARD_DIMENSIONS];                           //creating the boggle board
    string BoardCopy[BOARD_DIMENSIONS][BOARD_DIMENSIONS];                       //copy of board for solutions
    
    char answer;
    bool print = false;
    string inputLine;
    
    ofstream outfile;
    outfile.open("out.txt");
    
    //User input for boggle board
    cout << "Enter board: (With spaces in between each letter) \r\n";
    for(int row = 0; row < BOARD_DIMENSIONS; row++){                           
        cout  << "Row " << row << ": ";
        getline(cin, inputLine);
        stringstream ss(inputLine);                                             //stringstream to input board in one line 
        int col = 0;
        while(ss >> Board[row][col])
            col++;
    }
    
    //copying board to board copy
    for(int row = 0; row < BOARD_DIMENSIONS; row++){                            
        for(int col = 0; col <  BOARD_DIMENSIONS; col++){
            BoardCopy[row][col] = Board[row][col];
        }
    }
    outfile << "Boggle Board \r\n";
    for(int row = 0; row < BOARD_DIMENSIONS; row++){                            //double for loop to display board
        outfile << "Row " << row << ": ";
        for(int col = 0; col <  BOARD_DIMENSIONS; col++){
            outfile << setw(4) << Board[row][col];
        }
        outfile << "\r\n";
    }
    outfile << "\r\n";
    cout << "Print Solutions(Y/N)?: ";
    cin >> answer;
    if(answer == 'Y')
        print = true;
    
    BoggleSolver(Board, BoardCopy, dictionary, foundWords, outfile, print);
    outfile.close();
    return 0;
}


