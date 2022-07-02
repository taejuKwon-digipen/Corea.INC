#pragma once
#include <string>
#include "Rect.h"
#include "Vec2.h"
#include "../Engine/Header/Texture.h"

class SpriteFont {
public:
	SpriteFont(const std::filesystem::path& fileName);
	Texture DrawTextToTexture(std::string text, unsigned int color, bool drawShadow);
private:
	void SetupCharRects();
	math::irect2& GetCharRect(char c);
	math::ivec2 MeasureText(std::string text);
	void DrawChar(math::TransformMatrix& matrix, char c);

	CS230::Texture texture;
	static constexpr int numOfChars = 'z' - ' ' + 1;
	math::irect2 charTexels[numOfChars];
};
