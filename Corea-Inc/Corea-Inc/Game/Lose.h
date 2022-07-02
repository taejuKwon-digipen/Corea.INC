// Geonhwi Sim
#pragma once
#include "../Engine/Texture.h"
#include "../Engine/GameState.h"
#include "..\Engine\Input.h"

class Lose : public coconut::GameState
{
public:
	Lose();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Lose"; }
private:
	coconut::Texture* Bg;

	InputKey exit;
};