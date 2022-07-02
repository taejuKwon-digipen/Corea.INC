#include "../../library/include/doodle/input.hpp"
#include "Input.h"
#include "Engine.h"			// Logger, Input

InputKey::Keyboard DoodleKeyToCS230Key(doodle::KeyboardButtons button) {
	if (button == doodle::KeyboardButtons::Enter) {
		return InputKey::Keyboard::Enter;
	} else if (button == doodle::KeyboardButtons::Escape) {
		return InputKey::Keyboard::Escape;
	} else if (button == doodle::KeyboardButtons::Space) {
		return InputKey::Keyboard::Space;
	} else if (button == doodle::KeyboardButtons::Left) {
		return InputKey::Keyboard::Left;
	} else if (button == doodle::KeyboardButtons::Right) {
		return InputKey::Keyboard::Right;
	} else if (button == doodle::KeyboardButtons::Up) {
		return InputKey::Keyboard::Up;
	} else if (button == doodle::KeyboardButtons::Down) {
		return InputKey::Keyboard::Down;
	} else if (button == doodle::KeyboardButtons::Tilde) {
		return InputKey::Keyboard::Tilde;
	} else if (button >= doodle::KeyboardButtons::A && button <= doodle::KeyboardButtons::Z) {
		int offset = static_cast<int>(button) - static_cast<int>(doodle::KeyboardButtons::A);
		return static_cast<InputKey::Keyboard>(static_cast<int>(InputKey::Keyboard::A) + offset);
	}
	return InputKey::Keyboard::None;
}

void on_key_pressed(doodle::KeyboardButtons doodleButton) {
	InputKey::Keyboard button = DoodleKeyToCS230Key(doodleButton);
	if (button != InputKey::Keyboard::None) {
		Engine::GetLogger().LogDebug("on_key_pressed");
		Engine::GetInput().SetKeyDown(button, true);
	}
}

void on_key_released(doodle::KeyboardButtons doodleButton) { //두들엔 릴리즈가 없어 그래서 내가 우리가 만든 엔진에는 릴리즈 있으니까 거기서 바로 하는게 어떻겠냐고 말했던거ㅇㅇ
	InputKey::Keyboard button = DoodleKeyToCS230Key(doodleButton);
	if (button != InputKey::Keyboard::None) {
		Engine::GetLogger().LogDebug("on_key_released");
		Engine::GetInput().SetKeyDown(button, false);
	}
}

InputMouse::Mouse DoodleMouseToProject(doodle::MouseButtons button) {
	if (button == doodle::MouseButtons::Left) {
		return InputMouse::Mouse::Left;
	}
	else if (button == doodle::MouseButtons::Right) {
		return InputMouse::Mouse::Right;
	}

	return InputMouse::Mouse::None;
}

void on_mouse_pressed(doodle::MouseButtons doodleButton) {
	InputMouse::Mouse button = DoodleMouseToProject(doodleButton);
	if (button != InputMouse::Mouse::None) {
		Engine::GetLogger().LogDebug("on_key_pressed");
		Engine::GetInput().SetMouseDown(button, true);
	}
}

void on_mouse_released(doodle::MouseButtons doodleButton) {
	InputMouse::Mouse button = DoodleMouseToProject(doodleButton);
	if (button != InputMouse::Mouse::None) {
		Engine::GetLogger().LogDebug("on_mouse_clicked");
		Engine::GetInput().SetMouseDown(button, false);
	}
}

double InputMouse::MousePositionX() {
	return doodle::get_mouse_x();
}

double InputMouse::MousePositionY() {
	return doodle::get_mouse_y();
}