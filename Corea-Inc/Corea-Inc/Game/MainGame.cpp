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

MainGame::MainGame(Hero* hero) :
mainMenu(InputKey::KeyboardButtons::Escape), hero(hero)
{
	hero->setStat(Hero::herostat::intelligence, 10);
	hero->setStat(Hero::herostat::hp, 100);
	hero->setStat(Hero::herostat::luck, 10);
	hero->setStat(Hero::herostat::attack, 10); // attack == power
}

void MainGame::Load() {

	AddGSComponent(new Background());
	GetGSComponent<Background>()->Add("assets/mainGame.png");
	Button* buttonPtr = new Button();

	AddGSComponent(buttonPtr);

	buttonPtr->Add(glm::ivec2(Engine::GetWindow().GetSize().x / 2 - 120, Engine::GetWindow().GetSize().y * 0.58),
		"assets/HR0.png", "assets/HR1.png", false);
	buttonPtr->Add(glm::ivec2(Engine::GetWindow().GetSize().x / 2 - 120, Engine::GetWindow().GetSize().y * 0.33),
		"assets/EN0.png", "assets/EN1.png", false);
	buttonPtr->Add(glm::ivec2(Engine::GetWindow().GetSize().x / 2 + 240, Engine::GetWindow().GetSize().y * 0.58),
		"assets/IT0.png", "assets/IT1.png", false);
	buttonPtr->Add(glm::ivec2(Engine::GetWindow().GetSize().x / 2 + 240, Engine::GetWindow().GetSize().y * 0.33),
		"assets/FI0.png", "assets/FI1.png", false);

	//statanm_->changestats(Hero::herostat::intelligence, 10);
	//statanm_->changestats(Hero::herostat::hp, 100);
	//statanm_->changestats(Hero::herostat::luck, 10);
	//statanm_->changestats(Hero::herostat::attack, 10); // attack == power

	coconut::SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));

	HPTexture = font.DrawTextToTexture("HP: " + std::to_string(hero->getStat(Hero::herostat::hp)), 0xFFFFFFFF, true);
	PowerTexture = font.DrawTextToTexture("POWER: " + std::to_string(hero->getStat(Hero::herostat::attack)), 0xFFFFFFFF, true);
	LuckTexture = font.DrawTextToTexture("LUCK: " + std::to_string(hero->getStat(Hero::herostat::luck)), 0xFFFFFFFF, true);
	IntelTexture = font.DrawTextToTexture("INT: " + std::to_string(hero->getStat(Hero::herostat::intelligence)), 0xFFFFFFFF, true);

	sfx.typing();
	sfx.walking();

	HRTexture = Engine::GetTextureManager().Load("assets/HRdone.png");
	statx = Engine::GetTextureManager().Load("assets/stat/statx.PNG");
}

void MainGame::Update(double)
{
	coconut::SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));

	HPTexture = font.DrawTextToTexture("HP: " + std::to_string(hero->getStat(Hero::herostat::hp)), 0xFFFFFFFF, true);
	PowerTexture = font.DrawTextToTexture("POWER: " + std::to_string(hero->getStat(Hero::herostat::attack)), 0xFFFFFFFF, true);
	LuckTexture = font.DrawTextToTexture("LUCK: " + std::to_string(hero->getStat(Hero::herostat::luck)), 0xFFFFFFFF, true);
	IntelTexture = font.DrawTextToTexture("INT: " + std::to_string(hero->getStat(Hero::herostat::intelligence)), 0xFFFFFFFF, true);

	if (mainMenu.IsKeyReleased() == true)
	{
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}

	if (GetGSComponent<Button>()->GetBool(0) == true)
	{
		sfx.TYPING.play();
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::HumanResources));
		hero->setStat(Hero::herostat::intelligence, hero->getStat(Hero::herostat::intelligence) + 10);
		hero->setStat(Hero::herostat::luck, hero->getStat(Hero::herostat::luck) + 10);

		/*statanm_->changestats(Hero::herostat::intelligence, hero->getStat(Hero::herostat::intelligence) + 10);
		statanm_->changestats(Hero::herostat::luck, hero->getStat(Hero::herostat::luck) + 10);*/
	}
	else if (GetGSComponent<Button>()->GetBool(1) == true)
	{
		sfx.TYPING.play();
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::Enemy));
	}
	else if (GetGSComponent<Button>()->GetBool(2) == true)
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
	else if (GetGSComponent<Button>()->GetBool(3) == true)
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
	GetGSComponent<Button>()->Draw(3);

	statx->Draw(coconut::math::TranslateMatrix{ glm::vec2(20, 40)});
	/*statanm_->Draw(math::TranslateMatrix{ math::vec2(20, 60) });*/
	HPTexture.Draw(coconut::math::TranslateMatrix(glm::ivec2{ 50, Engine::GetWindow().GetSize().y / 2 - 150 }));
	PowerTexture.Draw(coconut::math::TranslateMatrix(glm::ivec2{ 50, Engine::GetWindow().GetSize().y / 2 -210 }));
	LuckTexture.Draw(coconut::math::TranslateMatrix(glm::ivec2{ 50, Engine::GetWindow().GetSize().y / 2 - 270 }));
	IntelTexture.Draw(coconut::math::TranslateMatrix(glm::ivec2{ 50, Engine::GetWindow().GetSize().y / 2 -330 }));
	
	if (showHRCheck)
	{
		HRTexture->Draw(coconut::math::TranslateMatrix{ glm::vec2(Engine::GetWindow().GetSize().x / 2 - 120, Engine::GetWindow().GetSize().y * 0.58) });
	}
}
