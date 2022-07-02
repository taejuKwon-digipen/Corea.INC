#include "Input.h"
#include "Engine.h"		//GetInput

Input::Input() {
	keyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
	wasKeyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
	mouseDown.resize(static_cast<int>(InputMouse::Mouse::Count));
	wasMouseDown.resize(static_cast<int>(InputMouse::Mouse::Count));
}

bool Input::IsKeyDown(InputKey::Keyboard key) const {
	return keyDown[static_cast<int>(key)];
}

bool Input::IsKeyReleased(InputKey::Keyboard key) const {
	return keyDown[static_cast<int>(key)] == false && wasKeyDown[static_cast<int>(key)] == true;
}

void Input::SetKeyDown(InputKey::Keyboard key, bool value) {
	keyDown[static_cast<int>(key)] = value;
}

bool Input::IsMouseClicked(InputMouse::Mouse key) const {
	return mouseDown[static_cast<int>(key)];
}

bool Input::IsMouseReleased(InputMouse::Mouse key) const {
	return mouseDown[static_cast<int>(key)] == false && wasMouseDown[static_cast<int>(key)] == true;
}

void Input::SetMouseDown(InputMouse::Mouse key, bool value) {
	mouseDown[static_cast<int>(key)] = value;
}

void Input::Update() {
	wasKeyDown = keyDown;
	wasMouseDown = mouseDown;
}

InputKey::InputKey(InputKey::Keyboard button) : button(button) {}

bool InputKey::IsKeyDown() const {
	return Engine::GetInput().IsKeyDown(button);
}

bool InputKey::IsKeyReleased() const {
	return Engine::GetInput().IsKeyReleased(button);
}


InputMouse::InputMouse(InputMouse::Mouse button) : button(button) {}

bool InputMouse::IsMouseClicked() const {
	return Engine::GetInput().IsMouseClicked(button);
}

bool InputMouse::IsMouseReleased() const {
	return Engine::GetInput().IsMouseReleased(button);
}