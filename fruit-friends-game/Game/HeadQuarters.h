// Geonhwi Sim

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"

class HeadQuarters : public GameState
{
public:
	HeadQuarters();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Head Quarters"; }
private:
	Texture title;
	InputKey mainGame;
};