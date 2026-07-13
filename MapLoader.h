#pragma once
#include<iostream>
#include<fstream>

#include "Map.h"
#include "MapData.h"

class MapLoader
{

public:
	void LoadMap(const std::string& mapFilePath, MapData&md);
	void SaveMap(const Map& map, const std::string& mapFilePath);
	void PrintMap(const Map& map);
	
};

