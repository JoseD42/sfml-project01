#pragma once
#include<SFML/Graphics.hpp>

class Score
{
    private:
        sf::Font* font{new sf::Font()};
        sf::Text* scoreText{new sf::Text()};
        sf::RenderWindow* window;
        int score{};
        const char* text;
    public:
        Score(const char*, const char*, unsigned int, sf::Color*, sf::RenderWindow*&);
        ~Score();
        void Update();
        void AddPoints(unsigned int);
};
