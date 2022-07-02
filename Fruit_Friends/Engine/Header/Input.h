#ifndef GLAPP_H
#define GLAPP_H

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include "glslshader.h"
#include <vector>

class InputKey {
public:
	enum class KeyboardButtons {
		None, Enter, Escape, Space, Left, Up, Right, Down,
		A, B, C, D, E, F, G, H, I, J,
		K, L, M, N, O, P, Q, R, S, T,
		U, V, W, X, Y, Z,
		Count
	};

	InputKey(KeyboardButtons button);
	bool IsKeyDown() const;
	bool IsKeyReleased() const;
private:
	KeyboardButtons button;
};

class InputMouse {
public:
	enum class MouseButtons {
		None, Left, Middle, Right, Count
	};

	InputMouse(MouseButtons button);
	bool IsMouseClicked() const;
	bool IsMouseReleased() const;
	//void setCursor(mutable GLFWimage img) const;

private:
	MouseButtons button;
	//int get_mouse_x();
	//int get_mouse_y();
};

class Input {
public:
	Input();
	bool IsKeyDown(InputKey::KeyboardButtons key) const;
	bool IsKeyReleased(InputKey::KeyboardButtons key) const;
	void key_callback(GLFWwindow* window, int glkey) const;
	void mouse_callback(GLFWwindow* window, int glkey) const;
	void SetKeyDown(InputKey::KeyboardButtons key, bool value);
	
	bool IsMouseClicked(InputMouse::MouseButtons button) const;
	bool IsMouseReleased(InputMouse::MouseButtons button) const;
	void SetMouseDown(InputMouse::MouseButtons button, bool value);
	void Update();

private:
	std::vector<bool> currentKey;
	std::vector<bool> pastKey;
	std::vector<bool> currentMouse;
	std::vector<bool> pastMouse;
};

#endif