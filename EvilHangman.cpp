// EvilHangman2.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include "FamilySet.h"
//#include "TreeMap.h"
using namespace std;

bool debug;

bool PromptYesNoMessage(string msg) {
	while (true) {
		cout << msg << " (y/n) ";
		string response;
		cin >> response;
		if (response == "y")
			return true;
		if (response == "n")
			return false;
		cout << "Please enter y or n." << endl;
	}
}

// this function asks the user to enter the amount of guesses they would like
int PromptGuesses() 
{
	while (true) {
		int len;
		cout << "Please enter how many guesses: ";
		cin >> len;
		if (len > 0)
			return len;
	}
}

// this function asks the user to enter the length
int PromptWordLength()
{
    while (true) {
        int len;
        cout << "Please enter the word length: ";
        cin >> len;
        if (len > 0)
            return len;
    }
}

// this function asks user to enter a letter
// appends last guessed letters and returns guessed letters
string PromptGuess(string& guessedLetters)
{
    string guess = "", letter;
    // ask user to enter a letter
    cout << "Enter a letter: ";
    cin >> letter;

    // append the letter to guessedLetters
    guess += letter;
    return guess;
}

// this function finds the largest family
string ChooseFamily(string guess, string guessProgress, FamilySet& set) 
{
    // filter families by guess and guessProgress/guessPattern

    // put all the words in wordlist to the correct family in the map
    set.filterFamilies(guess, guessProgress);

    // find the maximum family
    string maxFamily;
    int maxFamSize = 0;

    // ensure that the iterator starts at the beginning of the map
    set.resetFamilyIter();

    // find the largest family within the map
    string currFamily = set.getNextFamily();
    while (currFamily != "") {
        int tempMaxFamSize = set.familySize(currFamily);
        if (tempMaxFamSize > maxFamSize) {
            maxFamSize = tempMaxFamSize;
            maxFamily = currFamily;
        }
        currFamily = set.getNextFamily();
    }
    set.resetFamilyIter();

    return maxFamily;
}

bool isWin(string guessedProgress)
{
    // attempts to find * in the guessProgress. if no * is found, that means that the entire word has been guessed
	return guessedProgress.find('*') == string::npos;
}

void PlayEvilHangman(string file) 
{
    int len, guessesLeft;
    string maxFam, letter;

    string guessProgress = ""; // aka guessPattern      // correctly guessed positions
    string guessedLetters = "";     // letters already guessed by user

    // Prompt user for word length and number of guesses
    len = PromptWordLength();
    guessesLeft = PromptGuesses();

    // Load dictionary based on word length
    cout << "Loading dictionary..." << endl;
    FamilySet families(file, len);

    // Show *'s for the guessProgress at the beginning
    for (int i = 0; i < len; i++)
        guessProgress += "*";

	// Actual game loop...
	while (true) {
		cout << endl << endl;
		cout << guessProgress << endl;
		cout << "Guesses Left: " << guessesLeft << endl;
		cout << "Guessed Letters: " << guessedLetters << endl;

        guessedLetters = PromptGuess(guessedLetters);

        char tempLastGuessedLetter = guessedLetters[guessedLetters.size()-1];
        string lastGuessedLetter(1, tempLastGuessedLetter);

		// filters the families and returns the largest family
        maxFam = ChooseFamily(lastGuessedLetter, guessProgress, families);

        //families.printDictionary();

        // compare maxFam to guessPattern. check if guessed letter exist in maxFam. if so, that means that the user has guessed correct letter(s)
        char tempChar = lastGuessedLetter[0];
        int count = std::count(maxFam.begin(), maxFam.end(), tempChar);
        if (count != 0) {
            int index = 0;
            // change the guessProgress to the letters in the correct positions
            for (int i = 0; i < count; i++) {
                index = maxFam.find(tempChar, index);
                guessProgress[index] = tempChar;
                //guessProgress.replace(index, 1, tempChar); // change guessProgress[index] to correct letter
                index++; // find all instances of which the letter occurs in max family by incrementing index and starting from that index in the next iteration
            }
        }

        // reduces the wordlist.
		families.setFamily(maxFam);
		// at this point, all the words in the current wordlist can be a possible answer

		// decrement guesses left
		--guessesLeft;

		//cout << "current guessPattern: " << guessProgress << endl;

		if (isWin(guessProgress)) {
			cout << endl << "Wow! You won!" << endl;
			return;
		}

		if (guessesLeft <= 0) {
			cout << "Wow... you are a really bad guesser..." << endl;
			cout << "The mystery word was " << families.getRandomWord() << endl;
			return;
		}
	}
}

int main()
{
    string file;
    //cout << "Enter file: ";
    //cin >> file;				// Can comment out this line and include the following while developing
    file = "dictionary.txt";  // Convenient to hard code while developing

    //PlayEvilHangman(file);
	
	while (true) {
		debug = PromptYesNoMessage("Turn debugging on?");
		PlayEvilHangman(file);
		if (!PromptYesNoMessage("Would you like to play again? "))
			break;
	}
}

