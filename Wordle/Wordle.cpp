#include "WordleBoard.h"
#include <string>
#include <time.h>
#include <fstream>
#include <iostream>

using namespace std;

bool ValidWordOrNot(string guess);

string dictionary[3324];

// Create the Wordle board
WordleBoard wordleBoard;

int main()
{
    int guessesCount = 0;
    bool success = false;

    srand((int)time(nullptr));



    fstream file;
    file.open("Wordle-Words.txt"); // Open a file for reading
    if (!file.good())
    {
        cout << "Error opening file." << endl;
        return 1;
    }
    else if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            static int i = 0;
            dictionary[i] = line;
            ++i;
        }
    }

    int entry = rand() % 3324;

    string magicWord = dictionary[entry];
    
    while (guessesCount < 6 || !success) {

        // Display the empty board
        wordleBoard.UpdateDisplay();

        // Get a new 5-letter word from the user
        string guess = wordleBoard.GetNextGuess();

        // Display a message, e.g., if the word was invalid
        // Example: Get a different word from the user, e.g., if
        while (!ValidWordOrNot(guess)) {
            wordleBoard.DisplayMessage("dumbo");
            guess = wordleBoard.GetDifferentGuess();
        }

        if (ValidWordOrNot(guess)) {//maybe unnecessary because the dumbo loop
            guessesCount++;
        }

        bool checkedMagic[5]{ 0, 0, 0, 0, 0};
        bool checkedGuess[5]{ 0, 0, 0, 0, 0 };
        //green
        for (int i = 0; i < 5; ++i) {
            if (magicWord[i] == guess[i]) {
                // Mark as correct
                wordleBoard.MarkGuessLetterCorrectPosition(i);
                // Mark the keyboard letter as correct
                wordleBoard.MarkAlphabetLetterCorrectPosition(guess[i]);
                checkedMagic[i] = 1;
                checkedGuess[i] = 1;
            }
            
        }

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (i != j && magicWord[j] == guess[i] && !checkedMagic[j] && !checkedGuess[i]) {
                    // Mark as correct but in the wrong position
                    wordleBoard.MarkGuessLetterWrongPosition(i);
                    // Mark the keyboard letter as correct but in the wrong position
                    wordleBoard.MarkAlphabetLetterWrongPosition(guess[i]);
                    checkedGuess[i] = 1;
                    checkedMagic[j] = 1;
                }
            }
        }

        for (int i = 0; i < 5; ++i) {
            if (!checkedGuess[i]) {
                // Mark as incorrect
                wordleBoard.MarkGuessLetterWrong(i);
                // Mark the keyboard letter as wrong
                wordleBoard.MarkAlphabetLetterWrong(guess[i]);
            }
        }

        // Update the display before continuing
        wordleBoard.UpdateDisplay();

        if (magicWord == guess) {
            success = true;
        }
    }
    
    while (guessesCount == 6 || success) {
        wordleBoard.DisplayMessage("press space to do again");
    }

    return EXIT_SUCCESS;

    return 0;
}

bool ValidWordOrNot(string guess)
{
    for (int i = 0; i < 3324; ++i) {
        if (guess == dictionary[i]) {
            return true;
        }
    }

    return false;
}
