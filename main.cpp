// Brian Savage
// Gerp - Project 1: Part 2
// Nov. 29th, 2019
// main.cpp
// Purpose: main function for Gerp

#include <iostream>
#include <string>
#include <functional>
#include "library.h"
#include "FSTreeTraversal.h"
#include "stringProcessing.h"
#include "DirNode.h"
#include "FSTree.h"
#include "gerp.h"

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc == 3) {
        GerpSearch run(argv);
        run.startQuerying();
    } else {
        cerr << "Usage: gerp directory output_file" << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
