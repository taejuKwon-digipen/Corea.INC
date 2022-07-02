#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Sprite.h"
#include "../../library/include/doodle/input.hpp"
#include "../../library/include/doodle/image.hpp"
#include "../../library/include/doodle/drawing.hpp"
#include "Hero.h"
#include "../Engine/Rect.h"
#include "../Engine/ComponentManager.h"
#include "Music.h"

// position x, y is center of the button

class Potion : public Component {
public:
	Potion() = default;
	Potion(math::vec2 position, int stat, std::filesystem::path potion1, std::filesystem::path potion2);
	void Update(double dt);
	bool didClicked();
	void Draw();
	
	Hero::herostat GetStat();
	bool IsChoiced();
	void makeUnchoiced();

private:
	Texture* potionPtr;
	Texture* potionPtr1;

	math::vec2 position;
	math::rect2 potionRect;

	int stat;

	bool ismouseover = false;
	bool ischoiced = false;
	bool isclicked = false;
	bool wasclicked = false;

	//Music sound;
};