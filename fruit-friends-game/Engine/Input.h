#pragma once
#include <vector>

class InputKey {
public:
	enum class Keyboard {
		None, Enter, Escape, Space, Left, Up, Right, Down,
		A, B, C, D, E, F, G, H, I, J,
		K, L, M, N, O, P, Q, R, S, T,
		U, V, W, X, Y, Z, Tilde,
		Count
	};

	InputKey(Keyboard button);
	bool IsKeyDown() const;
	bool IsKeyReleased() const;
private:
	Keyboard button;
};

class InputMouse {
public:
	enum class Mouse {
		None, Left, Right, Count
	};

	InputMouse(Mouse button);
	bool IsMouseClicked() const;
	bool IsMouseReleased() const;
	double MousePositionX();
	double MousePositionY();
private:
	Mouse button;
};

class Input {
public:
	Input();
	bool IsKeyDown(InputKey::Keyboard key) const;
	bool IsKeyReleased(InputKey::Keyboard key) const;
	void SetKeyDown(InputKey::Keyboard key, bool value);
	bool IsMouseClicked(InputMouse::Mouse key) const;
	bool IsMouseReleased(InputMouse::Mouse key) const;
	void SetMouseDown(InputMouse::Mouse key, bool value);

	void Update();
private:
	std::vector<bool> keyDown;
	std::vector<bool> wasKeyDown;
	std::vector<bool> mouseDown;
	std::vector<bool> wasMouseDown;
};