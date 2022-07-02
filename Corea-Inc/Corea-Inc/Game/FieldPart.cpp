#include "FieldPart.h"
#include "Background.h"
#include "Fonts.h"
#include "Screens.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObject.h"
#include "../Engine/GameObjectManager.h"
#include "Button.h"
#include "../Engine/TextureManager.h"
#include "../Engine/Texture.h"

#include<iostream>
#include <numeric>

FieldPart::FieldPart(FieldHero& hero) :
	hero(hero), stageNum(stageNum), title(), GOM(), mainGame(InputKey::KeyboardButtons::Escape), instNext(InputKey::KeyboardButtons::Enter), showInstruction(true), showIns(0)
{
	stageNum = 1;
	npc = nullptr;
	workerptr = nullptr;
	npc_timer = 0;
	main_timer = 100;
}

void FieldPart::Load()
{
	AddGSComponent(new Background());
	GetGSComponent<Background>()->Add("assets/FieldPart/FieldBackground.png");

	//have t omake getspritefont
	title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Field Part", 0xFFFFFFFF, true);
	glm::ivec2 winSize = Engine::GetWindow().GetSize() / 2;

	coconut::SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));
	boredTexture = font.DrawTextToTexture("BORING: " + std::to_string(bored_num), 0xFFFFFFFF, true);
	douptTexture = font.DrawTextToTexture("DOUPTING: " + std::to_string(doupt_num), 0xFFFFFFFF, true);
	tiredTexture = font.DrawTextToTexture("TIRED: " + std::to_string(tired_num), 0xFFFFFFFF, true);

	timerTexture = font.DrawTextToTexture("Timer: " + std::to_string(timer), 0xFFFFFFFF, true);

	Button* button = new Button();
	AddGSComponent(button);
	button->Add(glm::ivec2((double)Engine::GetWindow().GetSize().x * (double)0.77, (double)Engine::GetWindow().GetSize().y * 0.66),
		"assets/FieldPart/Button/NB1.png", "assets/FieldPart/Button/NB0.png", false);
	button->Add(glm::ivec2((double)Engine::GetWindow().GetSize().x * (double)0.13, (double)Engine::GetWindow().GetSize().y * 0.13),
		"assets/FieldPart/Button/F1.png", "assets/FieldPart/Button/F0.png", false);
	button->Add(glm::ivec2((double)Engine::GetWindow().GetSize().x * (double)0.77, (double)Engine::GetWindow().GetSize().y * 0.13),
		"assets/FieldPart/Button/IB1.png", "assets/FieldPart/Button/IB0.png", false);


	GOM = new coconut::GameObjectManager();
	AddGSComponent(GOM);

	GOM->Add(new FieldHero({700,400}));
	npc = new NPC({ 0.0,0.0 });
	GOM->Add(npc);
	item = new ITEM({ 0.0,0.0 });
	GOM->Add(item);
	fix = new FIX({ 0.0,0.0});
	GOM->Add(fix);

	sound.walking();
	inst1 = Engine::GetTextureManager().Load("assets/FieldPart/FieldInstruction1.png");
	inst2 = Engine::GetTextureManager().Load("assets/FieldPart/FieldInstruction2.png");

}

void FieldPart::Update(double dt)
{
	GOM->Update(dt);
	UpdateGSComponents(dt);
	hero.check_status(&hero);

	if (mainGame.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
	}

	if (instNext.IsKeyReleased() == true)
	{
		showIns++;
		if (showIns > 2) {
			showInstruction = false;
		}
	}

	coconut::SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));
	//scoreTexture = font.DrawTextToTexture("Score: " + std::to_string(score_num), 0xFFFFFFFF, true);

	boredTexture = font.DrawTextToTexture("BORING: " + std::to_string(bored_num), 0xFFFFFFFF, true);
	douptTexture = font.DrawTextToTexture("DOPTING: " + std::to_string(doupt_num), 0xFFFFFFFF, true);
	tiredTexture = font.DrawTextToTexture("TIRED: " + std::to_string(tired_num), 0xFFFFFFFF, true);
	timerTexture = font.DrawTextToTexture("Timer: " + std::to_string(timer), 0xFFFFFFFF, true);

	main_timer -= dt;
	scoretimer -= dt;

	if (main_timer <= 0)
	{
		if (doupt_num >= 5)
		{
			doupt_num++;
		}
		bored_num++;
		//doupt_num++;
		tired_num++;
		timer--;
		main_timer = 100;
	}

	if (timer == 7 && doupt_num == 0)
	{
		doupt_num = 5;
	}

	if (npc->for_viewcheck == true)
	{
		InView();
		if (in_view == true && npc->update == true )
		{
			npcScore_num += 1;
			if (npcScore_num == 1)
			{
				score_change = true;
			}
		}

		in_view = false;
		in_circle = false;
	}
	if (hero.check_status(&hero) == 2 )
	{
		if (fix->mouse.MousePositionX() >= 200 && fix->mouse.MousePositionX() <= 350 &&
			fix->mouse.MousePositionY() >= 102 && fix->mouse.MousePositionY() <= 252 && 
			fix->mouse.IsMouseClicked())
		{
			fixisScore_num += 1;
			if (fixisScore_num == 1)
			{
				score_change = true;
			}	
		}
	}
	if (score_change == true)
	{
		bored_num -=2;
		tired_num += 1;
		score_change = false;
	}

	if (item->drawItem == true)
	{
		tired_change += 1;
		if (tired_change == 1)
		{
			tiredchange = true;
		}
	}

	if (tiredchange == true)
	{
		tired_num -= 5;
		doupt_num += 1;
		tiredchange = false;
	}

	if (fix->drawfix == true)
	{
		fix_change += 1;
		if (fix_change == 1)
		{
			fixchange = true;
		}
	}

	if (fixchange == true)
	{
		bored_num -= 1;
		doupt_num -= 4;
		fixchange = false;
	}

	if (timer == 0)
	{
		if (tired_num == 10 || doupt_num == 10 || bored_num == 10)
		{
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Lose));
		}
		else {
			/*heroforstat->setStat(Hero::herostat::hp, heroforstat->getStat(Hero::herostat::hp) - 30);
			heroforstat->setStat(Hero::herostat::intelligence, heroforstat->getStat(Hero::herostat::intelligence) - 40);
			heroforstat->setStat(Hero::herostat::attack, heroforstat->getStat(Hero::herostat::attack) + 20);*/
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
		}
	}
}
void FieldPart::Unload()
{
	ClearGSComponent();
}

void FieldPart::Draw()
{
	TransformMatrix Location;
	GetGSComponent<Background>()->Draw();
	GetGSComponent<Button>()->Draw(0);
	GetGSComponent<Button>()->Draw(1);
	GetGSComponent<Button>()->Draw(2);
	GetGSComponent<coconut::GameObjectManager>()->DrawAll(Location);

	scoreTexture.Draw(Location);
	boredTexture.Draw(TranslateMatrix(glm::ivec2{ 0, Engine::GetWindow().GetSize().y /2 - 100}));
	douptTexture.Draw(TranslateMatrix(glm::ivec2{ 0, Engine::GetWindow().GetSize().y / 2  }));
	tiredTexture.Draw(TranslateMatrix(glm::ivec2{ 0, Engine::GetWindow().GetSize().y / 2 + 100 }));
	timerTexture.Draw(TranslateMatrix(glm::ivec2{ 10, Engine::GetWindow().GetSize().y - 100}));

	coconut::math::TransformMatrix data{};
	GOM->DrawAll(data);

	if (showInstruction)
	{
		switch (showIns) {
		case 0:
			//have to make clear in window
			Engine::GetWindow().Clear(0.f, 0.f, 0.f, 0.46f);
			inst1->Draw(TranslateMatrix(glm::vec2{ Engine::GetWindow().GetSize().x / 2 - inst1->GetSize().x / 2.f, Engine::GetWindow().GetSize().y - inst1->GetSize().y /2.f }));
			break;

		case 1:
			Engine::GetWindow().Clear(0.f, 0.f, 0.f, 0.46f);
			inst2->Draw(TranslateMatrix(glm::vec2{ Engine::GetWindow().GetSize().x / 2 - inst2->GetSize().x / 2.f, Engine::GetWindow().GetSize().y - inst2->GetSize().y / 2.f }));
			break;
		}
	}
}

void FieldPart::InView()
{
	glm::vec2 HeroPos = {700,400};
	glm::vec2 PlayerPos = npc->endpos;
	float goaldistance = 400.f;
	 
	//°Å¸®
	float distance = sqrt((PlayerPos.x - HeroPos.x) * (PlayerPos.x - HeroPos.x) + (PlayerPos.y - HeroPos.y) * (PlayerPos.y - HeroPos.y));


	if (distance < goaldistance)
	{
		in_circle = true;
	}
	else {
		in_circle = false;
	}

	glm::vec2 direction = glm::vec2{400, 0};
	glm::vec2 A2 = { PlayerPos.x - HeroPos.x, PlayerPos.y - HeroPos.y };

	float hero_distance = sqrt((direction.x * direction.x) + (direction.y * direction.y));
	float player_distance = sqrt((A2.x * A2.x) + (A2.y * A2.y));

	float dot_value = (((direction.x * A2.x) + (direction.y * A2.y))/ (hero_distance * player_distance));


	if (dot_value >= cos(angle/2) && in_circle == true) {
		in_view = true;
	}
	else
	{
		in_view = false;
	}

}
