#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <iostream>
#include <vector>

#include "screen.h"




class startScreen : public screen{
    private:
        FloatRect titleRect; 
        Font titleFont;
        Text title;
        Texture bgTexture;
        Sprite startBg;

    public:
        startScreen(RenderWindow* w, std::vector<screen*>* s);
        void update();
        void draw();
};