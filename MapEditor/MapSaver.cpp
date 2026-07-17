#include "MapSaver.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void MapSaver::Save(const std::string& filename,
                    const std::vector<int>& bgData,
                    const MapData& config)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "ERROR: MapSaver could not open file: " << filename << std::endl;
        return;
    }

    // ------------------------------------------------------------------
    // Write header — MapLoader expects "[Map]" on the very first line
    // ------------------------------------------------------------------
    file << "[Map]\n";
    file << "version="     << config.version    << "\n";
    file << "tilesheet="   << config.tilesheet  << "\n";
    file << "name="        << config.name       << "\n";
    file << "tile-width="  << config.tileWidth  << "\n";
    file << "tile-height=" << config.tileHeight << "\n";
    file << "scale-x="     << config.scaleX     << "\n";
    file << "scale-y="     << config.scaleY     << "\n";
    file << "map-width="   << config.mapWidth   << "\n";
    file << "map-height="  << config.mapHeight  << "\n";
    file << "dataSize="    << bgData.size()     << "\n";

    // ------------------------------------------------------------------
    // Write comma-separated tile IDs in a neat grid (rows x columns)
    // -1 means "empty cell" — MapLoader / Map.cpp will skip those cells
    // ------------------------------------------------------------------
    file << "data=\n";
    for (int row = 0; row < config.mapHeight; ++row) {
        for (int col = 0; col < config.mapWidth; ++col) {
            int i = row * config.mapWidth + col;
            file << std::setw(4) << bgData[i];
            if (col < config.mapWidth - 1 || row < config.mapHeight - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
    std::cout << "Map saved successfully to: " << filename << std::endl;
}
