//  disk.cpp


#include<stdio.h>
#include<stdlib.h>
#include "disk.h"


char *systemStartAddr;

void initialize()
{
    systemStartAddr = (char*)malloc(TOTAL_MEMORY_SPACE * sizeof(char)); //Allocate a block of memory

    for(int i = 0; i < BLOCK_COUNT; i++)
        systemStartAddr[i] = '0'; 

    int bitMapSize = (BLOCK_COUNT * sizeof(char)) / BLOCK_SIZE;
    for(int i = 0; i < bitMapSize; i++)
        systemStartAddr[i] = '1'; 
}

void exit()
{
    free(systemStartAddr);
}

int getBlock(int blockSize)
{
    int startBlock = 0;
    int sum = 0;
    for(int i = 0; i < BLOCK_COUNT; i++)
    {
        if(systemStartAddr[i] == '0')
        {
            if(sum == 0)
                startBlock = i;
            sum++;
            if(sum == blockSize) 
            {
                for(int j = startBlock; j < startBlock+blockSize; j++)
                    systemStartAddr[j] = '1';  
                return startBlock; 
            }
        }
        else
            sum = 0;
    }
    printf("Not enough space. Delete files to release more memory.\n");
    return -1;
}

char* getBlockAddr(int blockNum)
{
    return systemStartAddr + blockNum * BLOCK_SIZE;
}

int getAddrBlock(char* addr)
{
    return (addr - systemStartAddr)/BLOCK_SIZE;
}

int releaseBlock(int blockNum, int blockSize)
{
    int endBlock = blockNum + blockSize;

    for(int i = blockNum; i < endBlock; i++)
        systemStartAddr[i] = '0';
    return 0;
}



//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// i-Node-Based Unix-Style File System
//
//  Created by MR.JON on 16/06/2020.
//  Copyright © All rights reserved 

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
