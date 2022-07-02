// Geonhwi Sim

#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"

class HumanResources : public coconut::GameState
{
public:
	HumanResources();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	void CheckParts();
	void AnswerChecking();
	//void CheckClick(bool boolCheck, Texture* texCheck);

	std::string GetName() override { return "HumanResources"; }
private:
	coconut::Texture* inst1;
	coconut::Texture* inst2;
	coconut::Texture* inst3;
	bool showInstruction;
	int showIns;

	coconut::Texture* stamp;
	coconut::Texture* stampNotyet;

	coconut::Texture stageTex;

	InputKey mainGame;

	int chance = 4;
	int currLevel = 1;
	int stage = 0;

	bool was0Clicked = false;
	bool was1Clicked = false;
	bool was2Clicked = false;
	bool was3Clicked = false;
	bool setComplete = false;

	struct checkPart
	{
		bool HR;
		bool It;
		bool En;
		bool Fi;
	};

	std::vector<checkPart> checkVec;
	InputKey instNext;
};