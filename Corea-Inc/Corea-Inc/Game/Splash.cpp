#include <filesystem>
#include "../Engine/Engine.h"	//GetGameStateManager	GetTextureManager
#include "../Engine/Texture.h"
#include "../Engine/MatrixOperator.h"
#include "Screens.h"
#include "Splash.h"

Splash::Splash() {}

void Splash::Load() {
	texturePtr = Engine::GetTextureManager().Load("assets/DigiPen_BLACK_1024px.png");
	timer = 0;
}

void Splash::Update(double dt) {
	timer += dt;
	if (timer >= DISPLAY_TIME) {
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
}

void Splash::Unload() {
}
void Splash::Draw() {
	Engine::GetWindow().Clear(1.f, 1.f, 1.f, 1.f);
	texturePtr->Draw(coconut::math::TranslateMatrix({ glm::vec2(Engine::GetWindow().GetSize().x / 2.0 - texturePtr->GetSize().x / 2.0, Engine::GetWindow().GetSize().y / 2.0 - texturePtr->GetSize().y / 2.0) }));
}