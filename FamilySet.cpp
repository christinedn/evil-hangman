#include "FamilySet.h"
#include <fstream>

FamilySet::FamilySet(string dictFile, int len) {
    //This constructor opens a file with the name dictFile
    // and pushes all words of the length len into the vector wordlist.
    // allocating the correct memory for the wordlist vector
    wordlist = new vector<string>[10]; // 10? how much memory should be allocated?

    ifstream myFile;
    myFile.open("dictionary.txt");
    string inputWord;
    if (!myFile.is_open())
        throw "File failed to open";

    while (!myFile.eof()) {
        myFile >> inputWord;
        if (inputWord.length() == len) {
            wordlist->push_back(inputWord);
        }
    }

    myFile.close();

}

FamilySet::~FamilySet() {

}

void FamilySet::setFamily(string family) {
    // This function sets wordlist to the dictionary of the given family.
    // This function should also clear the dictionaries.

}


/*
 * 1. iterate through all the words in wordlist
 * 2.
 */
void FamilySet::filterFamilies(string letter, string guessPattern) {
    // cannot use index to access elements on the vector since the constructor has not correctly allocated memory for it?
    // maybe use an iterator?
    // iterate through all the words in wordlist
    for (int i = 0; i < wordlist->size(); i++) {
        // check if the word is part of a family
        // std::string::npos means it is the end of the string
        int index = wordlist->find(letter);
        if (index != std::string::npos) { // compare guessPattern and wordlist[i] as well?
            // this means that the letter exists in wordlist[i]
            dictionaries.insert(pair<string, vector<string>*) (""), nullptr);
        }



    }
}

string FamilySet::getRandomWord()
{
	int ind = rand() % wordlist->size();
	return wordlist->at(ind);
}

int FamilySet::numWords()
{
	return wordlist->size();
}

int FamilySet::numFamilies()
{
	return dictionaries.size();
}

vector<string> FamilySet::getWords() {
    return *wordlist;
}







int FamilySet::familySize(string family) {
    resetFamilyIter();
    while (getNextFamily() != "") {
        if (getNextFamily() == family) {
            // at this point, the iterator will be pointing to the correct family that user wants to check the size of
            // return the number of words in the vector of this family by using "second" since you want to refer to the vector of the map
            return famIter->second->size();
        }
    }
    resetFamilyIter();
    return -1;
}

void FamilySet::resetFamilyIter() {
    famIter = dictionaries.begin(); // ??
}

string FamilySet::getNextFamily() {
    // If there are no more families left in the iterator (the iterator is not at the end),
    // then this function should return the empty string.
    if (famIter == dictionaries.end()) {
        return "";
    }
    string currString = famIter->first;
    famIter++;
    return currString;
}

