#include "GameObj.h"

class StaticObj : public GameObj
{
public:
	vec3 position;

	StaticObj();
	StaticObj(vec3 pos);

	void Init(
		std::string modelPath, 
		std::string texturePath, 
		std::shared_ptr<ShaderResource> shader, 
		BlinnPhongMaterial& mat
	);
};