// Brian Savage
// Gerp - Project 1: Part 2
// Nov. 29th, 2019
// gerp.h
// Purpose: Definitions for GerpSearch Class


#include <iostream>
#include "DirNode.h"
#include "FSTree.h"
#include "Search.h"
#include "library.h"

using namespace std;

class GerpSearch {
    public:
        GerpSearch(const char * argv[]);
        void startQuerying();
    private:
        string outputFile;
        string startDir;
        void runQuery(Library *store);
};
