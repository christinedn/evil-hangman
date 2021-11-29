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
    // If family is not in dictionary, then setFamily should do nothing.

    // ensure that the iterator starts at the very beginning
    resetFamilyIter();

    // this while loop will find the correct family
    while (getNextFamily() != family) {
        getNextFamily();
    }

    if (getNextFamily() == "") {
        // at this point, it means that the family was not found
        // do nothing, return
        return;
    }

    // at this point, the correct family has been found
    // reset the old wordlist, put all the words in this family into the new wordlist
    wordlist->clear();
    // iterate through vector within the family and add all the words into wordlist
    for (auto it = famIter->second->begin(); it != famIter->second->end(); it++) {
        // wordlist->push_back(it);
        wordlist->push_back(*it);
    }
    resetFamilyIter();
    dictionaries.clear();
//    resetFamilyIter();
//    // find the correct family
//    while (getNextFamily() != family) {
//        getNextFamily();
//        if (getNextFamily() == "") {
//            // at this point, it means that the family was not found
//            // do nothing, return
//            return;
//        }
//        if (getNextFamily() == family) {
//            // at this point, the correct family has been found
//            // insert all the correct words from wordlist to this family
//            // for example, if wordlist is ALLY BETA COOL DEAL ELSE FLEW GOOD HOPE IBEX
//            // possible families: ----, -E---, --E-, E--E, ---E (if user guessed E)
//            // compare family to the list of words in wordlist
//            for (int i = 0; i < wordlist->size(); i++) {
//                // compare each letter of wordlist[i] to family
//                for (int j = 0; j < wordlist[i].length(); j++) {
//                    if (wordlist[i][j] == family[j]) {
//                        famIter->second.push_back(wordlist[i]);
//                    }
//                }
//            }
//        }
//    }
//    resetFamilyIter();

}


/*
 * 1. iterate through all the words in wordlist
 * 2. see if wordlist[i] contains letter
 * 3. if it does, create appropriate family
 *      - find how many of letter exist in wordlist[i]
 *      - save the index at which it exists so you can create the appropriate family
 *
 */
void FamilySet::filterFamilies(string letter, string guessPattern) {
    // cannot use index to access elements on the vector since the constructor has not correctly allocated memory for it? double check constructor
    // maybe use an iterator instead of using index to access elements?
    // iterate through all the words in wordlist
    int famLength = guessPattern.length();
    string famString1;

    // create a family string of only hyphens to put all the words that do not contain letter
    for (int i = 0; i < famLength; i++) {
        famString1.append("-");
    }

    for (int i = 0; i < wordlist->size(); i++) {
        // find the number of times the letter occurs in the string
        int count = std::count(wordlist[i].begin(), wordlist[i].end(), letter);
        if (count == 0) {
            dictionaries.insert(pair<string, vector<string>*>(famString1, wordlist[i]));
        }
    }

    /*
     * // check if the word is part of a family
        // std::string::npos means it is the end of the string
        int index = wordlist->find(letter);
        if (index != std::string::npos) { // compare guessPattern and wordlist[i] as well?
            // this means that the letter exists in wordlist[i]
            dictionaries.insert(pair<string, vector<string>*) (""), nullptr);
        }
     */
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

