//  functions.h


#include "disk.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <limits>

#define dirTable_max_size 15

struct inode
{
    char fileName[50];
    char timeStamp[50];
    char type;
    int startBlock;
};

struct dirTable
{
    int inode_no;
    inode inode_array[dirTable_max_size];
};

//Data Blocks
struct dataBlock_struct {
    int blockNum;
    int fileSize;
    int dataSize;
    int readptr;
    int link;
};

dirTable* getRootDirTable();

void initRootDir();
char *getPath();
void welcome();
void listCommands();
void makeChoice();
void checkFileSize(string inputSizeStr);
void getTimeStamp(char *timeStamp);

int createFile(char fileName[], int fileSize);
int createDir(char dirName[]);
int deleteFile(char fileName[]);
int deleteDir(char fileName[]);
int changeDir(char dirName[]);
int copyFile(char fileName[], char fileName2[]);
void dir();
int sum(dirTable* currentDirTable);

int changeName(char oldName[], char newName[]);

int cat(char fileName[]);
int doCat(dataBlock_struct* thisDataBlock);
int populateRandomStringToFile(char fileName[]);
int rewrite(char fileName[], char content[]);
int writeToFile(dataBlock_struct* thisDataBlock, char content[]);
int releaseFile(int dataBlock);
int addDirUnit(dirTable* currentDirTable, char fileName[], int type, int dataBlock_no);
int createDataBlock(int dataBlock_no, int fileBlock_no, int fileSize);
int deleteFileInTable(dirTable* myDirTable, int unitIndex);
int deleteDirUnit(dirTable* currentDirTable, int unitIndex);
int findUnitInTable(dirTable* currentDirTable, char unitName[]);
int showRootSum();


//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

// i-Node-Based Unix-Style File System
//
//  Created by MR.JON on 16/06/2020.
//  Copyright © All rights reserved 

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------