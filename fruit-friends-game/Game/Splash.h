#pragma once
#include "..\Engine\GameState.h"

class Texture;

class Splash : public GameState {
public:
	Splash();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Splash"; }
private:
	double timer;
	const int DISPLAY_TIME = 3;
	Texture* texturePtr;
};

