#pragma once
#include "MapTile.h"


//Read from file, + only read this file once to generate the map
//only read model once 

//wavefunction collapse 
//infinite playground (regenerate map when goes out of bound)

class MapGen
{
	public:
		int map_WD, map_HT;
		std::vector<MapTile*> map;
		 
		MapGen() {}
		~MapGen() {/*Delete the array when exit the game*/ }
		MapGen(int x, int y) : map_WD(x), map_HT(y) {}

		void CreateTileMap()
		{
			Scene::Instance()->SetMapDimensions(map_WD, map_HT);
			auto& worldMap = Scene::Instance()->GetMapColliders();
			worldMap.resize(map_WD * map_HT, false);

			for(int x = 0; x < map_WD; x++)
			{
				for(int y = 0; y < map_HT; y++)
				{
					MapTile* tile = new MapTile(x, y, OPEN);
					bool createBlockTile = (rand()%15 == 0);
					if(createBlockTile)
					{
						tile->SetType(BLOCKED);
						//Create building static mesh 
						tile->GenerateStaticOBJ(tile->position, 1);
						worldMap[x + y * map_WD] = true;
					}
					else
					{
						//Create walkable space
						tile->GenerateStaticOBJ(tile->position, 0);
					}

					map.push_back(tile);
				}
			}
		}
};