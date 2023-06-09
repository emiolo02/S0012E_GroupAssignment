#include "Camera.h"

Camera::Camera()
{
	float fovY = 90;
	this->projection = perspective(fovY * PI / 180, 1024.0f / 768, 0.1f, 100);	
	this->view = mat4();
	this->up = vec3(0, 1, 0);
	this->right = vec3(1, 0, 0);

	float theta0 = atan2(fabs(-1.0), fabs(5.0));
	viewCut.nY = -tan(fovY * PI / 360 - theta0) * 5-2;
	viewCut.pY =  tan(fovY * PI / 360 + theta0) * 5+3;
	
	float theta1 = fovY * (1024.0f / 768) * PI / 180;
	viewCut.nX =  tan(theta1) * 5-2;
	viewCut.pX = -tan(theta1) * 5+2;
}

void
Camera::FreeFly(vec3 input, float dMouseX, float dMouseY, float speed)
{
	//this->up = normalize(cross(this->direction, this->right));
	//this->right = normalize(cross(this->up, this->direction));

	this->dirx -= dMouseX / 100;
	this->diry -= dMouseY / 100;

	// Lock y direction so it doesnt loop around
	if (this->diry > (PI / 2) - 0.1f)
		this->diry = (PI / 2) - 0.1f;
	if (this->diry < -(PI / 2) + 0.1f)
		this->diry = -(PI / 2) + 0.1f;

	this->direction = normalize(vec3(sin(dirx), tan(diry), cos(dirx)));

	//move
	this->position += 
		//forward
		this->direction * input.z * speed
		//right
		+ normalize(cross(this->direction, this->up)) * input.x * speed
		//up
		+ this->up * input.y * speed;

	this->view = lookat(this->position, this->position + this->direction, this->up);
}

void
Camera::Orbit(float speed, float height, float radius, float time)
{
	this->position.x = sin(time * speed) * radius;
	this->position.y = height;
	this->position.z = cos(time * speed) * radius;


	this->view = lookat(this->position, vec3(0, 0, 0), this->up);
}

void 
Camera::Follow(vec3 target, vec3 offset, float dt)
{
	this->position = Lerp(this->position, target + offset, dt*10);

	this->direction = normalize(target - this->position);

	this->view = lookat(this->position, target, this->up);

	projView = projection * view;
}

void Camera::ChangePerspective(Projection proj)
{
	switch (proj)
	{
	case persp:
		this->projection = perspective(90 * PI / 180, 1024.0f / 768, 0.1f, 100);
		break;
	case ortho:
		this->projection = orthographic(1024.0f / 768.0f, 1, 0.1f, 100.0f);
		break;
	default:
		break;
	}

}
