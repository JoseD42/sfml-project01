#pragma once
#include<box2d/box2d.h>
#include<SFML/Graphics.hpp>
#include "Score.hh"

class ContactListener : public b2ContactListener
{
    private:
        Score* score;
    public:
        ContactListener(Score*&);
        ~ContactListener();
        
        void BeginContact(b2Contact*);
        void EndContact(b2Contact*);
};
