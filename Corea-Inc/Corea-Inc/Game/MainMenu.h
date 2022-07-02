#pragma once
#include "..\Engine\GameState.h"
#include "Button.h"
#include "Music.h"

class MainMenu : public coconut::GameState {
public:
	MainMenu();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "MainMenu"; }

	coconut::Image cutSceneImg{"assets/cutScene.png"};
	Music bgm;
	bool showCutscene;
	int texX = 0;
	int timer = 70;
};

