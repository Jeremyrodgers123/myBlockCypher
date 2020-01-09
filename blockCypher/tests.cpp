//
//  tests.cpp
//  blockCypher
//
//  Created by Jeremy Rodgers on 2/26/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#include "tests.hpp"
#include "blockCypher.hpp"
//void testShuffle(){
//   std::array<uint8_t, 8> testarr[] = {0,1,2,3,4,5,6,7};
//    std::array<uint8_t, 8> checkarr = {0,1,2,3,4,5,6,7};
//    shuffle(testarr, 8);
//    bool isEqual = true;
//    for(int i = 0; i < 8; i++){
//        if(testarr[i] != checkarr[i]){
//            isEqual = false;
//            break;
//        }
//    }
//    assert(isEqual == false);
//}

void testTableInit(){
    Encrypted encrypted;
    //shuffle(subTables, 0);
    for(int i = 0; i < 8; i++){
        assert(!((encrypted.subTables[0][i] == encrypted.subTables[1][i]) &&
               (encrypted.subTables[0][i] == encrypted.subTables[2][i]) &&
               (encrypted.subTables[0][i] == encrypted.subTables[3][i]) &&
               (encrypted.subTables[0][i] == encrypted.subTables[4][i]) &&
               (encrypted.subTables[0][i] == encrypted.subTables[5][i]) &&
               (encrypted.subTables[0][i] == encrypted.subTables[6][i]) &&
               (encrypted.subTables[0][i] == encrypted.subTables[7][i])) );
    }
    //print(testarr, 256);=
}

void testRotateLeft(){
    unsigned char state [] = {0xAA, 0x99};
    rotateLeft((sizeof(state)/sizeof(*state)), state);
    assert(state[0] == 0x55 && state[1] ==0x33);
}

void testRotateRight(){
    unsigned char state [] = {0x55, 0x33};
    rotateRight((sizeof(state)/sizeof(*state)), state);
    assert(state[0] == 0xAA && state[1] ==0x99);
}

void testEncrypt(){
    unsigned char message [] = "secret1";
    Encrypted encrypted;
    encrypt(message, "JeremyRodgers", encrypted);
}

void testSubstitution(){
    unsigned char message [] = "secret1";
    Encrypted encrypted;

    for(int i = 0; i < 8; i++){
        encrypted.subTables[i][i] = i + 1;
    }
    substitute(8, encrypted.subTables, message);
    assert(encrypted.subTables[0][0] == '\01');
    assert(encrypted.subTables[1][1] == '\02');
    assert(encrypted.subTables[2][2] == '\03');
    assert(encrypted.subTables[3][3] == '\04');
    assert(encrypted.subTables[4][4] == '\05');
    assert(encrypted.subTables[5][5] == '\06');
    assert(encrypted.subTables[6][6] == '\07');
    assert(encrypted.subTables[7][7] == 8);
}

void subUnsub(){
    unsigned char message [] = "secret1";
    std::cout << "beginning" <<std::endl;
    printCharNumbers(message);
    Encrypted encrypted;
    substitute(8, encrypted.subTables, message);
    encrypted.addMessage(8, message);
    std::cout << "encrypted message: " <<std::endl;
    encrypted.printMessageAsDec();
    assert(encrypted.messageToString() != "secret1"); //assert change
    undoSubstitute(8, encrypted.subTables, encrypted.message);
    std::cout << "unencrypted message: " <<std::endl;
    encrypted.printMessageAsDec();
    assert(encrypted.messageToString() == "secret1");
    
}

void testDecrypt(){
    unsigned char message [] = "secret1";
    std::cout << "beginning" <<std::endl;
    printCharNumbers(message);
    Encrypted encrypted;
    //checkArrays(encrypted.subTables);
    encrypt(message , "JeremyRodgers", encrypted);
    std::cout << "encrypted" <<std::endl;
    encrypted.printMessageAsDec();
    decrypt("JeremyRodgers", encrypted);
    std::cout << "decrypted" <<std::endl;
    encrypted.printMessageAsDec();
    assert(encrypted.messageToString() == "secret1");
}

void testIncorrectDecrypt(){
    unsigned char message [] = "secret1";
    std::cout << "beginning" <<std::endl;
    printCharNumbers(message);
    Encrypted encrypted;
    //checkArrays(encrypted.subTables);
    encrypt(message , "JeremyRodgers", encrypted);
    std::cout << "encrypted" <<std::endl;
    encrypted.printMessageAsDec();
    decrypt("Jeremyrodgers", encrypted);
    std::cout << "decrypted" <<std::endl;
    encrypted.printMessageAsDec();
    assert(encrypted.messageToString() != "secret1");
}


void testKeys() {
        uint8_t key1 [] = {0,0,0,0,0,0,0,0};
        createKey("JeremyRodgers", key1);
        uint8_t key2 [] = {0,0,0,0,0,0,0,0};
        createKey("JeremyRodgers", key2);
        assert(key1[0] == key2[0]);
        assert(key1[1] == key2[1]);
        assert(key1[2] == key2[2]);
        assert(key1[3] == key2[3]);
        assert(key1[4] == key2[4]);
        assert(key1[5] == key2[5]);
        assert(key1[6] == key2[6]);
        assert(key1[7] == key2[7]);
}

void testKeyDiff() {
    uint8_t key1 [] = {0,0,0,0,0,0,0,0};
    createKey("Jeremyrodgers", key1);
    uint8_t key2 [] = {0,0,0,0,0,0,0,0};
    createKey("JeremyRodgers", key2);
    assert( (key1[0] != key2[0]) || (key1[1] != key2[1]) || (key1[2] != key2[2]) ||(key1[3] != key2[3]) || (key1[4] != key2[4]) || (key1[5] != key2[5]) || (key1[6] != key2[6]) ||(key1[7] != key2[7]) );
}

void testAddMessage(){
    unsigned char m [] = {'J', 'e', 'r', 'e', 'm', 'y', 'R', 0x0};
    Encrypted encrypted;
    encrypted.addMessage(8, m);
    std::string check = encrypted.messageToString();
    assert(check == "JeremyR");
}

void testMyXor(){
    uint8_t key1 [] = {0,0,0,0,0,0,0,0};
    createKey("Jeremyrodgers", key1);
    unsigned char m [] = {'J', 'e', 'r', 'e', 'm', 'y', 'R', 0x0};
    myXOR(key1, m);
    assert((key1[0] ^ m[0]) == 'J');
    assert((key1[1] ^ m[1]) == 'e');
    assert((key1[2] ^ m[2]) == 'r');
    assert((key1[3] ^ m[3]) == 'e');
    assert((key1[4] ^ m[4]) == 'm');
    assert((key1[7] ^ m[7]) == '\0');
}

void test(){
    testTableInit();
    testKeyDiff();
    testKeys();
    testRotateLeft();
    testEncrypt();
    testRotateRight();
    testAddMessage();
    testMyXor();
    subUnsub();
    testDecrypt();
    testSubstitution();
    testIncorrectDecrypt();
}
