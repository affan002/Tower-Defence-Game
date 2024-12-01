#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// #include "Map.h"

// #include "enemy.h"
// #include "enemy.cpp"
// #include "wave.h"
#include "wave.cpp"
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
        this->waves.push_back(new Wave("Wave 1" , 5,0,0,0,0, startPos, player));
        this->waves.push_back(new Wave("Wave 2" , 10,5,0,0,0, startPos, player));
        this->waves.push_back(new Wave("Wave 3" , 5,0,5,0,0, startPos, player));
        this->waves.push_back(new Wave("Wave 4" , 0,5,5,5,0, startPos, player));
        this->waves.push_back(new Wave("Wave 5" , 0,0,0,0,2, startPos, player));

        // enemies.push_back(new Enemy(1, "images/ship1.png", startPos, 100, 1.5, 80, 4, 25)); // waves
        // enemies.push_back(new Enemy(1, "images/ship1.png", startPos, 100, 1.5, 80, 4, 25));
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

    void update() {
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

        player->Update(); // Update player logic
        if (player->health < 1){
            quit = true;
        }
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
        
       

            // Draw all enemies
        // for (Enemy* enemy : enemies) {
        //     enemy->Render(window);   // waves
        // }

        if  (!waves.empty()) {
            (waves.front())->Render(window);
        }
        window.draw(whiteSpace);
        
        player->draw(window);

    }
};