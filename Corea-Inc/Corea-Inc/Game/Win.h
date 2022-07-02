// Geonhwi Sim
#pragma once
#include "../Engine/Texture.h"
#include "../Engine/GameState.h"
#include "..\Engine\Input.h"

class Win : public coconut::GameState
{
public:
	Win();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Win"; }
private:
	InputKey exit;
};