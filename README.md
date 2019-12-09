Brian Savage
Nov. 29th, 2019
Comp 15
Gerp Project 2: Part 2


[Purpose of the Project]
     The purpose of the assignment was to implement a version of the Linux 
     command Grep that provides a search of a directory and all subdirectories
     and files for a search query. Our version, named Gerp, does the same and 
     provides insensitve queries with (@i or @insensitive), @f will change the
     destination of the query results, and @q will quit and close the Gerp
     program.

[List of Provided Files]
   - main.cpp - contains the main function for the Gerp Program
   - gerp.h - contains the function definitions for the GerpSearch class
   - gerp.cpp - contains the implementation for the GerpSearch class
   - library.h - contains the function definitions for the GerpSearch class
   - library.cpp - contains the implementation for the GerpSearch class
   - FSTreeTraversal.h - contains the function definitions for the Indexer
     		         class
   - FSTreeTraversal.cpp - contains the implementation for the Indexer class
   - stringProcessing.h - contains the function defintions for the string
     			  Processing class
   - stringProcessing.cpp - contains the implementation for the Indexer class
   - DirNode.h - contains the function definitions for the DirNode class
   - DirNode.o - object file for the DirNode class
   - FSTree.h - contains the function definitions for the FSTree class
   - FSTree.o - object file for the FSTree class
   - Makefile - used to clean and compile Gerp program
   - README - all information pertaining to the Gerp program

[How to Compile and Run Program]
   - "make clean" - removes the object files for the Gerp program
   - "make gerp" - compile all required classes and object files to get the 
     	   	   gerp executable
   - Command to Run Gerp - 
     ./gerp [DirectoryToIndex] [QueryDestinationFile]
   - Commands to Run Search - 
     [Query?] [Not Necessary but @ commands below] [Word to Be Searched]
     "@i" or "@insensitive" --> make the search query insensitive
     "@f" --> changes the destination of the query results
     "@q" or "@quit" --> quits the gerp search program

[Architectural Overview of Classes]
   - main function - contains an instance of the GerpSearch class
   - GerpSearch class - contains instances of the stringProcessing class, the
     		      	FSTree class, the Indexer class, and a pointer to the
			Library class. The stringProcessing class clears the
			nonAlphaNumeric characters from the search queries. The
			FSTree class is passed to the Indexer class to provide
			a directory to be indexed. The Indexer class creates 
			the database of words that can be queried. The library
			class is also passed to the indexer class to be the 
			location of the words that will be stored.
   - FSTreeTraversal class - The FSTreeTraversal class contains instances of
     		     	     the FSTree class, a pointer to an instance of the 
			     library class, and an instance of the 
			     stringProcessing class. The instance of the 
			     FSTree class is used by the FSTreeTraversal class
			     to index the directory and file tree and process
			     all words contained within the files that will be
			     accessed through the pointer to the library 
			     class. 

[Outline of Data Structures and Algorithms]
   - Library Class Data Structures -
     The library class contains a pointer to the root of a binary search tree.
     This binary tree is comprised on nodes. The maximum occupancy of the tree
     is represented by the constant static integer named SIZE_OF_LIBRARY. In
     my implementation, I set the size of the library at 10,000 node to make
     the insertions quicker and prevent alot of indexing by the tree. Inside 
     each node, there is an unsigned integer for the hash value of that node,
     a linked list of location structs, a pointer to the last location inserted
     into the linked list, and two pointers to the left and right children of
     the node. Inside the location struct there is a string representing the
     instance of the word that was inserted into the tree, an unsigned integer
     representing the index position of the line that word originated from
     inside the lineItems vector, and a pointer to the next location struct 
     within the list. Additionally, within the library class there is a vector
     of lines collected from the FSTreeTraversal class while creating the 
     database of words. These lines contain the full pathway from the original
     directory, the line number within the file the line was collected from, 
     and the line containing the original word inserted. This prevents
     repetative storing of lines by using the same index for all words coming
     from the same line. Additionally, during the creating of the database, 
     a check is performed to prevent multiple insertions of the same string
     on the same line. This prevents duplicate printing during the querying.
[Methods for Testing Gerp]   
   - Testing FSTreeTraversal -
     The primary testing that I performed for the FSTreeTraversal class is by
     printing the list of all directories and files contains from the root
     directory. This confirms that all files that need to be inserted are 
     reached.
   - Testing stringProcessing -
     The primary testing I performed for the stringProcessing class is by 
     adding a testing main to the stringProcessing.cpp file and testing many
     different potential cases that could occur during the insertion process
     like only a single alpha numeric character, a string without alpha 
     numeric characters, a string that is boardered by alpha numeric chars and
     that's inside is only non alpha numeric characters, alternating alpha
     numeric and non alpha numeric characters, and a variety of other random
     orientations of characters. 
   - Testing Library - 
     The main testing I performed for the library class was to make sure all
     nodes and locations were inserted properly by printing each insertion,
     the hash value produced by the words inserted, the index position of
     the line within the lineItems vector, and the string at that index within
     the line items vector. Once all of these matched up, I knew the
     data stored during the insertion was correct. I used the small_test
     directory for this process because it was easy to check that all words
     within each file were inserted and recorded properly. Additionally, I used
     the print function within homework 4 to make sure the binary search tree
     is relatively balanced, which this test showed it is.
   - Testing GerpSearch - 
     The main method I used to test the GerpSearch class was using the
     reference implementation. I did this about 10 different times using a
     variety of different lists of search queries that were mixed with 
     sensitive and insensitive searches. Once the list of searches was run on
     my implementation, I would then run the same list of queries on the 
     reference implementation. I would then sort both files and compare the
     results using the diff linux command. Once all 10 different list of 
     queries yielded the same results, I was confident the results of the 
     queries were correct and the GerpSearch class and library search functions
     were running as intended.
   - Testing using Valgrind - 
     The final test I performed was running valgrind on processing the large
     gutenberg library. This took about 20 minutes to run, but it showed that
     there was no errors or memory leaks during the initialization of the tree,
     querying the tree, or deallocating all memory within the tree. 
   - Unit Testing -
     Finally, while creating my gerp implementation, I would conduct unit 
     testing of each function to make sure the basis of the gerp 
     implementation was functioning properly. 
