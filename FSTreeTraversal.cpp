// Brian Savage
// Gerp - Project 1: Part 2
// Nov. 29th, 2019
// FSTreeTraversal.cpp
// Purpose: Implementation for Indexer Class

#include "FSTreeTraversal.h"
#include "stringProcessing.h"
#include <fstream>
#include <sstream>

using namespace std;

// Indexer::Indexer(string start)
// Parameters: [string start] - the starting directory
//    Returns: Nothing
//       Does: Parameterized constructor for Indexer Class
Indexer::Indexer(string start)
{
    startingDirectory = "";
}

// void Indexer::printContents(FSTree origin)
// Parameters: [FSTree origin] - FSTree with the root as the origin directory
//    Returns: Nothing
//       Does: Prints the Contents of the FSTree
void Indexer::printContents(FSTree origin)
{
    printContents(origin, origin.getRoot(), "");
}

// void Indexer::printContents(FSTree traverse, DirNode *directoryNode, 
//                             string location)
// Parameters: [FSTree traverse] - FSTree with the root as the origin directory
//             [DirNode *directoryNode] - a pointer to a directory node within 
//                                        the FSTree
//             [string location] - the name of the starting directory
//    Returns: Nothing
//       Does: Prints the Contents of the FSTree
void Indexer::printContents(FSTree traverse, DirNode *directoryNode, 
			    string location)
{
    location = location + directoryNode->getName() + "/";
    if (not directoryNode->isEmpty()) {
        if (directoryNode->hasFiles()) {
            for (int i = 0; i < directoryNode->numFiles(); i++)
                cout << location << directoryNode->getFile(i) << endl;
        }
        if (directoryNode->hasSubDir()) {
            for (int i = 0; i < directoryNode->numSubDirs(); i++)
                printContents(traverse, directoryNode->getSubDir(i), location);
        }
    }
}

// void Indexer::createDatabase(Library *data, FSTree origin)
// Parameters: [Library *data] - pointer to instance of library Class
//             [FSTree origin] - instance of FSTree class
//    Returns: Nothing
//       Does: Creates the database of words through calling processFile and processDirectory functions
void Indexer::createDatabase(Library *data, FSTree origin)
{
    startingDirectory = origin.getRoot()->getName();
    string location = "/";
    if (not origin.getRoot()->isEmpty()) {
        if (origin.getRoot()->hasFiles()) {
            for (int i = 0; i < origin.getRoot()->numFiles(); i++)
                processFile(data, origin.getRoot()->getFile(i), location);
        }
        if (origin.getRoot()->hasSubDir()) {
            for (int i = 0; i < origin.getRoot()->numSubDirs(); i++)
                processDirectory(data, origin.getRoot()->getSubDir(i), 
				 location);
        }
    }
}

// void Indexer::processDirectory(Library *data, DirNode *directory, 
//                                string location)
// Parameters: [Library *data] - pointer to instance of library Class
//             [DirNode *directory] - pointer to instance of DirNode
//             [string location] - current string containing the location of 
//                                 the directory with respect to the origin 
//                                 directory
//    Returns: Nothing
//       Does: Processes Directory, calls process file for each file within 
//            the directory, and called processDirectory for all subdirectories
//            within the file
void Indexer::processDirectory(Library *data, DirNode *directory, 
			       string location)
{
    string newlocation = location + directory->getName() + "/";
    if (not directory->isEmpty()) {
        if (directory->hasFiles()) {
            for (int i = 0; i < directory->numFiles(); i++)
                processFile(data, directory->getFile(i), newlocation);
        }
        if (directory->hasSubDir()) {
            for (int i = 0; i < directory->numSubDirs(); i++)
                processDirectory(data, directory->getSubDir(i), newlocation);
        }
    }
}

// void Indexer::processFile(Library *data, string filename, string location)
// Parameters: [Library *data] - pointer to an instance of the library class
//             [string filename] - name of the file being processed
//             [string location] - current string containing the location of 
//                                 the directory with respect to the origin 
//                                 directory
//    Returns: Nothing
//       Does: Processes each word within the file until the end of the file is
//             reached
void Indexer::processFile(Library *data, string filename, string location)
{
    stringProcessing clean;
    location = location + filename;
    ifstream in(startingDirectory + location);
    if (in.is_open()) {
        string newLine, newWord;
        int i = 1;
        vector<string> insertedAlready;
        while (getline(in, newLine)) {
            istringstream read;
            read.str(newLine);
            unsigned int position = data->InsertLocation(location + ":" + 
							 to_string(i) + ": " +
							 newLine);
            insertedAlready.clear();
            bool alreadyInLine;
            while (read >> newWord) {
                newWord = clean.stripNonAlphaNum(newWord);
                alreadyInLine = false;
                for (unsigned int i = 0; i < insertedAlready.size(); i++) {
                    if (insertedAlready[i] == newWord)
                        alreadyInLine = true;
                }
                if (alreadyInLine == false) {
                    insertedAlready.push_back(newWord);
                    data->insert(newWord, position);
                }
            }
            i++;
        }
        in.close();
    } else {
        cerr << "***** Error Opening File *****" << endl;
    }
}

// string Indexer::getStartingName() {
// Parameters: None
//    Returns: string representing the name of the starting directory
//       Does: gets the starting directories name
string Indexer::getStartingName() 
{
    return startingDirectory;
}
