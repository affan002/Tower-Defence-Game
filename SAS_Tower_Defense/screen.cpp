#include "screen.h"

screen::screen(RenderWindow* win, std::vector<screen*>* sc){
    window = win;
    screens = sc;
}
screen::~screen(){

}