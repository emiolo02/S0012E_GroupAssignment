#pragma once
////#include <vector>
#include "MapTile.h"
////class MapTile;
//
class MapGen
{
	public:
		int map_WD, map_HT;
		std::vector<MapTile> map;
//
		MapGen() {}
//
		MapGen(int x, int y) : map_WD(x), map_HT(y) {}
//
		void CreateTileMap()
		{
			for(int x = 0; x < map_WD; x++)
			{
				for(int y = 0; y < map_HT; y++)
				{
					MapTile* tile = new MapTile(x, y, OPEN);
				}
			}
		}
};