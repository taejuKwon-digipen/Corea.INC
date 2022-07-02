// Geonhwi Sim

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "Background.h"
#include "Hero.h"
#include "Music.h"
#include "statanmset.h"
#include "HumanResources.h"
#include "ItemPart.h"

class MainGame : public GameState {
public:
	MainGame(Hero* hero, HumanResources* hr, Item_First* item);
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "MainGame"; }

	inline static bool showHRCheck{ false };

	int getProgress();
	int getLevel();

	void changeProgress();
	void setLevel();
	void changeLevel();

private:
	InputKey mainMenu;
	Texture* HRTexture;

	Texture HPTexture;
	Texture PowerTexture;
	Texture LuckTexture;
	Texture IntelTexture;
	Texture* statx;

	Texture LevelTexture;
	Texture ProgressTexture;

	int level;

	/*statanm* statanm_;*/

	Hero* hero;

	Item_First* item;

	Music sfx;

	int progress;

	bool item_clear;
	bool item_playable;
	bool hr_playable;

	int lastlevel;
	int currentlevel;
};


