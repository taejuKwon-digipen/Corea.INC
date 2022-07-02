#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Sprite.h"
#include "Hero.h"
#include "../Engine/Rect.h"
#include "../Engine/ComponentManager.h"
#include "Music.h"

class Potion : public coconut::Component {
public:
	Potion() = default;
	Potion(glm::vec2 position, int stat, const char* potion1, const char* potion2);
	void Update(double dt);
	bool didClicked();
	void Draw();
	
	Hero::herostat GetStat();
	bool IsChoiced();
	void makeUnchoiced();

private:
	coconut::Texture* potionPtr;
	coconut::Texture* potionPtr1;

	glm::vec2 position;
	coconut::math::rect2 potionRect;

	int stat;

	bool ismouseover = false;
	bool ischoiced = false;
	bool isclicked = false;
	bool wasclicked = false;

	Music sound;
};