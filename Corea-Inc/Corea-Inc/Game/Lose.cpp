// Geonhwi Sim
#include "Lose.h"
#include "Background.h"
#include "Button.h"
#include "../Engine/Engine.h"
#include "../Engine/MatrixOperator.h"

Lose::Lose() : exit(InputKey::KeyboardButtons::Escape)
{}

void Lose::Load()
{
	AddGSComponent(new Background());
	GetGSComponent<Background>()->Add("assets/loseBG.png");
	Button* buttonPtr = new Button();
	AddGSComponent(buttonPtr);
	buttonPtr->Add(glm::ivec2(Engine::GetWindow().GetSize().x / 2 + 350, Engine::GetWindow().GetSize().y * 0.15),
		"assets/quit0Button.png", "assets/quit1Button.png", false);
}

void Lose::Update(double dt)
{
	if (exit.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}

	if (GetGSComponent<Button>()->GetBool(0) == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}
}

void Lose::Unload()
{
	ClearGSComponent();
}

void Lose::Draw()
{
	GetGSComponent<Background>()->Draw();
	GetGSComponent<Button>()->Draw(0);
}
