//  functions.cpp

#include "functions.h"
#include <string>
#include <time.h>


using namespace std;

dirTable* rootDirTable;
dirTable* currentDirTable;
string path;
string input;
int inputFileSize;
//string fileName;
char fileName[50];

dirTable* getRootDirTable()
{
    return rootDirTable;
}
void initRootDir()
{
    int startBlock = getBlock(1);
    if(startBlock == -1)
        return;
    rootDirTable = (dirTable*)getBlockAddr(startBlock);
    rootDirTable->inode_no = 0;
    
    currentDirTable = rootDirTable;
    path= "root/";
    
}
char *getPath()
{
    char directoryPath[100];
    strcpy(directoryPath, path.c_str());
    return directoryPath;
}

void getTimeStamp(char *timeStamp)
{
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    char buffer[80];
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    strcpy(timeStamp, buffer);
}

void welcome(){
    cout << "Welcome to the i-Node-Based Unix-style file system!\n";
    cout << "This project was created by:\nMichael Bashaye (201769990419), Biruk Daniel (201769990275), Abdenur Ziyad (201769990305) and Naod Shiferaw (201769990278).\n";
    cout << endl << "Type \"help\" to display a list of commands." << endl;
}

void listCommands(){
    cout << "\nList of commands (the commands are case sensitive):" << endl;
    cout << "\"createFile\"" << setw(38) << "(i.e.: createFile /dir1/myFile)" << setw(23) << " Create new file" << endl;
    cout << "\"cp\"" << setw(46) << "(i.e.: cp file1 to /dir2/file2)" << setw(20) << "Copy a file\n";
    cout << "\"cat\"" << setw(37) << "(i.e.: cat /dir1/file1)" << setw(38) << "Display file contents\n";
    cout << "\"deleteFile\"" << setw(38) << "(i.e.: deleteFile /dir1/myFile)" << setw(22) << "Delete a file\n";
    cout << "\"createDir\"" << setw(36) << "(i.e.: createDir /dir1/sub1)" << setw(30) << "Create a directory\n";
    cout << "\"deleteDir\"" << setw(36) << "(i.e.: deleteDir /dir1/sub1)" << setw(30) << "Delete a directory\n";
    cout << "\"changeDir\"" << setw(31) << "(i.e.: changeDir /dir2)" << setw(49) << "Change current working directory\n";
    cout << "\"dir\"" << setw(88) << "List all files and sub-directories\n";
    cout << "\"sum\" " << setw(87) << "Display the usage of storage space\n";
    cout << "\"help\" " << setw(68) << "Display commands\n";
    cout << "\"exit\" " << setw(85) << "Save and Exit. Unmount the disk.\n\n";
}

void makeChoice(){
    
    string inputFileName;
    int inputFileSize = 0;
    cout << path << " </>: ";
    while (true)
    {
        string command;
        cin >> command;
        istringstream ss1(command); // Used to split string around spaces.
        if ((command == "createFile") ^ (command == "cp") ^ (command == "cat") ^ (command == "deleteFile") ^ (command == "createDir") ^ (command == "deleteDir") ^ (command == "changeDir") ^ (command == "dir") ^ (command == "sum") ^ (command == "help") ^ (command == "exit"))
        {
            if(command == "createFile")
            {
                inputFileSize = 0;
                size_t pos;
                string inputSizeStr;
                cin.ignore();
                getline(cin, input);
                while (input.empty()){
                    cout << "Enter a valid filename and a filesize: ";
                    getline(cin, input);
                }
                input.append(" ");
                pos = input.find(" ");
                inputFileName = input.substr(0, pos);
                strcpy(fileName, inputFileName.c_str());
                inputSizeStr = input.substr(pos, input.length());
                //checkFileSize(inputSizeStr);
                while (inputSizeStr.empty())
                {
                    cout << "Please input a valid file size: ";
                    getline(cin, inputSizeStr);
                }
                try{
                    inputFileSize = stoi(inputSizeStr);
                }
                catch(...)
                {
                    cout << "Please input a valid file size: ";
                    cin >> inputFileSize;
                    while (cin.fail())
                    {
                        cout << "Enter filesize in KB (i.e.: 10): ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        cin >> inputFileSize;
                    }
                }
                //inputFileSize = stoi(inputSizeStr);
                createFile(fileName, inputFileSize);
                makeChoice();
            }
            else if (command == "cp")
            {
                char oldName[59];
                scanf("%s", oldName);
                char newName[59];
                scanf("%s", newName);
                copyFile(oldName, newName);
                makeChoice();
            }
            else if (command == "cat")
            {
                cin.ignore();
                getline(cin, input);
                while (input.empty()){
                    cout << "Enter a valid filename: ";
                    getline(cin, input);
                }
                cat(fileName);
                makeChoice();
            }
            else if (command == "deleteFile")
            {
                cin.ignore();
                getline(cin, input);
                while (input.empty()){
                    cout << "Enter a valid filename: ";
                    getline(cin, input);
                }
                deleteFile(fileName);
                makeChoice();
            }
            else if (command == "createDir")
            {
                cin.ignore();
                getline(cin, input);
                while (input.empty()){
                    cout << "Enter a valid directory name: ";
                    getline(cin, input);
                }
                char name[59];
                strcpy(name, input.c_str());
                createDir(name);
                makeChoice();
            }
            else if (command == "deleteDir")
            {
                cin.ignore();
                getline(cin, input);
                while (input.empty()){
                    cout << "Enter a valid directory name: ";
                    getline(cin, input);
                }
                char name[59];
                strcpy(name, input.c_str());
                deleteDir(name);
                makeChoice();
            }
            else if(command == "changeDir")
            {
                cin.ignore();
                getline(cin, input);
                while (input.empty()){
                    cout << "Enter a valid directory name: ";
                    getline(cin, input);
                }
                char name[59];
                strcpy(name, input.c_str());
                changeDir(name);
                makeChoice();
            }
            else if(command == "dir")
            {
                dir();
                cout << endl;
                makeChoice();
            }
            else if (command == "sum")
            {
                int totalBlocks = showRootSum();
                cout << "Total blocks used: " << totalBlocks << endl;
                cout << "Total blocks left: "<< BLOCK_COUNT - BITMAP_BLOCK_COUNT - totalBlocks << endl << endl;
                makeChoice();
            }
            else if (command == "help")
            {
                listCommands();
                makeChoice();
            }
            else if (command == "exit")
            {
                break;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid input. "<< endl << path << " </>: ";
        }
    }
}


void checkFileSize(string inputSizeStr)
{
    while (inputSizeStr.empty())
    {
        cout << "Please input a valid file size: ";
        getline(cin, inputSizeStr);
    }
    try{
        inputFileSize = stoi(inputSizeStr);
    }
    catch(...)
    {
        cout << "Please input a valid file size: ";
        getline(cin, inputSizeStr);
        while (inputSizeStr.empty())
        {
            cout << "Enter filesize in KB (i.e.: 10): ";
            checkFileSize(inputSizeStr);
        }
    }
}

int createFile(char fileName[], int fileSize)
{
    if(strlen(fileName) >= 50)
    {
        printf("File name is too long (maximum 50 characters).\n");
        return -1;
    }
    
    int dataBlock_no = getBlock(1);
    if(dataBlock_no == -1)
        return -1;
    
    int fileBlock = getBlock(fileSize);
    if(fileBlock == -1)
        return -1;
    
    if(createDataBlock(dataBlock_no, fileBlock, fileSize) == -1)
        return -1;
    
    if(addDirUnit(currentDirTable, fileName, 1, dataBlock_no) == -1)
        return -1;
    
    populateRandomStringToFile(fileName);
    cout << "A file with name \"" << fileName << "\" was created sucessfully!" << endl;
    return 0;
}

void dir()
{
    int unitAmount = currentDirTable->inode_no;
    cout << "Total number of files/directories: " << unitAmount << endl;
    cout << setw(20) << "Name:" << setw(25) << "Time Created:" << setw(17) << "Type:"<< setw(15) << "Size:" << setw(15) << "Inode No.:" << endl;
    for(int i = 0; i < unitAmount; i++)
    {
        inode unitTemp = currentDirTable->inode_array[i];
        cout << setw(20) <<unitTemp.fileName << setw(25) << unitTemp.timeStamp; //This is printed for both file and directory
        if(unitTemp.type == 1) //(If type == 1) file is found
        {
            int dataBlock_no = unitTemp.startBlock;
            dataBlock_struct* fileDataBlock = (dataBlock_struct*)getBlockAddr(dataBlock_no);
            cout << setw(17) << "file" << setw(15) << fileDataBlock->fileSize << setw(15) << dataBlock_no << endl;
        }
        else  //(If type == 0) Directory is found
        {
            int dirBlock = unitTemp.startBlock;
            dirTable* myTable = (dirTable*)getBlockAddr(dirBlock);
            cout << setw(17) << "directory" << setw(15) << "error" << setw(15) << myTable->inode_no << endl;
        }
    }
}

int deleteFile(char fileName[])
{
    if(strcmp(fileName, "..") == 0)
    {
        printf("can't delete ..\n");
        return -1;
    }
    int unitIndex = findUnitInTable(currentDirTable, fileName);
    if(unitIndex == -1)
    {
        printf("file not found\n");
        return -1;
    }
    inode myUnit = currentDirTable->inode_array[unitIndex];
    if(myUnit.type == 0)
    {
        printf("not a file\n");
        return -1;
    }
    int dataBlock_no = myUnit.startBlock;
    releaseFile(dataBlock_no);
    deleteDirUnit(currentDirTable, unitIndex);
    
    cout << "\"" << fileName << "\"" << " deleted sucessfully!" << endl;
    return 0;
}

int copyFile(char fileName[], char fileName2[])
{
    int unitIndex = findUnitInTable(currentDirTable, fileName);
    if (unitIndex == -1)
    {
        printf("Source file not found\n");
        return -1;
    }
    int unitIndex2 = findUnitInTable(currentDirTable, fileName2);
    if (unitIndex2 != -1)
    {
        printf("A file with that destination name already exists.\n");
        return -1;
    }
    
    int dataBlock_no = currentDirTable->inode_array[unitIndex].startBlock;
    dataBlock_struct* oldDataBlock = (dataBlock_struct*)getBlockAddr(dataBlock_no);
    
    createFile(fileName2, oldDataBlock->fileSize);
    unitIndex2 = findUnitInTable(currentDirTable, fileName2);
    int dataBlock_no2 = currentDirTable->inode_array[unitIndex2].startBlock;
    dataBlock_struct* newDataBlock = (dataBlock_struct*)getBlockAddr(dataBlock_no2);
    char* data2 = (char*)getBlockAddr(newDataBlock->blockNum);
    
    int dataSize = oldDataBlock->dataSize;
    char* data = (char*)getBlockAddr(oldDataBlock->blockNum);
    oldDataBlock->dataSize = 0;
    for (int i = 0; i < oldDataBlock->fileSize * BLOCK_SIZE && oldDataBlock->dataSize < dataSize; i++, oldDataBlock->dataSize++, newDataBlock->dataSize++)
    {
        *(data2 + newDataBlock->dataSize) = *(data + oldDataBlock->dataSize);
    }
    
    return 0;
}

int createDir(char dirName[])
{
    if(strlen(dirName) >= 59)
    {
        printf("Directory name is too long (maximum 60 characters).\n");
        return -1;
    }
    
    int dirBlock = getBlock(1);
    if(dirBlock == -1)
        return -1;
    
    if(addDirUnit(currentDirTable, dirName, 0, dirBlock) == -1)
        return -1;
    
    dirTable* newTable = (dirTable*)getBlockAddr(dirBlock);
    newTable->inode_no = 0;
    char parent[] = "..";
    if(addDirUnit(newTable, parent, 0, getAddrBlock((char*)currentDirTable)) == -1)
        return -1;
    cout << "A new directory with name \"" << dirName << "\" was sucessfully created!" << endl;
    return 0;
}

int deleteDir(char dirName[])
{
    if(strcmp(dirName, "..") == 0)
    {
        printf("Cannot delete previous directory \"..\"\n");
        makeChoice();
        return -1;
    }
    int unitIndex = findUnitInTable(currentDirTable, dirName);
    if(unitIndex == -1)
    {
        printf("No directory with such name exists.\n");
        makeChoice();
        return -1;
    }
    inode myUnit = currentDirTable->inode_array[unitIndex];
    
    if(myUnit.type == 0)
    {
        deleteFileInTable(currentDirTable, unitIndex);
    }
    else
    {
        printf("This is not a directory,\n");
        makeChoice();
        return -1;
    }
    deleteDirUnit(currentDirTable, unitIndex);
    
    cout << "The directory \"" << dirName << "\" was sucessfully deleteed!" << endl;
    return 0;
}

int changeDir(char dirName[])
{
    int unitIndex = findUnitInTable(currentDirTable, dirName);
    if(unitIndex == -1)
    {
        printf("Directory not found\n");
        return -1;
    }
    if(currentDirTable->inode_array[unitIndex].type == 1)
    {
        printf("This is a file, not a directory.\n");
        return -1;
    }
    int dirBlock = currentDirTable->inode_array[unitIndex].startBlock;
    currentDirTable = (dirTable*)getBlockAddr(dirBlock);
    if(strcmp(dirName, "..") == 0)
    {
        for (size_t i = path.length ()-3; i >= 0; i--)
        {
            if (path.at(i) == '/')
            {
                path = path.substr(0, i+1);
                break;
            }
        }
        
        
        /*pos = path.length()-(strlen(dirName)+1);
        string toRemove = path;
                toRemove.erase(toRemove.end(), toRemove.begin()); // Erase the last directory from the full pathname
         path.erase(pos, str2.length(),"preposition");*/
    }
    else
    {
        path.append(dirName);
        path.append("/");
    }
    return 0;
}

int sum(dirTable* currentDirTable)
{
    int totalBlocks = 0;
    int unitAmount = currentDirTable->inode_no;
    //printf("total:%d\n", unitAmount);
    //printf("name\ttype\tsize\tdataBlock_struct\tdataStartBlock\n");
    for (int i = 1; i < unitAmount; i++)
    {
        inode unitTemp = currentDirTable->inode_array[i];
        //printf("%s\t%d\t", unitTemp.fileName, unitTemp.type);
        if (unitTemp.type == 1)
        {
            int dataBlock_no = unitTemp.startBlock;
            dataBlock_struct* fileDataBlock = (dataBlock_struct*)getBlockAddr(dataBlock_no);
            //printf("%d\t%d\t%d\n", fileDataBlock->fileSize, dataBlock_no, fileDataBlock->blockNum);
            totalBlocks += fileDataBlock->fileSize;
        }
        else {
            int dirBlock = unitTemp.startBlock;
            dirTable* myTable = (dirTable*)getBlockAddr(dirBlock);
            //printf("%s\n", unitTemp.fileName);
            //printf("%d\t%d\n", myTable->inode_no, unitTemp.startBlock);
            totalBlocks += sum(myTable);
        }
    }
    return totalBlocks;
}


int changeName(char oldName[], char newName[])
{
    int unitIndex = findUnitInTable(currentDirTable, oldName);
    if(unitIndex == -1)
    {
        printf("No file with that name was found.\n");
        return -1;
    }
    strcpy(currentDirTable->inode_array[unitIndex].fileName, newName);
    return 0;
}


int createDataBlock(int dataBlock_no, int fileBlock_no, int fileSize)
{
    dataBlock_struct *currentDataBlock = (dataBlock_struct*) getBlockAddr(dataBlock_no);
    currentDataBlock->blockNum = fileBlock_no;
    currentDataBlock->fileSize = fileSize;
    currentDataBlock->link = 1;
    currentDataBlock->dataSize = 0;
    currentDataBlock->readptr = 0;
    return 0;
}

int addDirUnit(dirTable* myDirTable, char fileName[], int type, int dataBlock_no)
{
    int inode_no = myDirTable->inode_no;
    if(inode_no == dirTable_max_size)
    {
        printf("There are no more available inodes to allocate your file/directory, try to delete some files or directories to free some inodes.\n");
        return -1;
    }
    
    if(findUnitInTable(myDirTable, fileName) != -1)
    {
        printf("A file with this name already exists.\n");
        return -1;
    }
    inode* newDirUnit = &myDirTable->inode_array[inode_no];
    myDirTable->inode_no++;
    strcpy(newDirUnit->fileName, fileName);
    newDirUnit->type = type;
    newDirUnit->startBlock = dataBlock_no;
    char timeInfo[50];
    getTimeStamp(timeInfo);
    strcpy(newDirUnit->timeStamp, timeInfo);
    return 0;
}

int releaseFile(int dataBlock_no)
{
    dataBlock_struct* thisDataBlock = (dataBlock_struct*)getBlockAddr(dataBlock_no);
    thisDataBlock->link--;
    if(thisDataBlock->link == 0)
    {
        releaseBlock(thisDataBlock->blockNum, thisDataBlock->fileSize);
    }
    releaseBlock(dataBlock_no, 1);
    return 0;
}

int deleteDirUnit(dirTable* myDirTable, int unitIndex)
{
    int inode_no = myDirTable->inode_no;
    for(int i = unitIndex; i < inode_no-1; i++)
    {
        myDirTable->inode_array[i] = myDirTable->inode_array[i+1];
    }
    myDirTable->inode_no--;
    return 0;
}

int deleteFileInTable(dirTable* myDirTable, int unitIndex)
{
    inode myUnit = myDirTable->inode_array[unitIndex];
    if(myUnit.type == 0)
    {
        int dataBlock_no = myUnit.startBlock;
        dirTable* table = (dirTable*)getBlockAddr(dataBlock_no);
        printf("cycle delete dir %s\n", myUnit.fileName);
        int unitCount = table->inode_no;
        for(int i=1; i<unitCount; i++)
        {
            printf("delete %s\n", table->inode_array[i].fileName);
            deleteFileInTable(table, i);
        }
        releaseBlock(dataBlock_no, 1);
    }else {
        int dataBlock_no = myUnit.startBlock;
        releaseFile(dataBlock_no);
    }
    return 0;
}

int cat(char fileName[])
{
    int unitIndex = findUnitInTable(currentDirTable, fileName);
    if(unitIndex == -1)
    {
        printf("No file with this name was found.\n");
        return -1;
    }
    int dataBlock_no = currentDirTable->inode_array[unitIndex].startBlock;
    dataBlock_struct* thisDataBlock = (dataBlock_struct*)getBlockAddr(dataBlock_no);
    doCat(thisDataBlock);
    
    return 0;
}
int doCat(dataBlock_struct* thisDataBlock)
{
    int dataSize = thisDataBlock->dataSize;
    char* data = (char*)getBlockAddr(thisDataBlock->blockNum);
    for(thisDataBlock->readptr = 0; thisDataBlock->readptr < dataSize; thisDataBlock->readptr++)
    {
        printf("%c", *(data+thisDataBlock->readptr));
    }
    if(thisDataBlock->readptr == dataSize)
        cout << "#" ;
    cout << "\n";
    return 0;
}


int populateRandomStringToFile(char fileName[])
{
    int unitIndex = findUnitInTable(currentDirTable, fileName);
    int dataBlock_no = currentDirTable->inode_array[unitIndex].startBlock;
    dataBlock_struct* thisDataBlock = (dataBlock_struct*)getBlockAddr(dataBlock_no);
    int fileSize = thisDataBlock->fileSize;
    //Generate random string of char
    char content[(ADDRESS_LENGTH*8)*fileSize+1];
    string randomString;
    char charArray[(ADDRESS_LENGTH*8)*fileSize+1]; //multiply by 8 to make it into bit-size string
    static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < ADDRESS_LENGTH*8*fileSize; ++i) {
        charArray[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
        char randomChar = charArray[i];
        randomString += (randomChar);
    }
    strcpy(content, randomString.c_str());
    //Search for file
    if(unitIndex == -1)
    {
        printf("No file with this name was found.\n");
        return -1;
    }
    //Send string to file
    writeToFile(thisDataBlock, content);
    return 0;
}


int rewrite(char fileName[], char content[])
{
    int unitIndex = findUnitInTable(currentDirTable, fileName);
    if(unitIndex == -1)
    {
        printf("file no found\n");
        return -1;
    }
    int dataBlock_no = currentDirTable->inode_array[unitIndex].startBlock;
    dataBlock_struct* thisDataBlock = (dataBlock_struct*)getBlockAddr(dataBlock_no);
    thisDataBlock->dataSize = 0;
    thisDataBlock->readptr = 0;
    
    writeToFile(thisDataBlock, content);
    return 0;
}
int writeToFile(dataBlock_struct* thisDataBlock, char content[])
{
    int contentLength = strlen(content);
    int fileSize = thisDataBlock->fileSize * BLOCK_SIZE;
    char* data = (char*)getBlockAddr(thisDataBlock->blockNum);
    for(int i=0; i < contentLength && thisDataBlock->dataSize < fileSize; i++, thisDataBlock->dataSize++)
    {
        *(data+thisDataBlock->dataSize) = content[i];
    }
    if(thisDataBlock->dataSize == fileSize)
        printf("The file is full, can't write more to it.\n");
    return 0;
}

int findUnitInTable(dirTable* myDirTable, char unitName[])
{
    int inode_no = myDirTable->inode_no;
    int unitIndex = -1;
    for(int i = 0; i < inode_no; i++)
        if(strcmp(unitName, myDirTable->inode_array[i].fileName) == 0)
            unitIndex = i;
    return unitIndex;
}

int showRootSum()
{
    int totalBlocks = 0;
    int unitAmount = rootDirTable->inode_no;
    //printf("total:%d\n", unitAmount);
    //printf("name\ttype\tsize\tdataBlock_struct\tdataStartBlock\n");
    for (int i = 0; i < unitAmount; i++)
    {
        inode unitTemp = rootDirTable->inode_array[i];
        //printf("%s\t%d\t", unitTemp.fileName, unitTemp.type);
        if (unitTemp.type == 1)
        {
            int dataBlock_no = unitTemp.startBlock;
            dataBlock_struct* fileDataBlock = (dataBlock_struct*)getBlockAddr(dataBlock_no);
            //printf("%d\t%d\t%d\n", fileDataBlock->fileSize, dataBlock_no, fileDataBlock->blockNum);
            totalBlocks += fileDataBlock->fileSize;
        }
        else {
            int dirBlock = unitTemp.startBlock;
            dirTable* myTable = (dirTable*)getBlockAddr(dirBlock);
            //printf("%d\t%d\n", myTable->inode_no, unitTemp.startBlock);
            totalBlocks += sum(myTable);
        }
    }
    return totalBlocks;
}



//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// i - Node - Based Unix - Style File System
//
//  Created by MR.JON on 16/06/2020.
//  Copyright © All rights reserved 

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
