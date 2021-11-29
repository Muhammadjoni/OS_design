//  main.cpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include "functions.h"
#include "disk.h"
#include "stdlib.h"

using namespace std;


int main()
{

    initialize();
    initRootDir();

    string a="";
    welcome();
    makeChoice();
    //char command[10];


    ifstream infile;
    infile.open("out.txt");

    string s;

    while (getline(infile, s))
    {
        string subs[3];
        int count = 0;
        for (int i = 0; i < s.length(); i++) {

            if (s[i] != ' ') {
                subs[count] = subs[count] + s[i];
            }
            else {
                count++;
            }
        }


        if (strcmp(subs[0].c_str(), "dir") == 0) {
            dir();
            
			//printf("ls\n");

        }
        else if (strcmp(subs[0].c_str(), "help") == 0)
        {
            listCommands();
        }
        else if (strcmp(subs[0].c_str(), "changeDir") == 0)
        {
            changeDir((char*)subs[1].c_str());

        }
        else if (strcmp(subs[0].c_str(), "currentPath") == 0)
        {
            printf("%s\n", getPath());
        }
        else if (strcmp(subs[0].c_str(), "createDir") == 0)
        {
            createDir((char*)subs[1].c_str());
        }
        else if (strcmp(subs[0].c_str(), "deleteDir") == 0)
        {
            deleteDir((char*)subs[1].c_str());
        }
        else if (strcmp(subs[0].c_str(), "rename") == 0)
        {
            changeName((char*)subs[1].c_str(), (char*)subs[2].c_str());

        }
        else if (strcmp(subs[0].c_str(), "createFile") == 0)
        {
            int b = atoi(subs[2].c_str());
            createFile((char*)subs[1].c_str(), b);
        }
        else if (strcmp(subs[0].c_str(), "deleteFile") == 0)
        {
            deleteFile((char*)subs[1].c_str());
        }
        else if (strcmp(subs[0].c_str(), "cat") == 0)
        {
            int b = atoi((char*)subs[2].c_str());
            cat((char*)subs[1].c_str());

        }
        else if (strcmp(subs[0].c_str(), "write") == 0)
        {
            populateRandomStringToFile((char*)subs[1].c_str());
        }
        else if (strcmp(subs[0].c_str(), "rewrite") == 0)
        {
            rewrite((char*)subs[1].c_str(), (char*)subs[2].c_str());

        }
        else if (strcmp(subs[0].c_str(), "cp") == 0)
        {
            copyFile((char*)subs[1].c_str(), (char*)subs[2].c_str());
        }
        else if (strcmp(subs[0].c_str(), "sum") == 0)
        {
            int totalBlocks = showRootSum();
            printf("total blocks used:%d\n", totalBlocks);
            printf("total blocks unused:%d\n", BLOCK_COUNT - BITMAP_BLOCK_COUNT - totalBlocks);
        }

    }
    infile.close();

    fstream fs;
    ofstream out1("out.txt");
    out1 << a.c_str();

    exit();

    return 0;
}


//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

// i-Node-Based Unix-Style File System
//
//  Created by MR.JON on 16/06/2020.
//  Copyright © All rights reserved 

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------