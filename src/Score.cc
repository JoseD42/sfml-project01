#include "Score.hh"
#include<iostream>

Score::Score(const char* fontUrl, const char* text, unsigned int fontSize, sf::Color* fillColor, sf::RenderWindow*& window)
{
    font->loadFromFile(fontUrl);
    scoreText->setFont(*font);
    scoreText->setString(text);
    scoreText->setCharacterSize(fontSize);
    scoreText->setFillColor(*fillColor);
    this->text = text;
    this->window = window;
}

Score::~Score()
{

}

void Score::Update()
{
    window->draw(*scoreText);
}

void Score::AddPoints(unsigned int points)
{
    score += points;
    scoreText->setString(text + std::to_string(score));
}
