// Geonhwi Sim

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "Screens.h"
#include "MainGame.h"
#include "Fonts.h"
#include <iostream>
#include "Background.h"
#include "Button.h"

static int HP_num = 100;
static int Power_num = 10;
static int Luck_num = 10;
static int Intel_num = 10;

math::ivec2 hrbuttonpos ;
math::ivec2 itembuttonpos ;
math::ivec2 fieldbuttonpos;

MainGame::MainGame(Hero* hero, HumanResources* hr, Item_First* item) :
mainMenu(InputKey::Keyboard::Escape), hero(hero), item(item), level(level)
{
	hero->setStat(Hero::herostat::intelligence, 10);
	hero->setStat(Hero::herostat::hp, 100);
	hero->setStat(Hero::herostat::luck, 10);
	hero->setStat(Hero::herostat::attack, 10); // attack == power

	level = 1;
	progress = 0;

	hr_playable = true;
	item_playable = true;
	item_clear = false;

	item->getLevel(level);
}

void MainGame::Load() {
	hrbuttonpos = math::ivec2(Engine::GetWindow().GetSize().x / 2 + 180, Engine::GetWindow().GetSize().y * 0.66);
	itembuttonpos = math::ivec2(Engine::GetWindow().GetSize().x / 2 + 180, Engine::GetWindow().GetSize().y * 0.40);
	fieldbuttonpos = math::ivec2(Engine::GetWindow().GetSize().x / 2 + 180, Engine::GetWindow().GetSize().y * 0.14);


	AddGSComponent(new Background());
	GetGSComponent<Background>()->Add("assets/mainGame.png");
	Button* buttonPtr = new Button();

	AddGSComponent(buttonPtr);
	buttonPtr->Add(hrbuttonpos, "assets/HR0.png", "assets/HR1.png", false);
	buttonPtr->Add(itembuttonpos, "assets/IT0.png", "assets/IT1.png", false);
	buttonPtr->Add(fieldbuttonpos, "assets/FI0.png", "assets/FI1.png", false);

	//statanm_->changestats(Hero::herostat::intelligence, 10);
	//statanm_->changestats(Hero::herostat::hp, 100);
	//statanm_->changestats(Hero::herostat::luck, 10);
	//statanm_->changestats(Hero::herostat::attack, 10); // attack == power
	
	/*

	SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));

	HPTexture = font.DrawTextToTexture("HP: " + std::to_string(hero->getStat(Hero::herostat::hp)), 0xFFFFFFFF, true);
	PowerTexture = font.DrawTextToTexture("POWER: " + std::to_string(hero->getStat(Hero::herostat::attack)), 0xFFFFFFFF, true);
	LuckTexture = font.DrawTextToTexture("LUCK: " + std::to_string(hero->getStat(Hero::herostat::luck)), 0xFFFFFFFF, true);
	IntelTexture = font.DrawTextToTexture("INT: " + std::to_string(hero->getStat(Hero::herostat::intelligence)), 0xFFFFFFFF, true);

	LevelTexture = font.DrawTextToTexture("Level : " + std::to_string(level), 0xFFFFFFFF, false);
	ProgressTexture = font.DrawTextToTexture("Progress : " + std::to_string(progress), 0xFFFFFFFF, false);*/

	sfx.typing();
	sfx.walking();

	HRTexture = Engine::GetTextureManager().Load("assets/HRdone.png");
	statx = Engine::GetTextureManager().Load("assets/stat/statx.PNG");
}

void MainGame::Update(double)
{/*
	SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));

	HPTexture = font.DrawTextToTexture("HP: " + std::to_string(hero->getStat(Hero::herostat::hp)), 0xFFFFFFFF, true);
	PowerTexture = font.DrawTextToTexture("POWER: " + std::to_string(hero->getStat(Hero::herostat::attack)), 0xFFFFFFFF, true);
	LuckTexture = font.DrawTextToTexture("LUCK: " + std::to_string(hero->getStat(Hero::herostat::luck)), 0xFFFFFFFF, true);
	IntelTexture = font.DrawTextToTexture("INT: " + std::to_string(hero->getStat(Hero::herostat::intelligence)), 0xFFFFFFFF, true);

	LevelTexture = font.DrawTextToTexture("Level : " + std::to_string(level), 0xFFFFFFFF, false);
	ProgressTexture = font.DrawTextToTexture("Progress : " + std::to_string(progress), 0xFFFFFFFF, false);*/


	if (mainMenu.IsKeyReleased() == true)
	{
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}

	if (GetGSComponent<Button>()->GetBool(0) == true && hr_playable == true)
	{
		sfx.TYPING.play();
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::HumanResources));
		hero->setStat(Hero::herostat::intelligence, hero->getStat(Hero::herostat::intelligence) + 10);
		hero->setStat(Hero::herostat::luck, hero->getStat(Hero::herostat::luck) + 10);

		/*statanm_->changestats(Hero::herostat::intelligence, hero->getStat(Hero::herostat::intelligence) + 10);
		statanm_->changestats(Hero::herostat::luck, hero->getStat(Hero::herostat::luck) + 10);*/
	}
	else if (GetGSComponent<Button>()->GetBool(1) == true && item_playable == true)
	{
		sfx.TYPING.play();
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::Item_First));
		hero->setStat(Hero::herostat::luck, hero->getStat(Hero::herostat::luck) + 30);
		hero->setStat(Hero::herostat::intelligence, hero->getStat(Hero::herostat::intelligence) + 20);
		hero->setStat(Hero::herostat::attack, hero->getStat(Hero::herostat::attack) + 10);
		hero->setStat(Hero::herostat::hp, hero->getStat(Hero::herostat::hp) - 10);

		/*statanm_->changestats(Hero::herostat::luck, hero->getStat(Hero::herostat::luck) + 30);
		statanm_->changestats(Hero::herostat::intelligence, hero->getStat(Hero::herostat::intelligence) + 20);
		statanm_->changestats(Hero::herostat::attack, hero->getStat(Hero::herostat::attack) + 10);
		statanm_->changestats(Hero::herostat::hp, hero->getStat(Hero::herostat::hp) - 10);*/
	}
	else if (GetGSComponent<Button>()->GetBool(2) == true)
	{
		sfx.TYPING.play();
		sfx.WALKING.play();
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::Fields));
		hero->setStat(Hero::herostat::hp, hero->getStat(Hero::herostat::hp) - 30);
		hero->setStat(Hero::herostat::intelligence, hero->getStat(Hero::herostat::intelligence) - 40);
		hero->setStat(Hero::herostat::attack, hero->getStat(Hero::herostat::attack) + 20);

		/*statanm_->changestats(Hero::herostat::hp, hero->getStat(Hero::herostat::hp) - 30);
		statanm_->changestats(Hero::herostat::intelligence, hero->getStat(Hero::herostat::intelligence) - 40);
		statanm_->changestats(Hero::herostat::attack, hero->getStat(Hero::herostat::attack) + 20);*/
	}
	
	if (item->isCleared() == true) {
		item_clear = true;
	}

	/*if (item->isFinished() == true) {
		int abc = 0;
	}*/

	//if (item->isFinished() == true) {
	//	item_playable = false;
	//}

	if (showHRCheck == true) {
		hr_playable = false;
	}
	
	if (item_playable == true && item->isFinished() == true) {
		changeProgress();
	}

	if (progress == 10) {
		changeLevel();
		setLevel();
	}
}

void MainGame::Unload()
{
	ClearGSComponent();
}

void MainGame::Draw() {
	GetGSComponent<Background>()->Draw();
	GetGSComponent<Button>()->Draw(0);
	GetGSComponent<Button>()->Draw(1);
	GetGSComponent<Button>()->Draw(2);

	statx->Draw(math::TranslateMatrix{ math::vec2(20, 40)});
	/*statanm_->Draw(math::TranslateMatrix{ math::vec2(20, 60) });*//*
	HPTexture.Draw(math::TranslateMatrix(math::ivec2{ 50, Engine::GetWindow().GetSize().y / 2 - 150 }));
	PowerTexture.Draw(math::TranslateMatrix(math::ivec2{ 50, Engine::GetWindow().GetSize().y / 2 -210 }));
	LuckTexture.Draw(math::TranslateMatrix(math::ivec2{ 50, Engine::GetWindow().GetSize().y / 2 - 270 }));
	IntelTexture.Draw(math::TranslateMatrix(math::ivec2{ 50, Engine::GetWindow().GetSize().y / 2 -330 }));

	LevelTexture.Draw(math::TranslateMatrix(math::ivec2(50, Engine::GetWindow().GetSize().y / 2 + 330)));
	ProgressTexture.Draw(math::TranslateMatrix(math::ivec2(50, Engine::GetWindow().GetSize().y / 2 + 270)));*/
	
	if (showHRCheck)
	{
		HRTexture->Draw(math::TranslateMatrix{ hrbuttonpos });
	}
}

int MainGame::getProgress() {
	return progress;
}

int MainGame::getLevel() {
	return level;
}

void MainGame::changeProgress() {
	std::vector<Hero::herostat>item_answer = item->GetAnswer();

	//if (item->isFinished() == true) {
	//	Engine::GetLogger().LogEvent("item finished!");

	//	if (item->isCleared() == true) {
	//		progress += 3;
	//		Engine::GetLogger().LogEvent("item cleared! progress : " + std::to_string(progress));
	//	}

	//	if (item->isCleared() == false) {
	//		Engine::GetLogger().LogEvent("item not cleared! progress : " + std::to_string(progress));
	//	}
	//	
	//	item_playable = false;
	//}

	if (item->isFinished() == true) {
		Engine::GetLogger().LogEvent("item finished!");

		if (item->GetInput() == item_answer) {
			progress += 10;
			Engine::GetLogger().LogEvent("item cleared! progress : " + std::to_string(progress));
			item_playable = false;
		}

		if (item->GetInput() != item_answer) {
			Engine::GetLogger().LogEvent("item not cleared! progress : " + std::to_string(progress));
			item_playable = true;
		}

		item->changeStatus();
	}

	if (showHRCheck == true) {
		progress += 3;
		Engine::GetLogger().LogEvent("human resource cleared! progress : " + std::to_string(progress));

		hr_playable = false;
	}

	Engine::GetLogger().LogEvent("Level\t| " + std::to_string(level));

	Engine::GetLogger().LogEvent("H P\t| " + std::to_string(hero->getStat(Hero::herostat::hp)));
	Engine::GetLogger().LogEvent("POW\t| " + std::to_string(hero->getStat(Hero::herostat::attack)));
	Engine::GetLogger().LogEvent("LUK\t| " + std::to_string(hero->getStat(Hero::herostat::luck)));
	Engine::GetLogger().LogEvent("INT\t| " + std::to_string(hero->getStat(Hero::herostat::intelligence)));

	Engine::GetLogger().LogEvent("Progress| " + std::to_string(progress));

	Engine::GetLogger().LogEvent("------------------------------------------");
}

void MainGame::setLevel() {
	lastlevel = level;
	currentlevel = level;
}

void MainGame::changeLevel() {
	lastlevel = level;
	level ++;
	currentlevel = level;
	progress = 0;

	item->changeStatus();
	item->getLevel(level);

	hr_playable = true;
	item_playable = true;

	Engine::GetLogger().LogEvent("Level\t| " + std::to_string(level));
	Engine::GetLogger().LogEvent("Progress| " + std::to_string(progress));
}