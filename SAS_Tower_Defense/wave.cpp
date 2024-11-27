#include "wave.h"

Wave::Wave(std::string _name, int e1, int e2, int e3, int e4, int e5, std::pair<int, int> _startPos, Player* pl)
{
    startPos = _startPos;
    name = _name;
    std::cout << "starting wave " << name << std::endl; 

    //enemy type 5  5000 health   0.25 speed  140 size 500 coins
    for (size_t i = e5; i > 0; i--)
    {
        enemiesWaitlist.push_back(new Enemy(5,"images/ship5.png", startPos, 5000, 0.20, 180, 40*(i-1), 500));      
    }
    //enemy type 4  200 health   1 speed  110 size 150 coins
    for (size_t i = 0; i < e4; i++)
    {
        enemiesWaitlist.push_back(new Enemy(4,"images/ship4.png", startPos, 200, 0.75, 110, 2, 150));      
    }
    //enemy type 3  200 health   1.5 speed  100 size 100 coins
    for (size_t i = 0; i < e3; i++)
    {
        enemiesWaitlist.push_back(new Enemy(3,"assets/images/ship3.png", startPos, 200, 1, 100, 2, 100));      
    }
    //enemy  type 2 50 health   4 speed  80 size 50 coins
    for (size_t i = 0; i < e2; i++)
    {
        enemiesWaitlist.push_back(new Enemy(2,"images/ship2.png", startPos, 50, 2, 80, 2, 50));      
    }
    //enem type 1  100 health   1 speed  80 size 25 coins
    for (size_t i = 0; i < e1; i++)
    {
        enemiesWaitlist.push_back(new Enemy(1,"images/ship1.png",startPos, 100, 0.5, 80, 2, 25));      
    }

    this->font.loadFromFile("fonts/upheavtt.ttf");
    this->text.setFont(this->font);
    this->text.setString(_name + "/5");
    this->text.setFillColor(Color::Black);
    this->text.setCharacterSize(30);
    this->text.setPosition(30,5);
    player = pl;
}

Wave::~Wave()
{
    for(auto i: enemies){
        delete i;
    }
    std::cout << "ending wave " << name << std::endl; 
}

void Wave::Update() {
    // Spawn new enemies from the waitlist if the wait time has passed
    // if (!enemiesWaitlist.empty()) { 
    //     if (wait >= enemiesWaitlist.back()->GetWait()) { // Check if the wait time is met
    //         enemies.push_back(enemiesWaitlist.back());   // Add to active enemies
    //         enemiesWaitlist.pop_back();                 // Remove from the waitlist
    //         wait = 0;                                   // Reset wait timer
    //     } 
    //     wait += 1; // Increment wait time
    // } 

        if (!enemiesWaitlist.empty()) {
        if (spawnClock.getElapsedTime().asSeconds() >= enemiesWaitlist.back()->GetWait()) {
            enemies.push_back(enemiesWaitlist.back());
            enemiesWaitlist.pop_back();
            spawnClock.restart(); // Restart the timer
        }
    }
    // if (call == 1){
    // enemies.push_back(enemiesWaitlist.back());
    // enemiesWaitlist.pop_back();
    // call = 0;
    // }

    // Update all currently active enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        Enemy* enemy = *it;
        enemy->Update(); // Update enemy logic (movement, health, etc.)

        // Check if the enemy reached the end position
        if (enemy->GetCurTile() == getEndPos()) {
            player->health -= 1; // Deduct health
            delete enemy;        // Free memory
            it = enemies.erase(it); // Remove enemy from the list
        }
        // Check if the enemy is dead
        else if (enemy->CheckIfDead()) {
            player->coins += enemy->GetReward(); // Add reward to player

            // Handle enemy splitting logic
            switch (enemy->GetType()) {
                case 5: // Spawn smaller enemies (type 3)
                    for (int j = 0; j < 3; j++) {
                        auto e = new Enemy(3, "assets/images/ship3.png", enemy->GetCurTile(), 
                                           200, 0.9 + 0.2 * j, 100, 0, 100);
                        enemiesWaitlist.push_back(e);
                    }
                    break;
                case 3: // Spawn smaller enemies (type 1)
                    for (int j = 0; j < 3; j++) {
                        auto e = new Enemy(1, "assets/images/ship1.png", enemy->GetCurTile(), 
                                           100, 0.4 + 0.2 * j, 80, 0, 25);
                        enemiesWaitlist.push_back(e);
                    }
                    break;
            }

            delete enemy;        // Free memory
            it = enemies.erase(it); // Remove enemy from the list
        } 
        else {
            ++it; // Move to the next enemy
        }
    }
}


// void Wave::Update(){
//     if (!enemiesWaitlist.empty()){ 
//         if (enemiesWaitlist.back()->GetWait() <= wait) {
//             enemies.push_back(enemiesWaitlist.back());
//             enemiesWaitlist.pop_back();
//             wait = 0;
//         } 
//         wait += 1;
//     } 

//     for (auto it = enemies.begin(); it != enemies.end();) {
//         Enemy* enemy = *it;

//         enemy->Update(); // Update each enemy (waves)

//         // Check if the enemy reached the end position
//         if (enemy->GetCurTile() == getEndPos()) { // waves
//             player->health -= 1; // Deduct health
//             delete enemy;        // Free memory
//             it = enemies.erase(it); // Remove enemy from the list
//         }
//         else if((*it)->CheckIfDead()){
//             // std::cout << "removing element" << std::endl;
//             player->coins += (*it)->GetReward();
//             auto curEnemy = (*it);
//             this->enemies.erase(it);
//             switch (curEnemy->GetType()) {
//                 case 5:
//                     for(int j = 0; j < 3; j++) {
//                         auto e = new Enemy(3,"assets/images/ship3.png", curEnemy->GetCurTile(), 200, 0.9 + 0.2*j, 100, 0, 100);     
//                         // e->SetPath(this->path,curEnemy->GetCurTile(), curEnemy->GetDist());
//                         enemiesWaitlist.push_back(e);
//                     }
//                     break;
//                 case 3:
//                     for(int j = 0; j < 3; j++) {
//                         auto e = new Enemy(1,"assets/images/ship1.png", curEnemy->GetCurTile(), 100, 0.4 + 0.2*j, 80, 0, 25);      
//                         // e->SetPath(this->path,curEnemy->GetCurTile(), curEnemy->GetDist());
//                         enemiesWaitlist.push_back(e);
//                     }
//                     break;
//             }
//             curEnemy->~Enemy();
//         } 
//          else {
//             ++it; // Move to the next enemy
//         }
//     }

    // for (auto i = this->enemies.begin(); i != enemies.end(); ){
    //     (*i)->Update();
    //     (*i)->UpdatePath();
    //     if((*i)->CheckEndOfPath()) {
    //         // std::cout << "removing element" << std::endl;
    //         (*i)->~Enemy();
    //         this->enemies.erase(i);
    //         player->health -= 1;
    //     }
        // else if((*i)->CheckIfDead()){
        //     // std::cout << "removing element" << std::endl;
        //     player->coins += (*i)->GetReward();
        //     auto curEnemy = (*i);
        //     this->enemies.erase(i);
        //     switch (curEnemy->GetType()) {
        //         case 5:
        //             for(int j = 0; j < 3; j++) {
        //                 auto e = new Enemy(3,"assets/images/ship3.png", static_cast<float>(curEnemy->GetPosition().x), static_cast<float>(curEnemy->GetPosition().y), 200, 0.9 + 0.2*j, 100, 0, 100);     
        //                 e->SetPath(this->path,curEnemy->GetCurTile(), curEnemy->GetDist());
        //                 enemiesWaitlist.push_back(e);
        //             }
        //             break;
        //         case 3:
        //             for(int j = 0; j < 3; j++) {
        //                 auto e = new Enemy(1,"assets/images/ship1.png", static_cast<float>(curEnemy->GetPosition().x), static_cast<float>(curEnemy->GetPosition().y), 100, 0.4 + 0.2*j, 80, 0, 25);      
        //                 e->SetPath(this->path,curEnemy->GetCurTile(), curEnemy->GetDist());
        //                 enemiesWaitlist.push_back(e);
        //             }
        //             break;
        //     }
        //     curEnemy->~Enemy();
        // } 
    // else {
    //         i++;
    //     }
    // }
    // bullet animation
// }

void Wave::Render(sf::RenderWindow& window){
    for (Enemy* enemy : enemies) {
        enemy->Render(window);   // waves
    }
    window.draw(this->text);
}

// void Wave::SetPath(std::map<int ,std::vector<std::pair<int,DIRECTION>>>* _path) {
//     path = _path;
//     for (auto e : enemiesWaitlist){
//         e->SetPath(_path,startPos.first*MAPDIM+startPos.second);
//     }
// }

bool Wave::HasEnded() {
    if (enemies.empty() && enemiesWaitlist.empty()) {
        return true;
    }
    return false;
}


std::vector<Enemy*> Wave::getCurEnemies(){
    return this->enemies;
}