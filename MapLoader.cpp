#include<fstream>
//#include<string>

#include "MapLoader.h"
#include"MapData.h"

using namespace std;

void MapLoader::LoadMap( const std::string& mapFilePath, MapData& mapData)
{
	//MapData data;

	string line;
	ifstream mapFile(mapFilePath);
	 
	bool isMapValid = false;

	if (mapFile.is_open()) {
		
		while (getline(mapFile, line)) {

			if (!isMapValid) {
				if (line == "[Map]") {
					isMapValid = true;
					continue;
				}
				else {
					cout << "map file is not valid" << endl;
					break;
				}
			}

			if (isMapValid) {
				size_t count = line.find('=');
				string variable = line.substr(0, count);
				string value = line.substr(count + 1, line.length() - count);

				if (variable == "version") {
					mapData.version = stof(value);
				}
				else if (variable == "tilesheet") {
					mapData.tilesheet = value;
				}
				else if (variable == "name") {
					mapData.name = value;
				}
				else if (variable == "tile-width") {
					mapData.tileWidth = stoi(value);
				}
				else if (variable == "tile-height") {
					mapData.tileHeight= stoi(value);
				}
				else if (variable == "scale-x") {
					mapData.scaleX = stoi(value);
				}
				else if (variable == "scale-y") {
					mapData.scaleY = stoi(value);
				}
				else if (variable == "dataSize") {
					mapData.dataSize = stoi(value);
				}
				else if (variable == "data") {
					
					size_t pos = 0;
					// Parse comma separated values
					while ((pos = value.find(',')) != string::npos) {
						mapData.data.push_back(stoi(value.substr(0, pos)));
						value = value.substr(pos + 1);
					}
					// Grab the final number after the last comma
					if (!value.empty()) {
						mapData.data.push_back(stoi(value));
					}
				}

			}
		}

		//cout << "tilesheet: " << data.tilesheet << endl;
		//cout << "name: " << data.name << endl;
		//cout << "tileWidth: " << data.tileWidth << endl;
		//cout << "tileHeight: " << data.tileHeight << endl;
		//cout << "scaleX: " << data.scaleX << endl;
		//cout << "scaleY: " << data.scaleY << endl;
		//cout << "dataSize: " << data.dataSize << endl;
		////cout << "dataArray: " << *data.data << endl;
		//for (int i = 0; i < data.dataSize; i++) {
		//	cout << data.data[i] << " ";
		//}

	mapFile.close();
	}

}


void MapLoader::SaveMap(const Map& map, const std::string& mapFilePath)
{
}

void MapLoader::PrintMap(const Map& map)
{
 }
