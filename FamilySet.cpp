#include "FamilySet.h"
#include <fstream>
#include <vector>

FamilySet::FamilySet(string dictFile, int len) {
    //This constructor opens a file with the name dictFile
    // and pushes all words of the length len into the vector wordlist.
    // allocating the correct memory for the wordlist vector

    wordlist = new vector<string>; // 10? how much memory should be allocated?

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
}


void FamilySet::filterFamilies(string letter, string guessPattern) {
    char tempChar = letter[0];
    // iterate through all the words in wordlist
    for (auto it = wordlist->begin(); it != wordlist->end(); it++) {
        int count = std::count(it->begin(), it->end(), tempChar);
        if (count == 0) {
            // check if family already exists
            if (dictionaries.count(guessPattern) == 0) {
                vector<string>* v1 = new vector<string>;
                //auto v1 = new vector<string>;
                dictionaries.insert(pair<string, vector<string>*>(guessPattern, v1));
            }
            dictionaries[guessPattern]->push_back(*it);
        } else {
            string fam = guessPattern;
            int index = 0;
            // create appropriate family
            for (int i = 0; i < count; i++) {
                index = it->find(letter, index);
                //fam[index] = (char)letter;
                fam.replace(index, 1, letter); // change family[index] to correct letter
                index++; // start looking for the next occurrence of the letter by incrementing index
            }
            // if the family doesn't exist, create a new pair (family, vector<string>*) and put it into the map
            if (dictionaries.count(fam) == 0) {
                vector<string>* v1 = new vector<string>;
                //auto v1 = new vector<string>;
                dictionaries.insert(pair<string, vector<string>*>(fam, v1));
            }
            dictionaries[fam]->push_back(*it);
        }
    }

    int maxFamSize = 0;
    string maxFam;
    // ensure that the iterator starts at the beginning of the map
    resetFamilyIter();
    // find the largest family within the map
    string tempString = getNextFamily();
    while (tempString != "") {
        int tempMaxFamSize = familySize(tempString);
        if (tempMaxFamSize > maxFamSize) {
            maxFamSize = tempMaxFamSize;
            maxFam = tempString;
        }
        tempString = getNextFamily();
    }
    resetFamilyIter();
    setFamily(maxFam);
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
    for (auto it = dictionaries.begin(); it != dictionaries.end(); it++) {
        if ((it->first) == family) {
            return it->second->size();
        }
    }
//    resetFamilyIter();
//    while (getNextFamily() != "") {
//        if (getNextFamily() == family) {
//            // at this point, the iterator will be pointing to the correct family that user wants to check the size of
//            // return the number of words in the vector of this family by using "second" since you want to refer to the vector of the map
//            return famIter->second->size();
//        }
//    }
//    resetFamilyIter();
    // return -1 if the family does not exist
    return -1;
}

void FamilySet::resetFamilyIter() {
    famIter = dictionaries.begin();
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

