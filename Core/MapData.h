#pragma once
#include <string>
#include <vector>

struct MapData {

    float version = 1.0f;

    std::string tilesheet = "";
    std::string name      = "";

    int tileWidth  = 0;
    int tileHeight = 0;

    int scaleX = 0;
    int scaleY = 0;

    int mapWidth  = 0;   // Number of tile columns in the map grid
    int mapHeight = 0;   // Number of tile rows in the map grid

    int dataSize = 0;
    std::vector<int> data; // Tile IDs (-1 = empty cell)
};
