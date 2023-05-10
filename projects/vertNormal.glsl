#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec4 tangent;

out vec3 outPosition;
out vec2 outTexCoord;
out vec3 outNormal;
out mat3 TBN;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	outPosition = vec4(model * vec4(position, 1)).xyz;
	outTexCoord = texCoord;
	outNormal = vec4(model * vec4(normal, 1)).xyz; 

	vec3 T = normalize(vec3(model * tangent));
	vec3 N = normalize(vec3(model * vec4(normal, 1)));
	vec3 B = normalize(cross(N, T));

	TBN = mat3(T, B, N);

	gl_Position = projection * view * model * vec4(position, 1);
};