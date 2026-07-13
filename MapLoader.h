#pragma once
#include<iostream>
#include<fstream>

#include "Map.h"

class MapLoader
{

public:
	void LoadMap(const std::string& mapFilePath);
	void SaveMap(const Map& map, const std::string& mapFilePath);
	void PrintMap(const Map& map);
	
};

