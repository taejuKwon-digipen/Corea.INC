#include "../Header/Input.h"
#include "../Header/Engine.h"

InputKey::KeyboardButtons ConvertKey(int glkey) {
	if (glkey == GLFW_KEY_ENTER) {
		return InputKey::KeyboardButtons::Enter;
	} if (glkey == GLFW_KEY_ESCAPE) {
		return InputKey::KeyboardButtons::Escape;
	} if (glkey == GLFW_KEY_SPACE) {
		return InputKey::KeyboardButtons::Space;
	} if (glkey == GLFW_KEY_UP) {
		return InputKey::KeyboardButtons::Up;
	} if (glkey == GLFW_KEY_DOWN) {
		return InputKey::KeyboardButtons::Down;
	} if (glkey == GLFW_KEY_RIGHT) {
		return InputKey::KeyboardButtons::Right;
	} if (glkey == GLFW_KEY_LEFT) {
		return InputKey::KeyboardButtons::Left;
	} if (glkey >= GLFW_KEY_A && glkey <= GLFW_KEY_Z) {
		int offset = glkey - GLFW_KEY_A;
		return static_cast<InputKey::KeyboardButtons>(static_cast<int>(InputKey::KeyboardButtons::A) + offset);
	}
	return InputKey::KeyboardButtons::None;
}

InputMouse::MouseButtons ConvertMouse(int glmouse) {
	switch (glmouse) {
	case GLFW_MOUSE_BUTTON_LEFT:
		return InputMouse::MouseButtons::Left;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		return InputMouse::MouseButtons::Middle;

	case GLFW_MOUSE_BUTTON_RIGHT:
		return InputMouse::MouseButtons::Right;
	}
	return InputMouse::MouseButtons::None;
}

void Input::key_callback(GLFWwindow* window, int glkey) const {
	if (glfwGetKey(window, glkey) == GLFW_PRESS) {
		switch (glkey)
		{
		case GLFW_KEY_ENTER: [[fallthrough]];
		case GLFW_KEY_ESCAPE: [[fallthrough]];
		case GLFW_KEY_SPACE: [[fallthrough]];
		case GLFW_KEY_LEFT: [[fallthrough]];
		case GLFW_KEY_UP: [[fallthrough]];
		case GLFW_KEY_RIGHT: [[fallthrough]];
		case GLFW_KEY_DOWN:
			Engine::GetInput().SetKeyDown(ConvertKey(glkey), true);
			break;
		}
		if (glkey >= GLFW_KEY_A && glkey <= GLFW_KEY_Z)
		{
			int offset = glkey - GLFW_KEY_A;
			Engine::GetInput().SetKeyDown(ConvertKey(glkey), true); // is it okay just like this?
		}
	}
	if (glfwGetKey(window, glkey) == GLFW_RELEASE) {
		switch (glkey)
		{
		case GLFW_KEY_ENTER: [[fallthrough]];
		case GLFW_KEY_ESCAPE: [[fallthrough]];
		case GLFW_KEY_SPACE: [[fallthrough]];
		case GLFW_KEY_LEFT: [[fallthrough]];
		case GLFW_KEY_UP: [[fallthrough]];
		case GLFW_KEY_RIGHT: [[fallthrough]];
		case GLFW_KEY_DOWN:
			Engine::GetInput().SetKeyDown(ConvertKey(glkey), false);
			break;
		}
		if (glkey >= GLFW_KEY_A && glkey <= GLFW_KEY_Z)
		{
			int offset = glkey - GLFW_KEY_A;
			Engine::GetInput().SetKeyDown(ConvertKey(glkey), false); // is it okay just like this? maybe...
		}
	}
}

void Input::mouse_callback(GLFWwindow* window, int glmouse) const {
	if (glfwGetMouseButton(window, glmouse) == GLFW_PRESS)
	{
		switch (glmouse)
		{
		case GLFW_MOUSE_BUTTON_RIGHT: [[fallthrough]];
		case GLFW_MOUSE_BUTTON_MIDDLE: [[fallthrough]];
		case GLFW_MOUSE_BUTTON_LEFT:
			Engine::GetInput().SetMouseDown(ConvertMouse(glmouse), true);
			break;
		}
	}
	if (glfwGetMouseButton(window, glmouse) == GLFW_RELEASE)
	{
		switch (glmouse)
		{
		case GLFW_MOUSE_BUTTON_RIGHT: [[fallthrough]];
		case GLFW_MOUSE_BUTTON_MIDDLE: [[fallthrough]];
		case GLFW_MOUSE_BUTTON_LEFT:
			Engine::GetInput().SetMouseDown(ConvertMouse(glmouse), false);
			break;
		}
	}
}

void on_key_pressed(int glkey) {
	InputKey::KeyboardButtons button = ConvertKey(glkey);
	if (button != InputKey::KeyboardButtons::None) {
		Engine::GetInput().SetKeyDown(button, true);
	}
}

void on_key_released(int glkey) {
	InputKey::KeyboardButtons button = ConvertKey(glkey);
	if (button != InputKey::KeyboardButtons::None) {
		Engine::GetInput().SetKeyDown(button, false);
	}
}

//void on_mouse_clicked(GLFWmousebuttonfun glbutton) {
//	InputMouse::MouseButtons button = ConvertMouse((int)glbutton);
//	if (button != InputMouse::MouseButtons::None) {
//		Engine::GetInput().SetMouseDown(button, true);
//	}
//}
//
//void on_mouse_released(GLFWmousebuttonfun glbutton) {
//	InputMouse::MouseButtons button = ConvertMouse((int)glbutton);
//	if (button != InputMouse::MouseButtons::None) {
//		Engine::GetInput().SetMouseDown(button, false);
//	}
//}