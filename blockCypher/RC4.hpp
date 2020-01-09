//
//  RC4.hpp
//  blockCypher
//
//  Created by Jeremy Rodgers on 2/27/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef RC4_hpp
#define RC4_hpp

#include <stdio.h>
#include "blockCypher.hpp"
class RC4{
    std::array<uint8_t, 256> arr;
    public:
    RC4(std::string passcode){
        arr =  createIdentityArr(256);
        uint8_t key [] = {0,0,0,0,0,0,0,0};
        createKey(passcode, key);
        int j = 0;
        for(int i = 0; i < 256; i++){
            j = (j + arr[i] + key[i % 8] ) % 256;
            std::swap(arr[i], arr[j]);
        }
    }
    std::string vectorToString(std::vector<char> data){
        std::string ret = "";
        for(int i = 0; i < data.size(); i++){
            ret += data.at(i);
        }
        return ret;
    }

    std::string encrypt(std::string message){
        int i = 0;
        int j = 0;
        std::vector<char> cypherText;
        for(int k = 0; k < message.length(); k++){
            i = (i + 1) % 256;
            j = (j + 1) % 256;
            std::swap(arr[i], arr[j]);
            int t = (arr[i] + arr[j]) % 256;
            cypherText.push_back( arr[t] ^ message.at(k) );
            std::cout << (arr[t] ^ message.at(k)) << "\n";
        }
        std::string ret =  vectorToString(cypherText);
        return ret;
    }
    
    void checkArr(){
        for(int i = 0; i < arr.size(); i++){
            std::cout << (int) arr[i] << " ";
        }
        std::cout << std::endl;
    }
};
#endif /* RC4_hpp */
