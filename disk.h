//  disk.h


#ifndef disk_h
#define disk_h

#define TOTAL_MEMORY_SPACE  16*1024*1024  //16 MB total space in memory for the file-system.
#define BLOCK_SIZE 1024  //Block size is 1 KB
#define BLOCK_COUNT TOTAL_MEMORY_SPACE/BLOCK_SIZE
#define BITMAP_BLOCK_COUNT BLOCK_COUNT/BLOCK_SIZE
#define ADDRESS_LENGTH 3 // 24 Bit = 3 Byte

#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <math.h>
#include <iomanip>

using namespace std;

void initialize();
int getBlock(int blockSize);
char* getBlockAddr(int blockNum);
int getAddrBlock(char* addr);
int releaseBlock(int blockNum, int blockSize);
void exit();


#endif /* disk_h */


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// i-Node-Based Unix-Style File System
//
//  Created by MR.JON on 16/06/2020.
//  Copyright © All rights reserved 

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

