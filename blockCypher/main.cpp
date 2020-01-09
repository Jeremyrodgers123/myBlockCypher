//
//  main.cpp
//  blockCypher
//
//  Created by Jeremy Rodgers on 2/26/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#include <iostream>
#include "blockCypher.hpp"
#include "tests.hpp"
#include "RC4.hpp"


int main(int argc, const char * argv[]) {
     srand (time(NULL));
    //testShuffle();
    //test();
    std::cout << "*********************************" << std::endl;
    RC4 rc4 = RC4("Jeremy");
    std::string secretMessage = "My encrypted message";
    std::string cypher = rc4.encrypt(secretMessage);
     std::string secretMessage2 = "my top secret message";
    std::string cypher2 = rc4.encrypt(secretMessage2);
    
    std::cout << "original: " << secretMessage << std::endl;
    std::cout << "cypher: " << cypher << std::endl;
    std::string answer = rc4.encrypt(cypher);
    std::string answer2 = rc4.encrypt(cypher2);
    
    std::cout << "decrypted: " << answer << std::endl;
    std::cout << "decrypted2: " << answer2 << std::endl;
    
    RC4 rc42 = RC4("Jeremyodgers");
    std::string decryptWwrongKey = rc42.encrypt(cypher);
    std::cout << "decrypted with wrong key: " << decryptWwrongKey << std::endl;
    
    RC4 sameKeystream = RC4("JeremyRodgers");
    std::string dangerousCypher = sameKeystream.encrypt("new secret message");
    std::string xordMessages= "";
    for(int i = 0; i < dangerousCypher.length(); i++){
       xordMessages +=  dangerousCypher.at(i) ^ cypher.at(i);
    }
    std::string knownText = "new secret";
    for(int i = 0; i < knownText.length(); i++){
        std::cout << (char)(xordMessages.at(i) ^ knownText.at(i));
    }
    std::cout << xordMessages << std::endl;
    std::cout << std::endl;
    
    RC4 salaryStream = RC4("salary");
    std::string salary = salaryStream.encrypt("Your salary is $1000");
    std::cout << "salary: " << salary << std::endl;
    std::string newSalary = "";
    for(int i = 0; i < salary.length(); i++){
        if(i == 16){
            newSalary += salary.at(i) ^ 0x08;
            std::cout << i<<": " << salary.at(i) << std::endl;
        }else if (i == 17 || i == 18 || i == 19){
            newSalary += salary.at(i) ^ 0x09;
            std::cout << i<<": " << salary.at(i) << std::endl;
        }else{
            newSalary += salary.at(i);
        }
    }
    std::cout << "new Salary Encrypted: "<< newSalary << std::endl;
    std::string decryptedSalary = salaryStream.encrypt(newSalary);
    std::cout << "new Salary Decrypted: "<< decryptedSalary << std::endl;
    std::cout << std::endl;
    
    return 0;
}
