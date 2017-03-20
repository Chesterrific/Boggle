/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dictionary.h
 * Author: Chester Guinto 
 *
 * Created on February 14, 2017, 3:06 PM
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

const int LETTERS = 26;

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

class Dictionary{
private:
    struct Node{
        Node *abc[LETTERS];
        bool Word[LETTERS];
    };
    Node *top;
    int numWords;
public:
    Dictionary(){
        /*
         Function: Initializes empty object
         Pre: None
         Post: Dictionary object is initialized
         */
        top = new Node;
        //initializing an empty node
        for(int i = 0; i < LETTERS; i++){
            top->abc[i] = NULL;
            top->Word[i] = false;
        }
        numWords = 0;  
    };
    Dictionary(string file){
        /*
         Function: Initializes object with file
         Pre: None
         Post: Dictionary object is initialized with input file
         */
        top = NULL;
        numWords = 0;
        fstream infile;
        string inWord;
        try{
            infile.open(file + ".txt");
            if(!infile)
                throw string("dictionary.txt not found. \r\n");
        }
        catch(string msg){
            cerr << msg << endl;
            exit(0);
        }
        cout << "File open. \r\n";
        while(!infile.eof()){
            infile >> inWord;
            //cout << inWord << endl;
            addWord(inWord);
        }
        cout << numWords << " words have been loaded into Dictionary. \r\n";
    }
    void addWord(string word);
        /*
         Function: Adds word to dictionary
         Pre: Dictionary object exists
         Post: Word is added to object/prefix tree
         */
    bool isWord(string word);
        /*
         Function: Checks to see if word is in dictionary
         Pre: Dictionary object exists
         Post: Returns value of our bool array
         */
    bool isPrefix(string prefix);
        /*
        Function:  Checks to see if input is a prefix
        Pre: Dictionary object exists
        Post: Returns true if the order of letters given has a path down the tree
         */
    int wordCount(){
        /*
         Function: Returns numWords
         Pre: Dictionary object exists
         Post: numWords is returned
         */    
        return numWords;
    }
};
#endif /* DICTIONARY_H */

