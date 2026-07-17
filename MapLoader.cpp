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
				else if (variable == "map-width") {
					mapData.mapWidth = stoi(value);
				}
				else if (variable == "map-height") {
					mapData.mapHeight = stoi(value);
				}
				else if (variable == "dataSize") {
					mapData.dataSize = stoi(value);
				}
				else if (variable == "data") {
					// Multi-line data: read subsequent lines until EOF or blank line
					std::string dataLine;
					
					// First, parse anything that might be on the same line as "data=" (if any)
					if (!value.empty()) {
						size_t pos = 0;
						std::string tempValue = value;
						while ((pos = tempValue.find(',')) != std::string::npos) {
							std::string token = tempValue.substr(0, pos);
							mapData.data.push_back(stoi(token));
							tempValue = tempValue.substr(pos + 1);
						}
						if (!tempValue.empty()) mapData.data.push_back(stoi(tempValue));
					}

					// Then read the subsequent grid lines
					while (std::getline(mapFile, dataLine)) {
						// Trim whitespace from line
						dataLine.erase(0, dataLine.find_first_not_of(" \t\r\n"));
						dataLine.erase(dataLine.find_last_not_of(" \t\r\n") + 1);
						
						if (dataLine.empty()) break; // End of block or file
						
						size_t pos = 0;
						while ((pos = dataLine.find(',')) != std::string::npos) {
							std::string token = dataLine.substr(0, pos);
							mapData.data.push_back(stoi(token));
							dataLine = dataLine.substr(pos + 1);
						}
						if (!dataLine.empty()) mapData.data.push_back(stoi(dataLine));
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
