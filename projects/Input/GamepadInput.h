#pragma once 

#include "GLFW/glfw3.h"
#include <iostream>
#include "core/math/mat4.h"
namespace Input
{
	struct Button
	{
		bool pressed;
		bool held;
		bool released;
	};

	class Gamepad
	{
		int gp_ID;
		bool lastBtnVal;
	public:
		vec2 leftStick, rightStick;
		bool trigger;
		Button Abtn;
		Gamepad() {}

		void Update()
		{
			gp_ID = glfwJoystickPresent(GLFW_JOYSTICK_1);
			AxisValue();
			ActionValue();
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

		void ActionValue()
		{
			int count;
			const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

			if (count == 0)
				return;

			bool btnVal = (bool)buttons[0];
			Abtn.pressed = false;
			Abtn.released = false;

			if (btnVal && !lastBtnVal)
			{
				Abtn.pressed = true;
			}
			if (!btnVal && lastBtnVal)
			{
				Abtn.released = true;
			}
			Abtn.held = btnVal;
			lastBtnVal = btnVal;

			if (!trigger)
				trigger = ((bool)buttons[6] || (bool)buttons[7]);
		}
	};
}