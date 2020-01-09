//
//  main.c
//  rc4
//
//  Created by Jeremy Rodgers on 4/9/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include "rc4.h"
int main(int argc, const char * argv[]) {
    assert(argc == 2);
    
    char* passcode = (char *) argv[1];
    char message [] = "My encrypted message";
    struct RC4 *rc4;
    rc4 = initRC4(passcode);
    print(rc4);
    int msgSize = sizeof(message) -1;
    char *cypher = myEncrypt(rc4, message, msgSize);
    printS(cypher, msgSize);
    rc4 = initRC4(passcode);
    char *plainTxt = myEncrypt(rc4, cypher, msgSize);
    printS(plainTxt, msgSize);
    printf("\n");
    return 0;
}
