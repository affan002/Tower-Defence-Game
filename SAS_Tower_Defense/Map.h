#include <iostream>
#include <vector>
#include <cmath>
#include <set>
const int TILE_SIZE = 45; // Size of each tile in pixels
// const int GRID_WIDTH = 20;
// const int GRID_HEIGHT = 20;

// Define the path layout using a grid
const std::vector<std::vector<int>> levelMap = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    
};

    std::pair<int, int> getStartInVec(){
        std::pair<int, int> Pos;
        for (int i = 0;i < levelMap.size();i++){
            
            if (levelMap[i][0] == 1){
                Pos.second = i;
                Pos.first = 0;
                break;
            }
        }
        
        return Pos;
    }

    std::pair<int, int> getStartPos(){
        std::pair<int, int> Pos;
        for (int i = 0;i < levelMap.size();i++){
            
            if (levelMap[i][0] == 1){
                Pos.second = i*TILE_SIZE;
                Pos.first = 0*TILE_SIZE;
                break;
            }
        }
        
        return Pos;
    }
    
    std::pair<int, int> getEndInVec(){
        std::pair<int, int> Pos;
        for (int i = 0;i < levelMap.size();i++){
            
            if (levelMap[i][19] == 1){
                Pos.second = i;
                Pos.first = 19;
                break;
            }
        }
        // Pos.second = 11;
        // Pos.first = 13;
        return Pos;
    } 

    std::pair<int, int> getEndPos(){
        std::pair<int, int> Pos;
        for (int i = 0;i < levelMap.size();i++){
            
            if (levelMap[i][19] == 1){
                Pos.second = i*TILE_SIZE;
                Pos.first = 19*TILE_SIZE;
                break;
            }
        }
        // Pos.second = 11*TILE_SIZE;
        // Pos.first = 13*TILE_SIZE;
        return Pos;
    } 

    
    int startRow = getStartInVec().second;
    int startCol = getStartInVec().first;
    std::vector<std::pair<int, int>> getPathwayPositions() {
        std::vector<std::pair<int, int>> path;
        std::set<std::pair<int, int>> visited;  // To keep track of visited positions

        int rows = levelMap.size();
        int cols = levelMap[0].size();

        // Directions for moving: up, down, left, right
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // Start at the given position
        int currentRow = startRow, currentCol = startCol;
        
        // Traverse the grid
        while (true) {
            // Add the current position to the path
            path.push_back({currentRow, currentCol});
            visited.insert({currentRow, currentCol});
            
            bool moved = false;
            
            // Try all 4 directions
            for (auto& dir : directions) {
                int newRow = currentRow + dir[0];
                int newCol = currentCol + dir[1];

                // Check if the new position is within bounds and contains a '1' and hasn't been visited
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && levelMap[newRow][newCol] == 1 && visited.find({newRow, newCol}) == visited.end()) {
                    // Move to the new position
                    currentRow = newRow;
                    currentCol = newCol;
                    moved = true;
                    break;
                }
            }

            // If no valid move was made, break the loop
            if (!moved) {
                break;
            }
        }
        
        return path;
    }

    std::vector<std::pair<int, int>> path = getPathwayPositions();


    std::pair<int, int> getPos(int x,int y){ //convert i,j of vector into x,y of screen
        std::pair<int, int> Pos;
        Pos.second = x*TILE_SIZE;
        Pos.first = y*TILE_SIZE;
        return Pos;
    }





// int call = 1;



// if (std::find(visited.begin(), visited.end(), tile) == visited.end()) {
        //     visited.push_back(tile);  // Add i to the vector if it's not present
        // }
        // visited.push_back(tile);
        // std::string v = vectorToString(visited);
        // tartText.setString(v);


            // if (std::find(visited.begin(), visited.end(), nextTile) == visited.end()) {
        //     visited.push_back(nextTile);  // Add i to the vector if it's not present
        // }

        // void Enemy::CheckDirection() {
    // switch (dir) {
    //     case UP:
    //         yVelocity = 0-speed;
    //         xVelocity = 0;
    //         break;
    //     case DOWN:
    //         yVelocity = speed;
    //         xVelocity = 0;
    //         break;
    //     case LEFT:
    //         xVelocity = 0-speed;
    //         yVelocity = 0;
    //         break;
    //     case RIGHT:
    //         xVelocity = speed;
    //         yVelocity = 0;
    //         break;
    //     case IDLE:
    //         xVelocity = 0;
    //         yVelocity = 0;
    //         break;
    //     }
    
// }







        // sf::Text debugText;
    //     sf::Font startFont;
    // sf::Text startText;
    // sf::Font tartFont;
    // sf::Text tartText;


    //std::string vectorToString(const std::vector<std::pair<int,int>>& vec) {
//         std::ostringstream oss;
//         for (size_t i = 0; i < vec.size(); ++i) {
//             oss << "(" << vec[i].first<< "," << vec[i].second << ")";
//             if (i < vec.size() - 1) {
//                 oss << ", "; // Add comma between numbers
//             }
//         }
//         return oss.str();
//     }


    // In the render loop
    // window.draw(startText);
    // window.draw(tartText);

    // // Optional: Debugging message for direction
    // startFont.loadFromFile("fonts/upheavtt.ttf");
    // startText.setFont(startFont);
    // startText.setString(std::to_string(dir) + "   " + std::to_string(tile.first) + "   " + std::to_string(tile.second) + "    " + std::to_string(position.x) + "    " + std::to_string(position.y));
    // startText.setFillColor(Color::Black);
    // startText.setCharacterSize(20);
    // startText.setPosition(20, 20);
    // tartFont.loadFromFile("fonts/upheavtt.ttf");
    // tartText.setFont(startFont);
    
    // tartText.setFillColor(Color::Black);
    // tartText.setCharacterSize(20);
    // tartText.setPosition(20, 400);