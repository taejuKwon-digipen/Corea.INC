//Jihyeon Song

#include "Background.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"

void Background::Add(const std::filesystem::path& texturePath)
{
	backgrounds.push_back(ParallaxInfo{ Engine::GetTextureManager().Load(texturePath) });
}

math::ivec2 Background::Size()
{
	return backgrounds[0].backimage->GetSize();
}

void Background::Draw()
{
	backgrounds[0].backimage->Draw(math::TranslateMatrix(math::vec2{ 0, 0 }));
}

void Background::Unload()
{
	backgrounds.clear();
}
