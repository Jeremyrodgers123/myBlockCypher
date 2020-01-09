//
//  blockCypher.cpp
//  blockCypher
//
//  Created by Jeremy Rodgers on 2/26/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#include "blockCypher.hpp"

//64 bit blocks

//64 bit key


//compute secret key based on a password
//use hash
void checkArrays(std::array<std::array<uint8_t, 256>, 8> &subTables){
    for(int i = 0; i < 8; i++){
        std::cout << "array " << i << ": " <<std::endl;
        for (int j = 0; j < 256; j++){
            int temp = (int) subTables[i][j];
            std::cout << temp << " ";
        }
        std::cout << std::endl;
    }
}

void checkArr(std::array<uint8_t, 256> table){
    for (int j = 0; j < 256; j++){
        int temp = (int) table[j];
        std::cout << temp << " ";
    }
    std::cout << std::endl;
}

void printCharNumbers(unsigned char state []){
    for(int i = 0; i < 8; i++){
        std::cout << (int)state[i] <<" ";
    }
    std::cout << std::endl;
}

void myXOR(uint8_t key [], unsigned char state []){
    for(int i = 0; i < 8; i++){ //note 8 is the number of bytes in both arrays
        state[i] = state[i] ^ key[i];
    }
}

void substitute(const int &size, std::array<std::array<uint8_t, 256>, 8> &subTables, unsigned char state [] ){
    for(int i = 0; i < size; i++){
        //unsigned char temp = subTables[i][state[i]];
        state[i] = subTables[i][state[i]];
    }
}

void undoSubstitute(const int &size, std::array<std::array<uint8_t, 256>, 8> &subTables, unsigned char state [] ){
    for(int i = size -1; i >= 0; i--){
        for(int j = 0; j < 256; j++){
            //unsigned char temp = state[i];
            if(subTables[i][j] == state[i]){
                state[i] = j;
                break;
            }
        }
        
    }
}

void print(const uint8_t arr [], const int &size){
    for(int i = 0; i < size; i++){
        std::cout << unsigned(arr[i]) << " ";
    }
    std::cout << std::endl;
}

std::array<uint8_t, 256> createIdentityArr(const int &size){
    std::array<uint8_t, 256> arr;
    for(int i = 0; i < size; i++){
       arr[i] = i;
    }
    return arr;
}

void rotateLeft(const int &size, unsigned char state []){
    unsigned char firstBit = (state[0] & 0x80) >> 7;
    for(int i = 0; i < size - 1; i++){
        //get top bit of next byte
        unsigned char carryBit = (state[i + 1] & 0x80) >> 7;
        //shift target byte and merge
        state[i] = (state[i] << 1) | carryBit;
    }
     state[size - 1] = (state[size - 1] << 1) | firstBit;
}

void rotateRight(const int &size, unsigned char state []){
    unsigned char currentCarryBit = (state[size -1] & 0x01) << 7;
    
    for(int i = 0; i < size; i++){
        //get top bit of next byte
        unsigned char nextCarryBit = (state[i] & 0x01) << 7 ;
        //shift target byte and merge
        state[i] = (state[i] >> 1) | currentCarryBit;
        currentCarryBit = nextCarryBit;
    }
}

bool hasDups(std::vector<int>& dups, int insertVal){
    for(uint8_t val : dups){
        if(val == insertVal){
            return true;
        }
    }
    return false;
}

std::array<uint8_t, 256> shuffle(std::array<uint8_t, 256> &prevTable){
    std::array<uint8_t, 256> arr = prevTable;
    //checkArr(arr);
    int size = 256;
    for(int i = size -1; i > 0; i--){
        int j = rand() % (i+1);
        //std::cout << "i: " << i+1 << std::endl;
        assert(j <= i);
        if(arr[j] == arr[i]){
            continue;
        }
        uint8_t temp = arr[i];
        //int checkVal = (int) arr[j];
        arr[i] = arr[j];
        arr[j] = temp;
        //std::cout << "swap " << j << ":" << (int)arr[j] << " with " << i << ":" << (int)arr[i] <<std::endl;
    }
//    std::vector<int> checkForDups;
//    for(int i = 0; i < arr.size(); i++){
//
//        if(hasDups(checkForDups, arr[i])){
//            std::cout << "trouble " << std::endl;
//        }
//        checkForDups.push_back(arr[i]);
//    }
    return arr;
}

void createKey(std::string passcode, uint8_t key []){
    for(int i = 0; i < passcode.length(); i++){
        int index = i % 8;
        key[index] = key[index] ^ passcode.at(i) ;
    }
    //print(key, 8);
}
//TODO: compute set of substitution tables
//substitution == 256 element []
//start with regular 0 - 255 and then shuffle

//TODO: write encryption algorithm

void writeStateToMessage(){
    
}
/**
 note: currently there is a null turminator int unsigned char []. size is decremented by 1 to not allow it to be accessed. 
 
 **/
void encrypt(unsigned char state [], std::string passcode, Encrypted &encrypted){
    int size = 8;
    uint8_t key [] = {0,0,0,0,0,0,0,0};
    createKey(passcode, key);
   
    for(int roundNum = 0; roundNum < 16; roundNum++){
        myXOR(key, state);
        substitute(size, encrypted.subTables, state);
        rotateLeft(size, state);
    }
    encrypted.addMessage(8, state);
}

void decrypt(std::string passcode, Encrypted &encrypted){
     uint8_t key [] = {0,0,0,0,0,0,0,0};
     createKey(passcode, key);
    //right shift key
    for(int i = 16; i > 0; i--){
        rotateRight(8, encrypted.message);
        //undo substitution
        undoSubstitute(8, encrypted.subTables, encrypted.message);
        myXOR(key, encrypted.message);
    }
    
    std::cout << "decrypted message: " << encrypted.messageToString() <<std::endl;
}
