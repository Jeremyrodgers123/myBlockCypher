//
//  tests.hpp
//  blockCypher
//
//  Created by Jeremy Rodgers on 2/26/19.
//  Copyright © 2019 Jeremy Rodgers. All rights reserved.
//

#ifndef tests_hpp
#define tests_hpp
//#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include <stdio.h>
#include <set>
void testShuffle();
void testTableInit();
void testRotateLeft();
void testRotateRight();
void testEncrypt();
void testDecrypt();
void testKeys();
void testKeyDiff();
void testAddMessage();
void testMyXor();
void testSubstitution();
void subUnsub();
void testIncorrectDecrypt();
void test();
#endif /* tests_hpp */
