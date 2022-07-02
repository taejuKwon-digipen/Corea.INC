#pragma once
#include "../Engine/GameObject.h"
//#include "../Engine/Vec2.h"
#include "../Engine/Texture.h"
#include <filesystem>

class Button: public coconut::Component
{
private:
	struct Buttons
	{
		glm::ivec2 buttonLocation;
		coconut::Texture* startButton;
		coconut::Texture* endButton;
		bool mouseIsOver;
	};
	std::vector<Buttons> buttonVec;

public:
	Button();
	void Add(glm::ivec2 pos, const char* begin, const char* end, bool butBool);
	void Draw(int numb);
	void Unload();
	glm::ivec2 Size();
	bool GetBool(int numb);
	bool didClickButton();

private:
	bool mouseWasPressed = false;
	bool mouseIsOver = false;
	
};