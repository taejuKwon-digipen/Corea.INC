//Jihyeon Song

#pragma once
#include "FieldHero.h"
#include "FieldButton.h"
#include "UI.h"
#include "Background.h"
#include "FieldWorker.h"
#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Texture.h"
#include "Score.h"
#include "Music.h"
#include "Hero.h"

class GameObjectManager;

class FieldPart : public coconut::GameState
{
public:
	FieldPart(FieldHero& hero);
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	std::string GetName() override { return "FieldPart"; }

	void InView();

private:
	int stageNum; //1 to 3
	int npc_timer = 3;
	double main_timer = 0;
	bool gameover = false;
	double scoretimer = 150;
	int fix_change = 0;
	bool fixchange = false;

	bool score_change = false;
	int npcScore_num = 0;
	int itemisScore_num = 0;
	int fixisScore_num = 0;

	double PI = 3.141592653;
	double angle = PI / 3.f;
	bool in_circle = false;
	bool in_view = false;

	FieldHero& hero;
	NPC* npc;
	ITEM* item;
	FIX* fix;

	FieldWorker* workerptr;
	coconut::Texture title;
	coconut::Texture scoreTexture;
	coconut::Texture boredTexture;
	coconut::Texture douptTexture;
	coconut::Texture tiredTexture;
	coconut::Texture timerTexture;

	int score_num = 0;
	int bored_num = 0;
	int doupt_num = 0;
	int tired_num = 0;
	int timer = 12;

	int tired_change = 0;
	bool tiredchange = false;

	coconut::GameObjectManager* GOM;
	InputKey mainGame;
	coconut::Texture* inst1;
	coconut::Texture* inst2;
	Music sound;
	Hero* heroforstat;

	bool showInstruction;
	int showIns;
	InputKey instNext;
};