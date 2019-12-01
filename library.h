// Brian Savage
// Gerp - Project 1: Part 2
// Nov. 29th, 2019
// library.h
// Purpose: Library class definitions

#ifndef library_h
#define library_h

#include <stdio.h>
#include <vector>
#include <string>
#include <functional>
#include <cstring>
#include <climits>

using namespace std;

struct Location {
    string instance;
    unsigned int location;
    Location *next = nullptr;
};

struct Node {
    unsigned int hashValue;
    Location *list = nullptr;
    Location *lastInsert = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
};

class Library {
     public:
        Library();
        ~Library();
        void insert(string word, unsigned int location);
        Node *getRoot();
        bool find(string word, string startDir, bool ifSensitive, string printTo);
        int InsertLocation(string line);
    private:
        const static int SIZE_OF_LIBRARY = 10000; // Max number of storable nodes
        Node *root;
        vector<string> lineItems;
        unsigned int numLines;
        void burnTree(Node *node);
        void clearList(Location *list);
        void insert(Node *node, int hashRef, string word, unsigned int location);
        void addToList(Node *node, string word, unsigned int location);
        bool find(Node *node, int hashVal, bool ifSensitive, string word, string startDir, string printTo);
        bool findInList(Location *list, bool ifSensitive, string searching, string startDir, string printTo);
        Node *initialize(string word, unsigned int location);
        int getHash(string word);
        string lower(string word);
};


#endif /* library_h */
