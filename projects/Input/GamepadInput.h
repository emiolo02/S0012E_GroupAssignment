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
		vec2 leftStick , rightStick;
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

			const float deadzone = 0.1f;

			int axesCount;
			const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
			vec2 rawLstick = vec2(axes[0], axes[1]);
			vec2 rawRstick = vec2(axes[2], axes[3]);

			leftStick = vec2();
			rightStick = vec2();

			if (length(rawLstick) > deadzone)
				leftStick = rawLstick;

			if (length(rawRstick) > deadzone)
				rightStick = rawRstick;

			trigger = (axes[4] > 0.5 || axes[5] > 0.5);
		}
	};
}