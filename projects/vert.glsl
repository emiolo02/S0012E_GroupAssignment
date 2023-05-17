#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec4 tangent;

out vec3 outPosition;
out vec4 outColor;
out vec2 outTexCoord;
out vec3 outNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 u_position;

void main()
{
	outPosition = vec3(model * vec4(position, 1.0f));
	outTexCoord = texCoord;
	outNormal = normal; 

	gl_Position = projection * view * model * vec4(position, 1);
};