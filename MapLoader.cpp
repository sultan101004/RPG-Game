#include "MapLoader.h"
#include<fstream>
#include<string>

using namespace std;

void MapLoader::LoadMap( const std::string& mapFilePath)
{
	string line;
	ifstream mapFile(mapFilePath);

	if (mapFile.is_open()) {
		while (getline(mapFile, line)) {

			if (line == "[Map]") {
				continue;
			}
			else {
				cout << line << endl;
			}
		}
	}

}


void MapLoader::SaveMap(const Map& map, const std::string& mapFilePath)
{
}

void MapLoader::PrintMap(const Map& map)
{
 }
