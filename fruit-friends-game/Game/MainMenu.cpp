// Geonhwi Sim
#include "../../library/include/doodle/drawing.hpp"
#include "../Engine/Engine.h"	//GetGameStateManager GetSpriteFont
#include "../Engine/TransformMatrix.h"
#include "Screens.h"
#include "MainMenu.h"

#include <iostream>

#include "Background.h"
#include "Button.h"
#include "../Engine/GameObjectManager.h"
#include "Fonts.h"
MainMenu::MainMenu() : showCutscene(true)
{}

void MainMenu::Load() {
	AddGSComponent(new Background());
	GetGSComponent<Background>()->Add("assets/Background.png");
	Button* buttonPtr = new Button();
	AddGSComponent(buttonPtr);
	buttonPtr->Add(math::ivec2(Engine::GetWindow().GetSize().x / 2 - 70, Engine::GetWindow().GetSize().y * 0.28),
		"assets/start0Button.png", "assets/start1Button.png", false);
	buttonPtr->Add(math::ivec2(Engine::GetWindow().GetSize().x / 2 - 70, Engine::GetWindow().GetSize().y * 0.15),
		"assets/quit0Button.png", "assets/quit1Button.png", false);

		bgm.mainmenu_bgm();
		bgm.portal();
}

void MainMenu::Update(double) {
	timer--;
	if (timer < 0)
	{
		timer = 70;
		texX += 1440;
		if (texX >= 11520)
		{
			showCutscene = false;
		}
	}
	bgm.mainmenu_bgm();
	bgm.MAINMENU_BGM.play();
	bgm.MAINMENU_BGM.setLoop(true);
	
	if (GetGSComponent<Button>()->GetBool(0) == true)
	{
		bgm.PORTAL.play();
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
	}
	else if (GetGSComponent<Button>()->GetBool(1) == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}
}

void MainMenu::Unload()
{
	bgm.MAINMENU_BGM.stop();
	ClearGSComponent();
}

void MainMenu::Draw() {
	if (showCutscene == true)
	{
		draw_image(cutSceneImg, texX, 0);
	}
	else {
		GetGSComponent<Background>()->Draw();

		GetGSComponent<Button>()->Draw(0);
		GetGSComponent<Button>()->Draw(1);
	}
}