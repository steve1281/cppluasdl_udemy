#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include <fstream>
#include "./Components/TileComponent.h"

extern EntityManager manager;

Map::Map(std::string textureId, int scale, int tileSize) {
    this->textureId = textureId;
    this->scale = scale;
    this->tileSize=tileSize;
}


void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
    std::fstream mapFile;
    mapFile.open(filePath);

    //std::cout << "tilesize :" << tileSize << std::endl;
    for (int y=0; y< mapSizeY; y++) {
        for (int x=0; x <mapSizeX; x++) {
            char ch;
            mapFile.get(ch);
            //std::cout << ch ;
            int sourceRectY = atoi(&ch) * tileSize;
            mapFile.get(ch);
            //std::cout << ch ;
            int sourceRectX = atoi(&ch) * tileSize;
            AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
            mapFile.ignore();
            //std::cout << ",";
        }
        //std::cout << std::endl;
    }
    mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y) {
   Entity& newTile(manager.AddEntity("Tile", TILEMAP_LAYER));
   newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureId);
}   
