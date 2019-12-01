// Brian Savage
// Gerp - Project 1: Part 2
// Nov. 29th, 2019
// FSTreeTraversal.h
// Purpose: Definitions of Indexer Class

#include <iostream>
#include <string>
#include "DirNode.h"
#include "FSTree.h"
#include "library.h"

using namespace std;

class Indexer {
    public:
        Indexer(string start);
        string getStartingName();
        void printContents(FSTree traverse);
        void createDatabase(Library *data, FSTree origin);
    private:
        string startingDirectory;
        void printContents(FSTree traverse, DirNode *directoryNode, string location);
        void processDirectory(Library *data, DirNode *directory, string location);
        void processFile(Library *data, string filename, string location);
};
