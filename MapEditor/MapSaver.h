#pragma once
#include <string>
#include <vector>
#include "MapData.h"

class MapSaver
{
public:
    /// <summary>
    /// Saves the map to a .map file readable by MapLoader.
    /// bgData contains one tile ID per cell (-1 = empty).
    /// config holds tilesheet path, dimensions, and grid size.
    /// </summary>
    static void Save(const std::string& filename,
                     const std::vector<int>& bgData,
                     const MapData& config);
};
