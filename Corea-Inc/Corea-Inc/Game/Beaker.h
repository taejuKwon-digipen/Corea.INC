#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Sprite.h"
#include "Hero.h"
#include "../Engine/Rect.h"
#include "Music.h"

class Beaker : public coconut::Component {
public:
	Beaker() = default;
	Beaker(glm::vec2 pos, int littersize, std::vector<const char*> beaker1, std::vector<const char*> beaker2);
	void Update(double dt);
	void Draw();
	bool didClicked();
	int getRemain();

	void Into(Beaker* beaker);
	int getLeft();
	int getSize();
	void makeUnchoiced();
	void updateRemain(int _remain);

	bool IsChoiced();

private:
	glm::vec2 position;
	coconut::math::rect2 beakerRect;

	std::vector<coconut::Texture*> beakerPtr;
	std::vector<coconut::Texture*> beakerPtr1;

	bool ismouseover = false;
	bool ischoiced = false;
	bool isclicked = false;
	bool wasclicked = false;

	int littersize;
	int remain;
	int left;

	Music sound;
};