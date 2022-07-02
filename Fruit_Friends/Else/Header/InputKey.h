#pragma once

class 
	board {
private:
public:
	// void KeyboardButton();

	void glutKeyboardFunc(void (*func)(unsigned char key, int x, int y));
	void glutSpecialFunc(void (*func)(int key, int x, int y));
};