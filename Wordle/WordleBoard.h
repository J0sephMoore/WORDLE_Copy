#pragma once

#include <SFML/Graphics.hpp>
#include "Letter.h"
#include <string>
#include <map>

class WordleBoard
{
public:

	// Creates a new game board
	WordleBoard();

	// Redraws the gameboard with the updated letter colors
	void UpdateDisplay();

	// Gets the next guessed word from the user
	std::string GetNextGuess();

	// Gets a different guess word from the user.
	// Use this when the user's previous guess was invalid.
	std::string GetDifferentGuess();

	// Mark the letter at position 'location' in the guessed word as wrong.
	void MarkGuessLetterWrong(int location);

	// Mark the letter at position 'location' in the guessed word as correct.
	void MarkGuessLetterCorrectPosition(int location);

	// Mark the letter at position 'location' in the guessed word as correct but wrong position.
	void MarkGuessLetterWrongPosition(int location);

	// Mark the keyboard letter as wrong
	void MarkAlphabetLetterWrong(char letter);

	// Mark the keyboard letter as correct
	void MarkAlphabetLetterCorrectPosition(char letter);

	// Mark the keyboard letter as correct but wrong position
	void MarkAlphabetLetterWrongPosition(char letter);

	// Returns the current status of the keyboard letter
	//
	// Possible values are
    //    Letter::UNUSED
    //    Letter::WRONG
    //    Letter::WRONG_LOCATION
    //    Letter::CORRECT_LOCATION
	//
	// Use this function to determine if a keyboard's letter should have
	// its status changed.
	Letter::Status GetLetterStatus(char letter);

	void DisplayMessage(std::string message);
	void GameWon(std::string message);
	void GameLost(std::string message);

private:
	std::string GetCurrentGuess();
	std::string InputGuess();
	void CheckMousePosition(sf::Vector2f mousePosition);
	void ProcessLetter(std::string letter);
	void ProcessBackspace();
	void ProcessEnter();
	void GameOver();

	sf::RenderWindow m_gameWindow;
	Letter m_letters[6][5];
	std::map<char,KeyboardLetter> m_choices;
	SpecialKey m_backspace;
	SpecialKey m_enter;
    sf::Text m_message;
    sf::Text m_endGameText;
	sf::Font m_gameWonFont;
	sf::Font m_gameLostFont;
	int m_currentRow = -1; // Set to -1 so the next one is 0
	int m_currentColumn = 0;
	bool m_stillThinking = true;
};

