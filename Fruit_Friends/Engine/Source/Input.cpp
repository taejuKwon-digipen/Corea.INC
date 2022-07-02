#include "../Header/Engine.h"
#include "../Header/Input.h"

using namespace coconut;

Input::Input() {
	currentKey.resize((int)InputKey::KeyboardButtons::Count);
	pastKey.resize((int)InputKey::KeyboardButtons::Count);
}

bool Input::IsKeyDown(InputKey::KeyboardButtons key) const {
	return currentKey[(int)key];
}

bool Input::IsKeyReleased(InputKey::KeyboardButtons key) const {
	return currentKey[(int)key] == false && pastKey[(int)key] == true;
}

void Input::SetKeyDown(InputKey::KeyboardButtons key, bool value) {
	currentKey[static_cast<int>(key)] = value;
}

bool Input::IsMouseClicked(InputMouse::MouseButtons button) const {
	return currentMouse[(int)button];
}

bool Input::IsMouseReleased(InputMouse::MouseButtons button) const {
	return currentMouse[(int)button] == false && pastMouse[(int)button] == true;
}

void Input::SetMouseDown(InputMouse::MouseButtons button, bool value) {
	currentMouse[(int)button] = value;
}

void Input::Update() {
	pastKey = currentKey;
	pastMouse = currentMouse;
}

InputKey::InputKey(InputKey::KeyboardButtons button) { this->button = button; }

bool InputKey::IsKeyDown() const {
	return Engine::GetInput().IsKeyDown(button);
}

bool InputKey::IsKeyReleased() const {
	return Engine::GetInput().IsKeyReleased(button);
}

InputMouse::InputMouse(InputMouse::MouseButtons button) { this->button = button; }

bool InputMouse::IsMouseClicked() const {
	return Engine::GetInput().IsMouseClicked(button);
}

bool InputMouse::IsMouseReleased() const {
	return Engine::GetInput().IsMouseReleased(button);
}