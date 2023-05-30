#pragma once
#include "MapTile.h"


//Read from file, + only read this file once to generate the map
//only read model once 

//wavefunction collapse 
//infinite playground (regenerate map when goes out of bound)

class MapGen
{
	//test singleton
	static MapGen* instance;
	int map_WD, map_HT;
	std::vector<MapTile*> map;
	std::vector<MapTile*> neighbourTiles;

	public:
		 
		static MapGen* Instance()
		{
			static MapGen instance;
			return &instance;
		}

		MapGen() {}
		~MapGen() {/*Delete the array when exit the game*/ }
		//MapGen(int x, int y) : map_WD(x), map_HT(y) {}

		void CreateTileMap(int width, int height)
		{
			map_WD = width; map_HT = height;
			auto resMan = ResourceManager::Instance();

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

		//Testing for astar
		int GetLastElement() { return (map.back()-1)->tileProp.id; }

		MapTile GetMapElement(int id) 
		{
			return *map[id];
		} //Get the tile at index

		std::vector<MapTile*> GetNeighbours(MapTile& tile)
		{
			std::vector<MapTile*> neighbours;

			for(int x = -1; x <= 1; x++)
			{
				for(int y = -1; y <= 1; y++)
				{
					if (x == 0 && y == 0)
						continue;
					
					int checkX = tile.tileProp.x_Coord + x;
					int checkY = tile.tileProp.y_Coord + y;

					if (checkX >= 0 && checkX < map_WD &&
						checkY >= 0 && checkY < map_HT)
						neighbours.insert(neighbours.begin(), &tile);
				}
			}
			return neighbours;
		}
};