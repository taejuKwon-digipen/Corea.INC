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
	mainGame{ InputKey::Keyboard::Escape }
{}

void HeadQuarters::Load()
{
#ifdef _DEBUG
#endif
	title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Head Quarters", 0xFFFFFFFF, true);
	math::ivec2 winSize = Engine::GetWindow().GetSize() / 2;
	GameObjectManager* gom = new GameObjectManager();
	AddGSComponent(new Background());
	GetGSComponent<Background>()->Add("assets/Background.png");
	Button* buttonPtr = new Button();
	AddGSComponent(buttonPtr);
	buttonPtr->Add(math::ivec2(Engine::GetWindow().GetSize().x / 2 + 350, Engine::GetWindow().GetSize().y * 0.15),
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
	Engine::GetWindow().Clear(0xFFFFFFFF);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	math::TransformMatrix mat;

	math::ivec2 position = math::ivec2{ winSize.x / 2 - title.GetSize().x, winSize.y / 2 - title.GetSize().y };
	GetGSComponent<Background>()->Draw();
	GetGSComponent<Button>()->Draw(0);
	title.Draw(math::TranslateMatrix(position) * math::ScaleMatrix({ 2,2 }));
	//GetGSComponent<GameObjectManager>()->DrawAll(mat);
}

void HeadQuarters::Unload()
{
	ClearGSComponent();
}