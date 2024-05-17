#include "Letter.h"
#include <SFML/Graphics.hpp>

sf::Font * Letter::letterFont = nullptr;

Letter::Letter()
{
    if (letterFont == nullptr)
    {
        letterFont = new sf::Font();
        letterFont->loadFromFile("c:\\windows\\Fonts\\arialbd.ttf");
    }
    m_width = 50.f;
    m_height = m_width;
    m_letter.setFont(*letterFont);
    SetLabel(" ");
    m_letter.setFillColor(sf::Color::Black);
    m_letterBox.setSize(sf::Vector2f(m_width, m_height));
    m_letterBox.setPosition(m_width/10.f, m_height/10.f);
    m_letterBox.setFillColor(sf::Color::White);
    float tempy = m_letter.getLocalBounds().height;
    m_letter.setLineSpacing(0.f);
}

void Letter::SetLabel(std::string letter)
{
    m_letter.setString(letter);
    m_letter.setOrigin( m_letter.getLocalBounds().width / 2.f, m_letter.getLocalBounds().height * 3.f / 4.f );
}
void Letter::WrongLetter()
{
    m_status = WRONG;
    m_letterBox.setFillColor(sf::Color(120, 124, 126));
    m_letter.setFillColor(sf::Color::White);
}

void Letter::MatchingLetter()
{
    m_status = WRONG_LOCATION;
    m_letterBox.setFillColor(sf::Color(201, 180, 88));
    m_letter.setFillColor(sf::Color::White);
}

void Letter::MatchingLetterAndPosition()
{
    m_status = CORRECT_LOCATION;
    m_letterBox.setFillColor(sf::Color(106, 170, 100));
    m_letter.setFillColor(sf::Color::White);
}

void Letter::Reset()
{
    m_status = UNUSED;
    m_letterBox.setFillColor(sf::Color::White);
    m_letter.setFillColor(sf::Color::Black);
}

void Letter::Draw( sf::RenderWindow & gameWindow )
{
    gameWindow.draw(m_letterBox);
    gameWindow.draw(m_letter);
}

void Letter::SetPosition(float x, float y)
{
    m_letterBox.setPosition(x, y);
    m_letter.setPosition(x + m_width / 2.f, y + m_height / 2.f);
}

KeyboardLetter::KeyboardLetter()
{
    if (letterFont == nullptr)
    {
        letterFont = new sf::Font();
        letterFont->loadFromFile("c:\\windows\\Fonts\\arialbd.ttf");
    }
    m_width = 25.f;
    m_height = m_width;
    m_letter.setFont(*letterFont);
    SetLabel(" ");
    m_letter.setFillColor(sf::Color::Black);
    m_letterBox.setSize(sf::Vector2f(m_width, m_height));
    m_letterBox.setPosition(m_width/10.f, m_height/10.f);
    m_letterBox.setFillColor(sf::Color::White);
    m_letter.setLineSpacing(0.f);
    m_letter.setCharacterSize(15);
}

bool KeyboardLetter::Clicked(sf::Vector2f mousePosition)
{
    sf::FloatRect keyBounds = m_letterBox.getGlobalBounds();
    return keyBounds.contains(mousePosition);
}

SpecialKey::SpecialKey()
{
    m_width = 40.f;
    m_height = 25.f;

    m_letter.setFillColor(sf::Color::Black);
    m_letterBox.setSize(sf::Vector2f(m_width, m_height));
    m_letterBox.setPosition(m_width/10.f, m_height/10.f);
    m_letterBox.setFillColor(sf::Color::White);
    m_letter.setLineSpacing(0.f);
    m_letter.setCharacterSize(10);
}
