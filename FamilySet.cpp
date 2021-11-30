#include "FamilySet.h"
#include <fstream>
#include <vector>
#include <iostream>

FamilySet::FamilySet(string dictFile, int len) {
    wordlist = new vector<string>; // how much memory should be allocated?

    // open file with name dictFile
    ifstream myFile;
    myFile.open(dictFile);
    string inputWord;

    if (!myFile.is_open())
        throw "File failed to open";

    // read from file and input all the words of length len into wordlist
    while (!myFile.eof()) {
        myFile >> inputWord;
        if (inputWord.length() == len) {
            wordlist->push_back(inputWord);
        }
    }

    myFile.close();

}

FamilySet::~FamilySet() {
    delete wordlist;
    // delete the vectors in dictionary since it was created using "new"
    for (auto it1 = dictionaries.begin(); it1 != dictionaries.end(); it1++) {
        string fam = it1->first;
        delete dictionaries[fam];
    }
}

void FamilySet::setFamily(string family) {
    // ensure that the iterator starts at the very beginning
    resetFamilyIter();

    // this while loop will find the correct family
    string currFamily = getNextFamily();
    while (currFamily != family) {
        currFamily = getNextFamily();
    }

    if (currFamily == "") {
        // at this point, it means that the family was not found
        // do nothing, return
        return;
    }

    // at this point, the correct family has been found
    // reset the old wordlist, put all the words in this family into the new wordlist
    wordlist->clear();
    // iterate through vector within the family and add all the words into wordlist
    for (auto it = dictionaries[currFamily]->begin(); it != dictionaries[currFamily]->end(); it++) {
        // wordlist->push_back(it);
        wordlist->push_back(*it);
    }
    resetFamilyIter();
    dictionaries.clear();
}


void FamilySet::filterFamilies(string letter, string guessPattern) {
    char tempChar = letter[0]; // convert letter to char
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

    // not sure if the code below is required?
//    int maxFamSize = 0;
//    string maxFam;
//    // ensure that the iterator starts at the beginning of the map
//    resetFamilyIter();
//    // find the largest family within the map
//    string currFamily = getNextFamily();
//    while (currFamily != "") {
//        int tempMaxFamSize = familySize(currFamily);
//        if (tempMaxFamSize > maxFamSize) {
//            maxFamSize = tempMaxFamSize;
//            maxFam = currFamily;
//        }
//        currFamily = getNextFamily();
//    }
//    resetFamilyIter();
    //setFamily(maxFam);
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
    // iterate through the keys in the dictionary to find the correct family
    for (auto it = dictionaries.begin(); it != dictionaries.end(); it++) {
        if ((it->first) == family) {
            return it->second->size();
        }
    }
    return -1;
}

void FamilySet::resetFamilyIter() {
    famIter = dictionaries.begin();
}

string FamilySet::getNextFamily() {
    // if there are no more families left to iterate over, return an empty string
    if (famIter == dictionaries.end()) {
        return "";
    }
    // return the current family that the famIter is pointing at
    string currString = famIter->first;
    famIter++;
    return currString;
}

void FamilySet::printDictionary() {
    for (auto it1 = dictionaries.begin(); it1 != dictionaries.end(); it1++) {
        cout << it1->first << "\t";
        string fam = it1->first;
        for (auto it2 = dictionaries[fam]->begin(); it2 != dictionaries[fam]->end(); it2++) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
}

