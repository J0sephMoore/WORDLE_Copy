#include "WordleBoard.h"
#include "Letter.h"
#include <string>

using namespace std;

WordleBoard::WordleBoard()
{
	// Define and create the game window
	int windowWidth = 300;
	int windowHeight = 500;
	m_gameWindow.create(sf::VideoMode( windowWidth, windowHeight, 32), "Wordle", sf::Style::Titlebar | sf::Style::Close);
	m_gameWindow.setVerticalSyncEnabled(true);

    // Create the board letter boxes
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
			m_letters[i][j].SetPosition(5.f + j * 60.f, 5.f + i*60.f);
		}
    }

	m_message.setFont(*Letter::GetFont());
    m_message.setFillColor(sf::Color::White);
    m_message.setLineSpacing(0.f);
    m_message.setCharacterSize(15);
	m_message.setPosition(4.f, 360.f);

	m_gameLostFont.loadFromFile("c:\\windows\\Fonts\\SNAP____.TTF");
	m_gameWonFont.loadFromFile("c:\\Windows\\Fonts\\BROADW.TTF");
	m_endGameText.setPosition(150.f, 150.f);
	m_endGameText.setCharacterSize(35.f);

    // Initialize the keyboard letters
	const char* alphabet = "QWERTYUIOPASDFGHJKLZXCVBNM";
	float firstRow = 390.f;
	float keySpace = 30.f;
    for (int i = 0; i < 26; ++i)
    {
		m_choices[alphabet[i]].SetLabel(string(1,alphabet[i]));
        if (i < 10)
        {
            m_choices[alphabet[i]].SetPosition(4.f + i * keySpace, firstRow);
        }
        else if (i<19)
        {
            m_choices[alphabet[i]].SetPosition(19.f + (i-10) * keySpace, firstRow + keySpace);
        }
        else
        {
            m_choices[alphabet[i]].SetPosition(49.f + (i-19) * keySpace, firstRow + 2* keySpace);
        }
    }
	m_enter.SetPosition(4.f,firstRow + 2* keySpace);
	m_enter.SetLabel("ENTER");
	m_backspace.SetLabel("BCKSP");
	m_backspace.SetPosition(49.f+7*keySpace,firstRow + 2* keySpace);
}

void WordleBoard::UpdateDisplay()
{
	// Clear the window
	m_gameWindow.clear(sf::Color(20, 10, 50));

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
			m_letters[i][j].Draw( m_gameWindow );
		}
    }

	for (auto choice : m_choices)
	{
		choice.second.Draw(m_gameWindow);
    }

	m_backspace.Draw(m_gameWindow);
	m_enter.Draw(m_gameWindow);

	m_gameWindow.draw(m_message);

	if (m_endGameText.getString() != "")
	{
		//center text
		sf::FloatRect textRect = m_endGameText.getLocalBounds();
		m_endGameText.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);

		// Save the current color
		sf::Color color = m_endGameText.getFillColor();

		// Add a black drop shadow
		m_endGameText.setFillColor(sf::Color::Black);
		m_gameWindow.draw(m_endGameText);

		// Reset the color and add the message
		m_endGameText.setFillColor(color);
		m_endGameText.move(-1.f, -1.f);
		m_gameWindow.draw(m_endGameText);
	}


	// Display the objects on the screen
	m_gameWindow.display();
}

string WordleBoard::GetDifferentGuess()
{
	m_currentColumn = 5;
	return InputGuess();
}

string WordleBoard::GetNextGuess()
{
	++m_currentRow;
	m_currentColumn = 0;
	return InputGuess();
}

string WordleBoard::InputGuess()
{
    if (!m_gameWindow.isOpen())
        return string();

	if ( m_currentRow > 5 )
        return string();

	sf::Vector2i mousePosition;
	bool mouseClicked = false;

	m_stillThinking = true;
	while ( m_stillThinking )
	{
		// Handle keyboard events
		sf::Event event;
		while (m_gameWindow.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				m_gameWindow.close();
				break;
			}
			else if (event.type == sf::Event::TextEntered)
			{
				m_message.setString("");

				char input = event.text.unicode;
				if (input >= 'a' && input <= 'z')
				{
					input = toupper(input);
				}
				if (input >= 'A' && input <= 'Z')
				{
					ProcessLetter(string(1, input));
				}
				else if (input == '\b')
				{
					ProcessBackspace();
				}
				else if (input == '\r')
				{
					ProcessEnter();
				}
				else
				{
					char t = input;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				m_message.setString("");
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					CheckMousePosition(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
				}
			}
		}
		UpdateDisplay();
	}

	return GetCurrentGuess();
}

void WordleBoard::DisplayMessage(std::string message)
{
	m_message.setString(message);
}

void WordleBoard::GameWon(std::string message)
{
	m_endGameText.setString(message);
	m_endGameText.setFont(m_gameWonFont);
    m_endGameText.setFillColor(sf::Color(20, 180, 20));
	GameOver();
}

void WordleBoard::GameLost(std::string message)
{
	m_endGameText.setString(message);
	m_endGameText.setFont(m_gameLostFont);
    m_endGameText.setFillColor(sf::Color(210, 20, 20));
	GameOver();
}

void WordleBoard::GameOver()
{
	UpdateDisplay();

	while (m_gameWindow.isOpen())
	{
		// Handle keyboard events
		sf::Event event;
		while (m_gameWindow.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				m_gameWindow.close();
				break;
			}
		}
	}
}

void WordleBoard::CheckMousePosition(sf::Vector2f mousePosition)
{
	if (m_backspace.Clicked(mousePosition))
	{
		ProcessBackspace();
	}
	else if (m_enter.Clicked(mousePosition))
	{
		ProcessEnter();
	}
	else
	{
		for (auto choice : m_choices)
		{
			if (choice.second.Clicked(mousePosition))
			{
				ProcessLetter(choice.second.GetLetter());
				break;
			}
		}
	}
}

void WordleBoard::ProcessLetter(string letter)
{
	if (m_currentColumn < 5)
	{
		m_letters[m_currentRow][m_currentColumn].SetLabel(letter);
		++m_currentColumn;
	}
}

void WordleBoard::ProcessEnter()
{
	m_stillThinking = m_currentColumn < 5;
}

void WordleBoard::ProcessBackspace()
{
	if (m_currentColumn > 0)
	{
		--m_currentColumn;
		m_letters[m_currentRow][m_currentColumn].SetLabel(" ");
	}
}

string WordleBoard::GetCurrentGuess()
{
	string guess;
	for (int iCol = 0; iCol < 5; ++iCol)
	{
		guess += m_letters[m_currentRow][iCol].GetLetter();
	}
	return guess;
}
void WordleBoard::MarkGuessLetterWrong(int location)
{
	m_letters[m_currentRow][location].WrongLetter();
}

void WordleBoard::MarkGuessLetterWrongPosition(int location)
{
	m_letters[m_currentRow][location].MatchingLetter();
}

void WordleBoard::MarkGuessLetterCorrectPosition(int location)
{
	m_letters[m_currentRow][location].MatchingLetterAndPosition();
}

void WordleBoard::MarkAlphabetLetterWrong(char letter)
{
	m_choices[letter].WrongLetter();
}

void WordleBoard::MarkAlphabetLetterCorrectPosition(char letter)
{
	m_choices[letter].MatchingLetterAndPosition();
}

void WordleBoard::MarkAlphabetLetterWrongPosition(char letter)
{
	m_choices[letter].MatchingLetter();
}

Letter::Status WordleBoard::GetLetterStatus(char letter)
{
	return m_choices[letter].GetStatus();
}
