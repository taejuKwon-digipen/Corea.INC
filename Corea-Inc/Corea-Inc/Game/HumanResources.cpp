// Geonhwi Sim

#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "Screens.h"
#include "HumanResources.h"
#include "Fonts.h"
#include "Background.h"
#include "GreatPeople.h"
#include "Silhouette.h"
#include "MainGame.h"

HumanResources::HumanResources()
	: mainGame(InputKey::KeyboardButtons::Escape), instNext(InputKey::KeyboardButtons::Enter), showInstruction(true), showIns(0)
{}

void HumanResources::Load()
{
	//have to make getspritefont
	Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Stage 0", 0x404040FF, true);

	coconut::GameObjectManager* gom = new coconut::GameObjectManager();
	AddGSComponent(gom);
	gom->Add(new GreatPeople({ 400, 700 }, 0));
	gom->Add(new GreatPeople({ 600, 700 }, 1));
	gom->Add(new GreatPeople({ 800, 700 }, 2));
	gom->Add(new GreatPeople({ 1000,700 }, 3));

	AddGSComponent(new Background());
	GetGSComponent<Background>()->Add("assets/mainGame.png");
	
	Silhouette* silPtr = new Silhouette();
	if (stage == 0) {
		silPtr->Add(0, Silhouette::Applicants{ {0, 0}, {20, 0 },
			Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/app0-0.png") });
		silPtr->Add(0, Silhouette::Applicants{ {0, 1}, {370, 0 },
			Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/app0-1.png") });
		silPtr->Add(0, Silhouette::Applicants{ {0, 0}, {720, 0 },
			Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/app0-2.png") });
		silPtr->Add(0, Silhouette::Applicants{ {0, 1}, {1070, 0 },
			Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/app0-3.png") });
	}
	else if (stage == 1)
	{
		silPtr->Add(1, Silhouette::Applicants{ {0, 0}, {20, 0 },
			Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/app1-0.png") });
		silPtr->Add(1, Silhouette::Applicants{ {0, 1}, {370, 0 },
			Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/app1-1.png") });
		silPtr->Add(1, Silhouette::Applicants{ {0, 1}, {720, 0 },
			Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/app1-2.png") });
		silPtr->Add(1, Silhouette::Applicants{ {0, 0}, {1070, 0 },
			Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/app1-3.png") });
	}
	AddGSComponent(silPtr);

	inst1 = Engine::GetTextureManager().Load("assets/Human-Resources/HRP_instruction1.png");
	inst2 = Engine::GetTextureManager().Load("assets/Human-Resources/HRP_instruction2.png");
	inst3 = Engine::GetTextureManager().Load("assets/Human-Resources/HRP_instruction3.png");
}

void HumanResources::Update(double dt)
{
	if (mainGame.IsKeyReleased() == true)
	{
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
	}
	if (instNext.IsKeyReleased() == true)
	{
		showIns++;
		if (showIns > 3) {
			showInstruction = false;
		}
	}	
	UpdateGSComponents(dt);

	if (GetGSComponent<Silhouette>()->GetAnswerBool() == true)
	{
		stage++;
		if (stage > 1)
		{
			Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
			MainGame::showHRCheck = true;
		}
		ClearGSComponent();
		Load();
		GetGSComponent<Silhouette>()->SetAnswerBool(false);
	}

	if (GetGSComponent<Silhouette>()->GetIsDeadBool() == true)
	{
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
		ClearGSComponent();
		Load();
		GetGSComponent<Silhouette>()->SetIsDeadBool(false);
	}
}

void HumanResources::Draw()
{
	coconut::math::TransformMatrix Location;

	GetGSComponent<Background>()->Draw();
	GetGSComponent<Silhouette>()->Draw(stage);
	GetGSComponent<coconut::GameObjectManager>()->DrawAll(Location);
	
	if (showInstruction)
	{
		switch (showIns) {
		case 0:
			Engine::GetWindow().Clear(0.f, 0.f, 0.f, 0.46f);
			inst1->Draw(coconut::math::TranslateMatrix(glm::vec2{ Engine::GetWindow().GetSize().x / 2 - inst1->GetSize().x / 2, Engine::GetWindow().GetSize().y / 2 - inst1->GetSize().y / 2 }));
			break;

		case 1:
			Engine::GetWindow().Clear(0.f, 0.f, 0.f, 0.46f);
			inst2->Draw(coconut::math::TranslateMatrix(glm::vec2{ Engine::GetWindow().GetSize().x / 2 - inst1->GetSize().x / 2, Engine::GetWindow().GetSize().y / 2 - inst1->GetSize().y / 2 }));
			break;

		case 2:
			Engine::GetWindow().Clear(0.f, 0.f, 0.f, 0.46f);
			inst3->Draw(coconut::math::TranslateMatrix(glm::vec2{ Engine::GetWindow().GetSize().x / 2 - inst1->GetSize().x / 2, Engine::GetWindow().GetSize().y / 2 - inst1->GetSize().y / 2 }));
			break;
		}
	}
}

void HumanResources::Unload()
{
	ClearGSComponent();
}