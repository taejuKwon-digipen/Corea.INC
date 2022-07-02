#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Sprite.h"
#include "../../library/include/doodle/input.hpp"
#include "../../library/include/doodle/image.hpp"
#include "../../library/include/doodle/drawing.hpp"
#include "Hero.h"
#include "../Engine/Rect.h"
#include "Music.h"

class Beaker : public Component {
public:
	Beaker() = default;
	Beaker(math::vec2 pos, int littersize, std::vector<std::filesystem::path> beaker1, std::vector<std::filesystem::path> beaker2);
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
	math::vec2 position;
	math::rect2 beakerRect;

	std::vector<Texture*> beakerPtr;
	std::vector<Texture*> beakerPtr1;

	bool ismouseover = false;
	bool ischoiced = false;
	bool isclicked = false;
	bool wasclicked = false;

	int littersize;
	int remain;
	int left;

	Music sound;
};