// Brian Savage
// Gerp - Project 1: Part 2
// Nov. 29th, 2019
// stringProcessing.cpp
// Purpose: Implementation for stringProcessing class

#include "stringProcessing.h"
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

// string stringProcessing::stripNonAlphaNum(string original)
// Parameters: [string original] - the original string that needs to be stripped on nonAlphaNumeric chars
//    Returns: the cleaned string without beginning and ending nonAlphaNumeric chars
//       Does: Cleans strings of beginning and ending nonAlphaNumeric chars
string stringProcessing::stripNonAlphaNum(string original)
{
    string cleaned = "";
    unsigned short start = 0, end = original.length();
    while (not isalnum(original[start]) and start != original.length())
        start++;
    while (not isalnum(original[end]) and end != start)
        end--;
    while (start <= end) {
        cleaned += original[start];
	    start++;
    }
    return cleaned;
}
