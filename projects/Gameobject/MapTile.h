#pragma once
#include "GameObj.h"


enum TileType
{
	OPEN = 0,
	BLOCKED = 1
};

struct TileProperties
{
	int id;
	int x_Coord;
	int y_Coord;
	TileType type;
	TileProperties() : id(++s_id) {}
	
	/*
	* g = distance from start tile
	* h = distance from end tile
	* f = total cost (g + h)
	*/
	int g_Cost, h_Cost, f_Cost;

protected:
	static std::atomic<int> s_id;

};

//initialize atomic integer 
std::atomic<int> TileProperties::s_id;

//FANCY SHIT A* PROPERTIES //TO IMPLEMENT LATER

class StaticObj;

class MapTile : public GameObj
{
public:
	TileProperties tileProp;
	

	MapTile() //Defualt opem space on origin
	{
		tileProp.x_Coord = 0;
		tileProp.y_Coord = 0;
		tileProp.type = OPEN;
		position = vec3(tileProp.x_Coord, 0, tileProp.y_Coord);
	}

	MapTile(int x, int y, TileType type )
	{
		tileProp.x_Coord = x;
		tileProp.y_Coord = y;
		tileProp.type = type;
		
		position = vec3(tileProp.x_Coord, 0, tileProp.y_Coord);
	}

	bool isWalkable()
	{
		return tileProp.type != BLOCKED;
	}

	int SetType(TileType t)
	{
		switch (t)
		{
		case 0: return tileProp.type = OPEN; 
		case 1: return tileProp.type = BLOCKED;
		}
	}

	//generate the static mesh on top of the tile
	void GenerateStaticOBJ(vec3 pos, int modelID)
	{
		position = vec3(pos.x,0.25f,pos.z);
		StaticObj* staticObj = new StaticObj(position);
		staticObj->Init(modelID);
	}

	//Astar Calculate costs
	int CalculateFCost()
	{
		return (tileProp.f_Cost + tileProp.h_Cost);
	}
};