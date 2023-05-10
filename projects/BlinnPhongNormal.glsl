#version 460 core

in vec3 outPosition;
in vec2 outTexCoord;
in mat3 TBN;

layout(binding = 0) uniform sampler2D u_texture;
layout(binding = 1) uniform sampler2D u_normal;
layout(binding = 2) uniform sampler2D u_emissive;
layout(binding = 3) uniform sampler2D u_AO;

uniform vec3 cameraPos;

layout(location = 0) out vec4 color;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;

struct PointLight
{
	vec3 position;
	vec3 color;
	float intensity;
};

struct Sun
{
	vec3 direction;
	vec3 color;
	float intensity;
};
#define POINT_LIGHTS 2
uniform PointLight pointLights[POINT_LIGHTS];

uniform Sun sun;

vec3 CalcSun(Sun sun, vec3 normal, vec3 fragPos)
{
	// Ambient
	vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);
	
	// Diffuse
	vec3 diffuse = sun.color * clamp(dot(normalize(-sun.direction), normal), 0, 1) * sun.intensity;

	return (ambientLight * material.ambient + diffuse * material.diffuse);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 camPos)
{
	// Ambient
	vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);
	
	// Diffuse
	vec3 dirToLight = normalize(light.position - fragPos);
	vec3 diffuse = light.color * clamp(dot(dirToLight, normal), 0, 1);
	float distance = length(light.position - fragPos);
	diffuse = diffuse * (1.0 / (1.0 + (0.01 * distance))) * light.intensity;


	// Highlight
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 viewDir = normalize(camPos - fragPos);
	vec3 halfWay = normalize(lightDir + viewDir);
	float specularConstant = pow(max(dot(normal, halfWay), 0), 20);
	vec3 highlight = light.color * specularConstant;

	return (ambientLight * material.ambient + diffuse * material.diffuse + highlight * material.specular);
}

void main()
{
	vec3 normal = normalize(texture(u_normal, outTexCoord).rgb);
	normal = normalize(normal * 2 - 1);
	normal = normalize(TBN * normal);

	vec3 lights = vec3(0);

	for (int i = 0; i < POINT_LIGHTS; i++)
		lights += CalcPointLight(pointLights[i], normal, outPosition, cameraPos);

	lights += CalcSun(sun, normal, outPosition);

	color = texture(u_texture, outTexCoord) * vec4(lights, 1) + texture(u_emissive, outTexCoord); 
};