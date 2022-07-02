// Geonhwi Sim

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "Background.h"
#include "Hero.h"
#include "Music.h"
#include "statanmset.h"

class MainGame : public coconut::GameState {
public:
	MainGame(Hero* hero);
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "MainGame"; }

	inline static bool showHRCheck{ false };
private:
	InputKey mainMenu;
	coconut::Texture* HRTexture;

	coconut::Texture HPTexture;
	coconut::Texture PowerTexture;
	coconut::Texture LuckTexture;
	coconut::Texture IntelTexture;
	coconut::Texture* statx;

	/*statanm* statanm_;*/

	Hero* hero;

	Music sfx;
};


