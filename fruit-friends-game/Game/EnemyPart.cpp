// Geonhwi Sim

#include "EnemyPart.h"

#include "Background.h"
#include "Button.h"
#include "Fonts.h"
#include "Screens.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"

EnemyPart::EnemyPart() :
	mainGame{ InputKey::Keyboard::Escape }
{}

void EnemyPart::Load()
{
	AddGSComponent(new Background());
	GetGSComponent<Background>()->Add("assets/loseBG.png");
	Button* buttonPtr = new Button();
	AddGSComponent(buttonPtr);
	buttonPtr->Add(math::ivec2(Engine::GetWindow().GetSize().x / 2 + 350, Engine::GetWindow().GetSize().y * 0.15),
		"assets/quit0Button.png", "assets/quit1Button.png", false);
}

void EnemyPart::Update(double dt)
{
	if (mainGame.IsKeyReleased() == true)
	{
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
	}
	UpdateGSComponents(dt);
	if (GetGSComponent<Button>()->GetBool(0) == true)
	{
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
	}
}

void EnemyPart::Unload()
{
	ClearGSComponent();
}

void EnemyPart::Draw()
{
	math::TransformMatrix Location;
	//Bg->Draw(math::TranslateMatrix({ (Engine::GetWindow().GetSize() - Bg->GetSize()) / 2.0 }));
	GetGSComponent<Background>()->Draw();
	GetGSComponent<Button>()->Draw(0);
}
