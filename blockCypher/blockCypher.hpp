//
//  blockCypher.hpp
//  blockCypher
//
//  Created by Jeremy Rodgers on 2/26/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef blockCypher_hpp
#define blockCypher_hpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include <array>
std::array<uint8_t, 256> createIdentityArr(const int &size);
std::array<uint8_t, 256> shuffle(std::array<uint8_t, 256> &prevTable);
void checkArrays(std::array<std::array<uint8_t, 256>, 8> &subTables);
void checkArr(std::array<uint8_t, 256> table);

struct Encrypted{
    std::array<std::array<uint8_t, 256>, 8> subTables;
    Encrypted(){
        //create identity tables
        subTables.at(0) = createIdentityArr(256);
        
        for(int i = 1; i < subTables.size(); i++){
            subTables[i] = shuffle(subTables[i - 1]);
        }
    }
    
    unsigned char message [8] = {0,0,0,0,0,0,0,0};
    
    void addMessage(const int &size, const unsigned char m []){
        for(int i = 0; i < size; i++){
            message[i] = m[i];
        }
    }
    
    void printMessageAsDec(){
        for(unsigned char c : message){
            std::cout << (int) c << " ";
        }
        std::cout << std::endl;
    }
    
    std::string messageToString(){
        std::string output = "";
        for (int i = 0; i < 8; i++){
            if(message[i] == '\0') continue;
            output += message[i];
            
        }
        return output;
    }
};

void printCharNumbers(unsigned char state []);
void print(const uint8_t arr [], const int &size);
void myXOR(uint8_t key [], unsigned char state []);
void substitute(const int &size, std::array<std::array<uint8_t, 256>, 8> &subTables, unsigned char state [] );
void undoSubstitute(const int &size, std::array<std::array<uint8_t, 256>, 8> &subTables, unsigned char state []);
void rotateLeft(const int &size, unsigned char state []);
void rotateRight(const int &size, unsigned char state []);
void createKey(std::string passcode, uint8_t key []);
void encrypt(unsigned char state [], std::string passcode, Encrypted &encrypted);
void decrypt(std::string passcode, Encrypted &encrypted);

#endif /* blockCypher_hpp */
