//Jihyeon Song

#include "Background.h"
#include "../Engine/Engine.h"
#include "../Engine/MatrixOperator.h"

void Background::Add(const char* texturePath)
{
	backgrounds.push_back(ParallaxInfo{ Engine::GetTextureManager().Load(texturePath) });
}

glm::ivec2 Background::Size()
{
	return backgrounds[0].backimage->GetSize();
}

void Background::Draw()
{
	backgrounds[0].backimage->Draw(coconut::math::TranslateMatrix(glm::vec2{ 0, 0 }));
}

void Background::Unload()
{
	backgrounds.clear();
}
