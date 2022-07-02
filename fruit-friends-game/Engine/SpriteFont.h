#pragma once
#include <string>
#include "Texture.h"
#include "Vec2.h"
#include "Rect.h"

class SpriteFont {
public:
	SpriteFont(const std::filesystem::path& fileName);
	Texture DrawTextToTexture(std::string text, unsigned int color, bool drawShadow);
private:
	void SetupCharRects();
	math::irect2& GetCharRect(char c);
	math::ivec2 MeasureText(std::string text);
	void DrawChar(math::TransformMatrix& matrix, char c);

	Texture texture;
	static constexpr int numOfChars = 'z' - ' ' + 1;
	math::irect2 charTexels[numOfChars];
};
