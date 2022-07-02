#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Vec2.h"
#include "../Engine/Texture.h"
#include "../../library/include/doodle/input.hpp"
#include <filesystem>

class Button: public Component
{
private:
	struct Buttons
	{
		math::ivec2 buttonLocation;
		Texture* startButton;
		Texture* endButton;
		bool mouseIsOver;
	};
	std::vector<Buttons> buttonVec;

public:
	Button();
	void Add(math::ivec2 pos, const std::filesystem::path& start, const std::filesystem::path& end, bool butBool);
	void Draw(int numb);
	void Unload();
	math::ivec2 Size();
	bool GetBool(int numb);
	bool didClickButton();

private:
	bool mouseWasPressed = false;
	bool mouseIsOver = false;
	
};