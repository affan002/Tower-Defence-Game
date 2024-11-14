#include "startScreen.h"
#include <iostream>

startScreen::startScreen(RenderWindow* w, std::vector<screen*>* s) : screen(w,s){
    if(!bgTexture.loadFromFile("images/background_start.png")) {
        std::cout << "eror" << std::endl;
    }
    startBg.setTexture(bgTexture);
    if (!titleFont.loadFromFile("fonts/Robus.otf"))
    {
        std::cout << "error" << std::endl;
    }
    title.setFont(titleFont);
    //maybe change the title
    title.setString("SAS Tower Defence");
    titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width/2.0f, titleRect.top  + titleRect.height/2.0f);
    title.setPosition(Vector2f(this->window->getSize().x/2.0f,this->window->getSize().y/3.0f));
    title.setFillColor(Color::Black);
    title.setCharacterSize(100);
}