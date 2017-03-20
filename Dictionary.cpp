#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "Dictionary.h"

using namespace std;

void Dictionary::addWord(string word){
    Node *currentNode = top;
    if(currentNode == NULL){                                                    //if prefix tree is empty, create new first node
        currentNode = new Node;
        top = currentNode;
        for(int i = 0; i < LETTERS; i++){
        currentNode->abc[i] = NULL;                                             //initializes pointer array of new node to NULL
        currentNode->Word[i] = false;                                           //initializes word array of new node to false
        } 
    }
    for(int i = 0; i < word.length(); i++){
        int index = (int)word[i] - (int)'a';
        if(currentNode->abc[index] == NULL){
            currentNode->abc[index] = new Node;                                 //creates new node for next letter
            if(i == word.length()-1){                                           //final loop iteration, adding true to end of loop
                currentNode->Word[index] = true;                                //signals end of word
            }
            currentNode = currentNode->abc[index];                              //moves current node to next node down for the next letter in the word
            for(int i = 0; i < LETTERS; i++){
            currentNode->abc[i] = NULL;                                         //initializes pointer array of new node to NULL
            currentNode->Word[i] = false;                                       //initializes word array of new node to false
            }   
        }
        else                                                                    //if a path already exists, aka the letter has already been used to point to another  
            currentNode = currentNode->abc[index];                              //node, the function moves currentNode down to that node and moves on to next letter         
    }                                                                          
    numWords++;
}
bool Dictionary::isWord(string word){
    Node *currentNode = top;
    int index = 0;
    for(index; index < word.length()-1; index++){                               //loops through size of word
        if(currentNode->abc[(int)word[index] - (int)'a'] == NULL)               //checks to see if letter exists in prefix tree
            return currentNode->Word[(int)word[index] - (int)'a'];              //returns flag at end of path
        else
            currentNode = currentNode->abc[(int)word[index] - (int)'a'];        //traverses to next letter/node
    }
    return currentNode->Word[(int)word[index] - (int)'a'];
}
bool Dictionary::isPrefix(string prefix){
    Node *currentNode = top;
    int index = 0;
    for(index; index < prefix.length(); index++){                               //same basic function as isWord
        if(currentNode->abc[(int)prefix[index] - (int)'a'] == NULL){
            return false;
        }
        else
            currentNode = currentNode->abc[(int)prefix[index]- (int)'a'];
    }
    return true;
}
