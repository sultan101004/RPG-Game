#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct MapData {
	
	float version;

	string tilesheet = "";
	string name = "";

	int tileWidth = 0;
	int tileHeight = 0;
	
	int scaleX = 0;
	int scaleY = 0;

	int dataSize = 0;
	std::vector<int> data;
};
