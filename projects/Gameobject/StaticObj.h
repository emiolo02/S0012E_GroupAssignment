#include "GameObj.h"


enum ModelID
{
	ROAD = 0,
	BUILDING = 1
};

struct modelP
{
	std::string modelPath;
	void GetModel(int m_id)
	{
		switch (m_id)
		{
		case 0: 
			modelPath = "../assets/Kenney/roadAsphalt_cornerInner.obj";
			break;
		case 1:
			modelPath = "../assets/Kenney/wallA.obj";
			break;
		default:
			break;
		}
	}

	std::string GetModelPath() { return modelPath; }
};


class StaticObj : public GameObj
{
public:
	StaticObj();
	StaticObj(vec3 pos);
	modelP m_Path;

	void Init(
		std::string modelPath, 
		std::string texturePath, 
		std::shared_ptr<ShaderResource> shader, 
		BlinnPhongMaterial& mat
	);

	void Init(
		std::string modelPath,
		std::shared_ptr<ShaderResource> shader,
		BlinnPhongMaterial& mat
	);

	//testing with id
	void Init(
		int modelID,
		std::shared_ptr<ShaderResource> shader,
		BlinnPhongMaterial& mat
	);
};