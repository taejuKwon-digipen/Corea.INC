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


class Item_First : public GameState {
public:
	Item_First(Hero* hero);
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	std::string GetName() override;

	void ShowStats();
	std::vector<Hero::herostat> GetInput();
	std::vector<Hero::herostat> GetAnswer();
	bool isCleared();
	void changeStatus();
	bool isFinished();
	void beakerChange();

	void getLevel(int level);
	void clearVector();

private:
	int level;

	std::vector<Hero::herostat> input;
	std::vector<Hero::herostat> answer;
	bool iscleared = false;
	bool isdone = false;

	bool isfinished = false;

	Hero* hero;
	InputKey escape;
	InputKey next_description;

	Texture statsTexture;
	std::vector<Potion*> potionVec;

	Texture* description1;
	Texture* description2;
	Texture* description3;
	Texture* guidebook_open;

	Texture* herostat;

	int descriptionno;

	bool part1;

	bool litter3;
	bool litter5;

	std::vector<Beaker*> beakerVec;

	Texture HPTexture;
	Texture PowerTexture;
	Texture DefenceTexture;
	Texture LuckTexture;
	Texture IntelTexture;

	Music sound;
};