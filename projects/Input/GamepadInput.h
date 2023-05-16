#pragma once 

#include "GLFW/glfw3.h"
#include <iostream>
#include "core/math/mat4.h"
namespace Input
{
	class Gamepad
	{
		int gp_ID;

	public:
		vec3 leftStick , rightStick;
		bool trigger;

		Gamepad(){}

		void Update()
		{
			gp_ID = glfwJoystickPresent(GLFW_JOYSTICK_1);
			AxisValue();
		}

		void AxisValue()
		{
			if (gp_ID == 0)
				return;

			int axesCount;
			const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

			leftStick.x = axes[0]; leftStick.y = axes[1];

			rightStick.x = axes[2]; rightStick.y = axes[3];

			trigger = (axes[4] > 0.5 || axes[5] > 0.5);
		}

	};
}