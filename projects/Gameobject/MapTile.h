#pragma once
#include "GameObj.h"


enum TileType
{
	OPEN = 0,
	BLOCKED = 1
};

struct TileProperties
{
	//bool bWall;
	int x_Coord;
	int y_Coord;
	TileType type;
};

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
	}

	MapTile(int x, int y, TileType type )
	{
		tileProp.x_Coord = x;
		tileProp.y_Coord = y;
		tileProp.type = type;
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
	void GenerateStaticOBJ(vec3 pos, int modelID, std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& mat)
	{
		StaticObj* staticObj = new StaticObj(pos); 
		staticObj->Init(modelID, shader, mat);
		this->SetType(BLOCKED);
	}
};