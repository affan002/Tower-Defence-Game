#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// #include "Map.h"

// #include "enemy.h"
// #include "enemy.cpp"
// #include "wave.h"
#include "wave.cpp"
#include "tower.cpp"
#include "guntower.cpp"
#include "Button.cpp"
#include "rocketlaunchertower.cpp"
#include "slowdownTower.cpp"
#include "milltower.cpp"
// #include "Player.h"

class TileMap {
private:
    
    sf::Texture grassTexture;
    sf::Texture pathTexture;
    sf::Sprite grassSprite;
    sf::Sprite pathSprite; 

    Player* player;

    std::pair<int, int> startPos;
    sf::Font startFont;
    sf::Text startText;

    std::pair<int, int> endPos;
    sf::Font endFont;
    sf::Text endText;
    // std::vector<Enemy*> enemies; // waves
    
    std::vector<Wave*> waves;

    sf::RectangleShape whiteSpace;
    bool quit = false;
    bool win = false;

    std::vector<Tower*> towers;
    

    // for tower 1 gun tower
    sf::Texture t1;
    sf::Sprite tower1;
    bool isPressed1 = false;
    int t1Cost;

    // For tower 2 Rocket Launcher tower
    sf::Texture t2;
    sf::Sprite tower2;
    bool isPressed2 = false;
    int t2Cost;

    // For SlowDown tower
    sf::Texture t3;
    sf::Sprite tower3;
    bool isPressed3 = false;
    int t3Cost;

    // For MillTower 
    sf::Texture t4;
    sf::Sprite tower4;
    bool isPressed4 = false;
    int t4Cost;
    


    // Dragging
    
    sf::Texture d;
    sf::Sprite drag;
   
   
    Vector2i mousePosScreen;
    Vector2i mousePosWindow;
    Vector2f mousePosView;

    
public:
    TileMap() {
        
        if (!grassTexture.loadFromFile("images/grass.jpeg")) {
            std::cerr << "Failed to load grass texture!" << std::endl;
        }
        if (!pathTexture.loadFromFile("images/tile_1.png")) {
            std::cerr << "Failed to load path texture!" << std::endl;
        }

        grassSprite.setTexture(grassTexture);
        pathSprite.setTexture(pathTexture);

        player = new Player();

        this->startPos = getStartPos();
        this->startFont.loadFromFile("fonts/upheavtt.ttf");
        this->startText.setFont(this->startFont);
        this->startText.setString("Start");
        this->startText.setFillColor(Color::Black);
        this->startText.setCharacterSize(20);
        this->startText.setPosition(this->startPos.first,this->startPos.second+5);


        this->endPos = getEndPos();
        this->endFont.loadFromFile("fonts/upheavtt.ttf");
        this->endText.setFont(this->endFont);
        this->endText.setString("End");
        this->endText.setFillColor(Color::Black);
        this->endText.setCharacterSize(20);
        this->endText.setPosition(this->endPos.first,this->endPos.second+5);

        std::srand(std::time(nullptr));
        this->waves.push_back(new Wave("Wave 1" , 5,0,0,2,0, startPos, player));
        this->waves.push_back(new Wave("Wave 2" , 10,5,0,0,0, startPos, player));
        this->waves.push_back(new Wave("Wave 3" , 5,0,5,0,0, startPos, player));
        this->waves.push_back(new Wave("Wave 4" , 0,5,5,5,0, startPos, player));
        this->waves.push_back(new Wave("Wave 5" , 0,0,0,0,2, startPos, player));

        // enemies.push_back(new Enemy(1, "images/ship1.png", startPos, 100, 1.5, 80, 4, 25)); // waves
        // enemies.push_back(new Enemy(1, "images/ship1.png", startPos, 100, 1.5, 80, 4, 25));


        if(!this->t1.loadFromFile("images/tower2.png")){
        std::cout << "nope" << std::endl;
    }
    this->tower1.setTexture(t1);
    this->tower1.setPosition(920, 300);
    this->t1Cost=100;

    
    if(!this->t2.loadFromFile("images/tower1.png")){
        std::cout << "nope" << std::endl;
    }
    this->tower2.setTexture(t2);
    this->tower2.setPosition(1100, 300);
    this->tower2.scale(sf::Vector2f(0.7,0.7));
    this->t2Cost=200;

    
    if(!this->t3.loadFromFile("images/tower3.png")){
        std::cout << "nope" << std::endl;
    }
    this->tower3.setTexture(t3);
    this->tower3.setPosition(920, 500);
    this->tower3.scale(sf::Vector2f(0.778,0.778));
    this->t3Cost=300;

    
    if(!this->t4.loadFromFile("images/mill2.png")){
        std::cout << "nope" << std::endl;
    }
    this->tower4.setTexture(t4);
    this->tower4.setPosition(1100, 500);
    this->tower4.scale(sf::Vector2f(0.778,0.778));
    this->t4Cost=350;


    drag.scale(sf::Vector2f(0.6,0.6));


    }

    ~TileMap(){
        delete player;
        // delete e;
        for(auto i: waves){
        delete i;
        }
    // for (Enemy* enemy : enemies) {
    //     delete enemy; // waves destructor
    // }
    // enemies.clear();
    }

    void update(sf::RenderWindow& window) {
    // for (auto it = enemies.begin(); it != enemies.end();) {
    //     Enemy* enemy = *it;

    //     enemy->Update(); // Update each enemy (waves)

    //     // Check if the enemy reached the end position
    //     if (enemy->GetCurTile() == getEndPos()) { // waves
    //         player->health -= 1; // Deduct health
    //         delete enemy;        // Free memory
    //         enemies.erase(it); // Remove enemy from the list
            

    //     } else {
    //         ++it; // Move to the next enemy
    //     }
    // }

    GunTower g("images/tower2.png", sf::Vector2f(48,48), sf::Vector2f(0.6, 0.6));
    RocketLauncherTower r("images/tower1.png", sf::Vector2f(48,48), sf::Vector2f(0.6, 0.6));
    SlowDownTower s("images/tower3.png", sf::Vector2f(48,48), sf::Vector2f(0.6, 0.6));
    MillTower m("images/mill2.png", sf::Vector2f(48,48),sf::Vector2f(0.6,0.6),this->player);

    

        if  (!waves.empty()) {
            (waves.front())->Update();
            if ((waves.front())->HasEnded()){
                waves.front()->~Wave();
                waves.erase(waves.begin());
            }
        }
        else{
            win = true;
        }

        player->Update(); 
        if (player->health < 1){
            quit = true;
        }

        for(auto i: towers){
        i->Update(this->mousePosView);
        std::vector<Enemy*> rawEnemies;
        for (auto& enemyPtr : waves.front()->getCurEnemies()) {
        rawEnemies.push_back(enemyPtr.get());  // Use get() to get raw pointer
        }
        i->enemieInRange(rawEnemies);

        // i->enemieInRange(waves.front()->getCurEnemies());
        i->collisionDetect(rawEnemies);
        
    }
        updateDrag(window);
        updateMousePositions(window);
        
    }

    bool getQuit(){
        return quit;
    }

    bool getWin(){
        return win;
    }
   

    void draw(sf::RenderWindow& window) {
        for (size_t y = 0; y < levelMap.size(); ++y) {
            for (size_t x = 0; x < levelMap[y].size(); ++x) {
                if (levelMap[y][x] == 0) {
                    grassSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    window.draw(grassSprite);
                } else if (levelMap[y][x] == 1) {
                    pathSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    window.draw(pathSprite);
                }
            }
        }
        
        whiteSpace.setPosition(900, 0);
        whiteSpace.setSize(sf::Vector2f(380, 720));
        whiteSpace.setFillColor(sf::Color::White);
        

        window.draw(this->startText);
        window.draw(this->endText);
        renderDrag(window);
        for(auto i: towers){
        i->Render(&window);
    }
       

            // Draw all enemies
        // for (Enemy* enemy : enemies) {
        //     enemy->Render(window);   // waves
        // }

        if  (!waves.empty()) {
            (waves.front())->Render(window);
        }
        window.draw(whiteSpace);
         window.draw(this->tower1);
        window.draw(this->tower2);
        window.draw(this->tower3);
        window.draw(this->tower4);
        player->draw(window);

    }
    void updateDrag(sf::RenderWindow& window) {
    

    // Button pressed event handling
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::MouseButtonPressed:
            // Check if any of the towers is clicked
            
            if (tower1.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->isPressed1 = true;
            
                
            }
            if (tower2.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->isPressed2 = true;
                
            }
            if (tower3.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->isPressed3 = true;
            }
            if (tower4.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->isPressed4 = true;
            }
           
            break;
            

        case sf::Event::MouseButtonReleased:
            // Check if a tower is placed within bounds
            if (isPressed1 && mousePosView.x < 900 && mousePosView.y < 720 && player->coins>=100) {
                int x = static_cast<int>(mousePosView.x) / 48;  // Ensure it's an integer division
                int y = static_cast<int>(mousePosView.y) / 48;

                // Ensure x and y are within valid bounds
                if (x >= 0 && y >= 0 && x < 15 && y < 15) {  // Assuming 15x15 grid
                    this->towers.push_back(new GunTower("images/tower2.png", sf::Vector2f(x * 48, y * 48), sf::Vector2f(0.6, 0.6)));
                player->coins-=100;
                }
            }

            if (isPressed2 && mousePosView.x < 900 && mousePosView.y < 720&& player->coins>=200) {
                int x = static_cast<int>(mousePosView.x) / 48;
                int y = static_cast<int>(mousePosView.y) / 48;

                if (x >= 0 && y >= 0 && x < 15 && y < 15) {
                    this->towers.push_back(new RocketLauncherTower("images/tower1.png", sf::Vector2f(x * 48, y * 48), sf::Vector2f(0.6, 0.6)));
                player->coins-=200;
                }
            }

            if (isPressed3 && mousePosView.x < 900 && mousePosView.y < 720&& player->coins>=150) {
                int x = static_cast<int>(mousePosView.x) / 48;
                int y = static_cast<int>(mousePosView.y) / 48;

                if (x >= 0 && y >= 0 && x < 15 && y < 15) {
                    this->towers.push_back(new SlowDownTower("images/tower3.png", sf::Vector2f(x * 48, y * 48), sf::Vector2f(0.6, 0.6)));
                player->coins-=200;
                }
            }

            if (isPressed4 && mousePosView.x < 900 && mousePosView.y < 720&& player->coins>=100) {
                int x = static_cast<int>(mousePosView.x) / 48;
                int y = static_cast<int>(mousePosView.y) / 48;

                if (x >= 0 && y >= 0 && x < 15 && y < 15) {
                    this->towers.push_back(new MillTower("images/mill2.png", sf::Vector2f(x * 48, y * 48), sf::Vector2f(0.6, 0.6),this->player));
                    player->coins-=250;
                }
            }
            // Reset the pressed flags
          
                isPressed1 = false;
                isPressed2 = false;
                isPressed3 = false;
                isPressed4 = false;
           
            break;

        default:
            break;
        }
    }
     
if(this->isPressed1 || this->isPressed2 || this->isPressed3|| this->isPressed4){
        if(this->tower1.getGlobalBounds().contains(mousePosView)){
            drag.setTexture(*this->tower1.getTexture());
        }
        if(this->tower2.getGlobalBounds().contains(mousePosView)){
            drag.setTexture(*this->tower2.getTexture());
        }
        if(this->tower3.getGlobalBounds().contains(mousePosView)){
            drag.setTexture(*this->tower3.getTexture());
        }
        if(this->tower4.getGlobalBounds().contains(mousePosView)){
            drag.setTexture(*this->tower4.getTexture());
        }
        drag.setPosition(mousePosView.x, mousePosView.y);
        drag.setOrigin(sf::Vector2f(80 ,80));
    }
    
}




void renderDrag(sf::RenderWindow& window){
    
    if(this->isPressed1 || isPressed2 || isPressed3 || isPressed4){
        window.draw(drag);
    }
} 

void updateMousePositions(sf::RenderWindow& window){
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(window);
    this->mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}
};