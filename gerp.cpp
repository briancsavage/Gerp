// Brian Savage
// Gerp - Project 1: Part 2
// Nov. 29th, 2019
// gerp.cpp
// Purpose: Implementation for GerpSearch Class

#include "gerp.h"
#include "DirNode.h"
#include "FSTree.h"
#include "FSTreeTraversal.h"
#include "stringProcessing.h"

using namespace std;

// GerpSearch::GerpSearch(const char * argv[])
// Parameters: command line arguments (index 1 and 2)
//    Returns: Nothing
//       Does: Parameterized Constructor for Gerp Class
GerpSearch::GerpSearch(const char * argv[])
{
    outputFile = argv[2];
    startDir = argv[1];
}

// void GerpSearch::startQuerying()
// Parameters: None
//    Returns: Nothing
//       Does: Initializes all classes required for to query the library
void GerpSearch::startQuerying()
{
    FSTree test(startDir);
    Indexer search(startDir);
    Library *store = new Library;
    search.createDatabase(store, test);
    runQuery(store);
    delete store;
}

// void GerpSearch::runQuery(Library *store)
// Parameter: [Library *store] - pointer to instance of library class that
//                               will be queried
//   Returns: Nothing
//      Does: Processes all user queries
//  Commands: @i or @insensitive-> insensitive search
//            @f -> change query destination File
//            @q or @quit -> ends querying
void GerpSearch::runQuery(Library *store)
{
    stringProcessing helper;
    string in = "", search = "";
    while (in != "@q" or in != "@quit") {
        cout << "Query? " ;
        cin >> in;
        if (in == "@q" or in == "@quit") {
            cout << endl;
            break;
        }
        if (in == "@i" or in == "@insensitive") {
            cin >> search;
            if (store->find(helper.stripNonAlphaNum(search), startDir, false, outputFile) == false)
                cout << "query Not Found." << endl;
            else
                cout << endl;
        } else if (in != "@f"){
            if (store->find(helper.stripNonAlphaNum(in), startDir, true, outputFile) == false)
                cout << "query Not Found. Try with @insensitive or @i." << endl;
            else
                cout << endl;
        }
        if (in == "@f") {
            cin >> search;
            outputFile = search;
            cout << endl;
        }
    }
    cout << "Goodbye! Thank you and have a nice day." << endl;
}
