#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Letter
{
public:
	enum Status
	{
		UNUSED,
		WRONG,
		WRONG_LOCATION,
		CORRECT_LOCATION
	};

    Letter();
    void WrongLetter();
    void MatchingLetter();
    void MatchingLetterAndPosition();
    void Reset();
    void Draw(sf::RenderWindow & gameWindow);
    void SetPosition(float x, float y);
    static sf::Font * letterFont;
    static sf::Font* GetFont() { return letterFont; }
    void SetLabel(std::string letter);
    std::string GetLetter() { return m_letter.getString(); }
    Status GetStatus() { return m_status; }

protected:
    sf::RectangleShape m_letterBox;
    sf::Text m_letter;
    float m_width;
    float m_height;
    Status m_status = UNUSED;
};

class KeyboardLetter : public virtual Letter
{
public:
    KeyboardLetter();
    bool Clicked(sf::Vector2f mousePosition);
};

class SpecialKey : public virtual KeyboardLetter
{
public:
    SpecialKey();
};
