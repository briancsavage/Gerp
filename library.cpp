// Brian Savage
// Gerp - Project 1: Part 2
// Nov. 29th, 2019
// library.cpp
// Purpose: Implementation for Library Class

#include "library.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

// Library::Library()
// Parameters: None
//    Returns: Nothing
//       Does: Constructor for the Library Class
Library::Library()
{
    root = nullptr;
    numLines = -1;
    lineItems.clear();
}

// Library::~Library()
// Parameters: None
//    Returns: Nothing
//       Does: Destructor for the Library Class
Library::~Library()
{
    if (root != nullptr) {
        burnTree(root->left);
        burnTree(root->right);
        clearList(root->list);
        delete root;
        root = nullptr;
    }
}

// void Library::burnTree(Node *node)
// Parameters: [Node *node] - pointer to a Node within the library BST
//    Returns: Nothing
//       Does: Deletes all memory allocated by the Node and then recursively 
//             deletes all child nodes
void Library::burnTree(Node *node)
{
    if (node != nullptr) {
        burnTree(node->left);
        burnTree(node->right);
        clearList(node->list);
        delete node;
        node = nullptr;
    }
}

// void Library::clearList(Location *list)
// Parameters: [Location *list] - pointer to the Location list of a node
//    Returns: Nothing
//       Does: Deletes all memory allocated by the linked list of locations 
//             contained within each node
void Library::clearList(Location *list)
{
    while (list != nullptr) {
        Location *prev = list;
        list = list->next;
        delete prev;
        prev = nullptr;
    }
}

// void Library::insert(string word, unsigned int location)
// Parameters: [string word] - string for the word to be inserted into the tree
//             [unsigned int location] - unsigned int representing the index 
//                                       position of the line the word came 
//                                       from inside the vector for all lines 
//                                       name lineItems
//    Returns: Nothing
//       Does: Inserts new word into BST
void Library::insert(string word, unsigned int location)
{
    if (root == nullptr)
        root = initialize(word, location);
    else
        insert(root, getHash(word), word, location);
}

// int Library::InsertLocation(string line)
// Parameters: [string line] - string representing the line to be inserted 
//                             into the lineItems vector
//    Returns: integer representing the index position of the line inserted 
//             into the lineItems vector
//       Does: Inserts line into the line items vector and returns the index 
//             of the line inserted
int Library::InsertLocation(string line)
{
    numLines++;
    lineItems.push_back(line);
    return numLines;
}

// void Library::insert(Node *node, int hashRef, string word, 
//                      unsigned int location)
// Parameters: [Node *node] - pointer to the current node in the BST being 
//                            traversed
//             [int hashRef] - integer for the hashVal of the word being 
//                             inserted
//             [string word] - string word representing the word being inserted
//             [unsigned int location] - unsigned int representing the location
//                                       of line within the lineItems vector
//    Returns: Nothing
//       Does: Inserts word into the BST or into the location list at the Node
//             if the hash values match
void Library::insert(Node *node, int hashRef, string word, 
		     unsigned int location)
{
    if (hashRef == node->hashValue) {
        addToList(node, word, location);
        return;
    }
    if (node != nullptr) {
        if (hashRef > node->hashValue) {
            if (node->right == nullptr) {
	            node->right = initialize(word, location);
            } else {
	            insert(node->right, hashRef, word, location);
            }
        } else {
            if (node->left == nullptr) {
	            node->left = initialize(word, location);
            } else {
	            insert(node->left, hashRef, word, location);
            }
        }
    }
}

// void Library::addToList(Node *node, string word, unsigned int location)
// Parameters: [Node *node] - pointer to the node that's list is being added to
//             [string word] - string representing the word being initialized 
//                             into the list
//             [unsigned int location] - index for line the word came from 
//                                       inside the lineItems vector
//    Returns: Nothing
//       Does: adds word to the linked list of locations
void Library::addToList(Node *node, string word, unsigned int location)
{
    if (node->lastInsert->next == nullptr) {
        node->lastInsert->next = new Location;
        node->lastInsert->next->instance = word;
        node->lastInsert->next->location = location;
        node->lastInsert->next->next = nullptr;
        node->lastInsert = node->lastInsert->next;
    } else {
        cout << "ERROR: LastInsert Not Null Unable to add to Node list." 
	     << endl;
    }
}

// Node *Library::initialize(string word, unsigned int location)
// Parameters: [string word] - string representing the word being initialized 
//                             into the BST
//             [unsigned int location] - unsigned int representing the index of
//                                       the line the word came from inside the
//                                       lineItems vector
//    Returns: pointer to the Node being initialized
//       Does: Initializes Node of BST
Node *Library::initialize(string word, unsigned int location)
{
    Node *setThis = new Node;
    setThis->list = new Location;
    setThis->hashValue = getHash(word);
    setThis->list->instance = word;
    setThis->list->location = location;
    setThis->list->next = nullptr;
    setThis->lastInsert = setThis->list;
    setThis->left = nullptr;
    setThis->right = nullptr;
    return setThis;
}

// bool Library::find(string word, string startDir, bool ifSensitive, 
//                    string printTo)
// Parameters: [string word] - string representing the word being search in 
//                             the tree
//             [string startDir] - string representing the starting directory 
//                                 of the index
//             [bool ifSensitive] - true if sensitive, false if not sensitive 
//                                  search
//    Returns: True if search returns anything, false if search finds no match
//       Does: Searches BST and linked lists for instances of the word being 
//             searched for
bool Library::find(string word, string startDir, bool ifSensitive, 
		   string printTo)
{
    return find(root, getHash(word), ifSensitive,  word, startDir, printTo);
}

// bool Library::find(Node *node, int hashVal, bool ifSensitive, string word, 
//                    string startDir, string printTo)
// Parameters: [Node *node] - pointer to the current node during the search 
//                            process
//             [int hashVal] - integer representing the hashVal of the word 
//                             being searched for
//             [bool ifSensitive] - true if sensitive, false if not sensitive 
//                                  search
//             [string word] - word being searched for
//             [string startDir] - name of the starting directory
//             [string printTo] - name of the file the results of the query 
//                                will be printed to
//    Returns: True if search returns anything, false if search finds no match
//       Does: Looks through BST and linked lists for instances of the word 
//             being searched for
bool Library::find(Node *node, int hashVal, bool ifSensitive, string word, 
		   string startDir, string printTo)
{
    bool found = false;
    if (node != nullptr) {
        if (node->hashValue == hashVal) {
            if (findInList(node->list, ifSensitive, word, startDir, printTo) 
		== true)
                return true;
            else
                return false;
        } else {
            found = find(node->left, hashVal, ifSensitive, word, startDir, 
			 printTo);
            if (found == false)
                found = find(node->right, hashVal, ifSensitive, word, startDir,
			     printTo);
            return found;
        }
    }
    return false;
}

// bool Library::findInList(Location *list, bool ifSensitive, string searching,
//                          string startDir, string printTo)
// Parameters: [Location *list] - pointer to the start of the linked list of 
//                                locations being searched
//             [bool ifSensitive] - true if sensitive, false if not sensitive 
//                                  search
//             [string searching] - string representing the word being searched
//                                  for
//             [string startDir] - string representing the file pathway that 
//                                 produced this word
//             [string printTo] - name of the file to be printed to
//    Returns: True if a match is found within the list, false if no match is 
//             found
//       Does: Searches linked list of locations for instance of word being 
//             searched for
bool Library::findInList(Location *list, bool ifSensitive, string searching, 
			 string startDir, string printTo)
{
    ofstream output;
    output.open(printTo, ios::app);
    if (output.is_open()) {
        Location *index = list;
        bool somethingFound = false;
        while (index != nullptr) {
            if (ifSensitive == true) {
                if (index->instance == searching) {
                    output << startDir << lineItems[index->location] << endl;
                    somethingFound = true;
                }
            } else {
                if (lower(index->instance) == lower(searching)) {
                    output << startDir << lineItems[index->location] << endl;
                    somethingFound = true;
                }
            }
            index = index->next;
        }
        output.close();
        return somethingFound;
    } else {
        cerr << "Error Opening File" << endl;
        exit(EXIT_FAILURE);
    }
    return false;
}

// int Library::getHash(string word)
// Parameters: [string word] - string representing the word to be hashed
//    Returns: integer for the hash value the word produced
//       Does: gets the hash value of the word (already lowered)
int Library::getHash(string word)
{
    return hash<string>{}(lower(word)) % SIZE_OF_LIBRARY;
}

// string Library::lower(string word)
// Parameters: [string word] - string that will be entirely lowered in 
//                             capitalization
//    Returns: the lowercased string
//       Does: lowers the case of a string
string Library::lower(string word)
{
    string lowerCase = "";
    for (int i = 0; i < word.length(); i++)
        lowerCase += tolower(word[i]);
    return lowerCase;
}

// Node *Library::getRoot()
// Parameters: None
//    Returns: pointer to the root of the tree
//       Does: gets the root of the word library
Node *Library::getRoot()
{
    return root;
}
