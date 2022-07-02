#pragma once
#include "../Engine/Header/Gamestate.h"
#include "../Engine/Header/Image.h"
#include "../fruit-friends-game/Engine/GameObject.h"

class Test : public coconut::GameState
{
public:
	Test();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Test"; }

private:
	coconut::Image img;
};