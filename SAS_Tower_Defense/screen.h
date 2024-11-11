#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <iostream>
#include <vector>
using namespace sf;

class screen{

    protected:
        std::vector<screen> screens;
        RenderWindow* window;

    public:
        screen();
        virtual ~screen();
        virtual void updateMousePositions();
        virtual void update() = 0;
        virtual void render() = 0;
};      