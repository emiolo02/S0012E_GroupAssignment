#pragma once
#include "MapTile.h"


//Read from file, + only read this file once to generate the map
//only read model once 
class MapGen
{
	public:
		int map_WD, map_HT;
		std::vector<MapTile*> map;
		 
		MapGen() {}
		~MapGen() {/*Delete the array when exit the game*/ }
		MapGen(int x, int y) : map_WD(x), map_HT(y) {}

		void CreateTileMap(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& mat)
		{
			for(int x = 0; x < map_WD; x++)
			{
				for(int y = 0; y < map_HT; y++)
				{
					MapTile* tile = new MapTile(x, y, OPEN);
					bool createBlockTile = (x % 5 == 0 && y % 5 == 0);
					if(createBlockTile)
					{
						tile->SetType(BLOCKED);
						//Create building static mesh 
						tile->GenerateStaticOBJ(tile->position, 1, shader, mat);
					}
					else
					{
						//Create walkable space
						tile->GenerateStaticOBJ(tile->position, 0, shader, mat);
					}

					map.push_back(tile);
				}
			}
		}
};