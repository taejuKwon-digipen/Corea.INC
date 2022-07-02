// Geonhwi Sim

#include "HeadQuarters.h"
#include "Background.h"
#include "Button.h"
#include "Fonts.h"
#include "GreatPeople.h"
#include "Screens.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Engine.h"

HeadQuarters::HeadQuarters() :
	mainGame{ InputKey::KeyboardButtons::Escape }
{}

void HeadQuarters::Load()
{
#ifdef _DEBUG
#endif
	//title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Head Quarters", 0xFFFFFFFF, true);
	glm::ivec2 winSize = Engine::GetWindow().GetSize() / 2;
	coconut::GameObjectManager* gom = new coconut::GameObjectManager();
	AddGSComponent(new Background());
	GetGSComponent<Background>()->Add("assets/Background.png");
	Button* buttonPtr = new Button();
	AddGSComponent(buttonPtr);
	buttonPtr->Add(glm::ivec2(Engine::GetWindow().GetSize().x / 2 + 350, Engine::GetWindow().GetSize().y * 0.15),
		"assets/quit0Button.png", "assets/quit1Button.png", false);
}

void HeadQuarters::Update(double dt)
{
	//UpdateGSComponents(dt);
	if (mainGame.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
	}
	if (GetGSComponent<Button>()->GetBool(0) == true)
	{
		Engine::GetGameStateManager().Shutdown();
	}
}

void HeadQuarters::Draw()
{
	Engine::GetWindow().Clear(1.f, 1.f, 1.f, 1.f);
	glm::ivec2 winSize = Engine::GetWindow().GetSize();
	coconut::math::TransformMatrix mat;

	glm::ivec2 position = glm::ivec2{ winSize.x / 2 - title.GetSize().x, winSize.y / 2 - title.GetSize().y };
	GetGSComponent<Background>()->Draw();
	GetGSComponent<Button>()->Draw(0);
	title.Draw(coconut::math::TranslateMatrix(position) * coconut::math::ScaleMatrix({ 2,2 }));
	//GetGSComponent<GameObjectManager>()->DrawAll(mat);
}

void HeadQuarters::Unload()
{
	ClearGSComponent();
}