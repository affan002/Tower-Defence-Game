#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <iostream>
#include <vector>

#include "screen.h"




class startScreen : screen{
    private:
        Font titleFont;
        Text title;
        Texture bgTexture;
        Sprite startBg;

    public:
        startScreen(RenderWindow* w, std::vector<screen*>* s);
};