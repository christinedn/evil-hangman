#pragma once

#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

class FamilySet
{
public:
    /*
     * Function: Constructor that takes in a file name and length
     * Precondition: None
     * Postcondition: A FamilySet object will be created
     */
    FamilySet(string dictFile, int len);
    /*
     * Function: Destructor that deletes the wordlist and dictionary map within the class
     * Precondition: None
     * Postcondition: The wordlist and dictionary will be deleted
     */
	~FamilySet();
	/*
    * Function: Pushes all the words of wordlist into the correct family
    * Precondition: None
    * Postcondition: All the words in wordlist will be in the correct family in the dictionary
    */
	void filterFamilies(string letter, string guessPattern);
	/*
    * Function: Reduces the wordlist to the words of the largest family
    * Precondition: The family must exist
    * Postcondition: The wordlist will be reduced to the words of the largest family. Dictionary will be cleared
    */
	void setFamily(string family);
	/*
    * Function: Returns a random word from the wordlist
    * Precondition: None
    * Postcondition: A random word from wordlist will be returned
    */
	string getRandomWord();
	/*
    * Function: Returns the wordlist vector
    * Precondition: None
    * Postcondition: The wordlist vector will be returned
    */
	vector<string> getWords();
	/*
    * Function: Returns the number of words in wordlist
    * Precondition: None
    * Postcondition: The number of words in wordlist will be returned
    */
	int numWords();
	/*
    * Function: Returns the number of families in the dictionary
    * Precondition: None
    * Postcondition: The number of families in the dictionary will be returned
    */
	int numFamilies();
	/*
    * Function: Returns the number of words in any given family
    * Precondition: None
    * Postcondition: The number of words in the family will be returned
    */
	int familySize(string family);

	// Iterator
	/*
    * Function: Resets the iterator
    * Precondition: None
    * Postcondition: The iterator will be set to the beginning of the dictionary
    */
	void resetFamilyIter();
	/*
    * Function: Gets the next family
    * Precondition: None
    * Postcondition: The next family will be returned
    */
	string getNextFamily();
	/*
    * Function: Tester function that prints the dictionary
    * Precondition: None
    * Postcondition: The dictionary will be printed
    */
	void printDictionary();
	
private:
    	// This stores all words currently "valid"
	vector<string>* wordlist;
	unordered_map<string, vector<string>*> dictionaries;

	// Used for Iterator.  The const_iterator is the same as an iterator
	// but used for situations where you want to prevent changes to the data.
	unordered_map<string, vector<string>*>::const_iterator famIter;
};

