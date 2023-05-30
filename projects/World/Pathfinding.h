#pragma once

#include "core/math/mat4.h"
#include "../Gameobject/MapGen.h"
//singleton ??

class Astar
{
public:
	static Astar* Instance()
	{
		static Astar instance;
		return &instance;
	}

	void FindPath(vec3 startPos, vec3 targetPos) //find all the neighbouring tile at current position
	{
		//get the index of the tile right below the player and enemy
		//raycast straight down to get hit on specific tile and use that tile
		MapTile s_Tile = MapGen::Instance()->GetMapElement(0); //enemy position standing tile
		MapTile t_Tile = MapGen::Instance()->GetMapElement(MapGen::Instance()->GetLastElement()); //player position standing tile

		openSet.push_back(s_Tile); //add it to the list

		while(openSet.size() > 0)
		{
			MapTile currentTile = openSet[0];

			for(int i = 1; i < openSet.size(); i++)
			{
				if (openSet[i].tileProp.f_Cost < currentTile.tileProp.f_Cost ||
					openSet[i].tileProp.f_Cost == currentTile.tileProp.f_Cost
					&& openSet[i].tileProp.h_Cost < currentTile.tileProp.h_Cost)
					currentTile = openSet[i];
			}
			openSet.pop_back();
			closedSet.push_back(currentTile);

			//need to operator overload == for maptile == maptile
			if(currentTile.position == t_Tile.position) //Check if reached to end 
			{
				std::cout << "Found path to player" << std::endl;
			}

			std::vector<MapTile*> neighbours = MapGen::Instance()->GetNeighbours(currentTile);
			//Need to operator overload || 
			for(auto& neighbour : neighbours)
			{
				if(!neighbour->tileProp.type == OPEN /* || std::find(neighbours.begin(), neighbours.end(), currentTile)*/)
				{
					continue;
				}
				//Calculate the distance()
			}
		}
	}

	void FindPath(MapTile startPos, MapTile targetPos); //find all the neighbouring tile at current position

	void FindNeighbour(){}

	int GetDistance(MapTile a, MapTile b) //Calculate the distance between the cur to tar node
	{
		int distX = abs(a.tileProp.x_Coord - a.tileProp.x_Coord);
		int distY = abs(a.tileProp.y_Coord - a.tileProp.y_Coord);

		if (distX > distY)
			return (14 * distY + 10 * (distX - distY));
		return (14 * distX + 10 * (distY - distX));
	}
private:
	static Astar* instance;
	std::vector<MapTile> openSet;
	std::vector<MapTile> closedSet;
};