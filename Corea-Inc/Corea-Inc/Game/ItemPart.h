//Juhong Mo

#pragma once
#include "../Engine/GameState.h"
#include "Button.h"
#include "Potion.h"
#include <vector>
#include "Hero.h"
#include "StatsforItems.h"
#include "../Engine/Sprite.h"
#include "Beaker.h"
#include "Music.h"


class Item_First : public coconut::GameState {
public:
	Item_First(Hero* hero, int stagenum);
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	std::string GetName() override;

	void ShowStats();
	std::vector<Hero::herostat> GetInput();
	std::vector<Hero::herostat> GetAnswer();
	bool isCleared();
	bool isDone();

private:
	int stagenum;

	std::vector<Hero::herostat> input;
	std::vector<Hero::herostat> answer;
	bool iscleared = false;
	bool isdone = false;

	Hero* hero;
	InputKey escape;
	InputKey next_description;

	coconut::Texture statsTexture;
	std::vector<Potion*> potionVec;

	coconut::Texture* description1;
	coconut::Texture* description2;
	coconut::Texture* description3;
	coconut::Texture* guidebook_open;

	int descriptionno;

	bool part1;

	bool litter3;
	bool litter5;

	std::vector<Beaker*> beakerVec;

	coconut::Texture HPTexture;
	coconut::Texture PowerTexture;
	coconut::Texture DefenceTexture;
	coconut::Texture LuckTexture;
	coconut::Texture IntelTexture;

	Music sound;
};