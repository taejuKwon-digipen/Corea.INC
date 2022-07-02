#include "Engine.h"
#include "SpriteFont.h"
#include "MatrixOperator.h"
#include "Image.h"
#include <string>

using namespace coconut;

SpriteFont::SpriteFont(const char* fileName) : texture(fileName) {
	Texture::Color white = {1.f, 1.f, 1.f, 1.f};
	Texture::Color color = texture.GetPixel({ 0, 0 });
	std::string fileNameStr = fileName;
	if (color.r != white.r && color.g != white.g
		&& color.b != white.b && color.alpha != white.alpha)
	{
		Engine::GetLogger().LogError(Part::Entire, "Sprite font " + fileNameStr + " not setup correctly");
		return;
	}
	// Build our rects
	SetupCharRects();
}

void SpriteFont::SetupCharRects() {
	Texture::Color testColor = texture.GetPixel({ 0, 0 });
	Texture::Color nextColor;

	double height = texture.GetSize().y;

	int xPos = 0;
	testColor = texture.GetPixel({ xPos, 0 });
	for (int index = 0; index < SpriteFont::numOfChars; index++) {
		int width = 0;
		do {
			width++;
			nextColor = texture.GetPixel({ xPos + width, 0 });
		}
		while (testColor.r == nextColor.r && testColor.g == nextColor.g &&
			testColor.b == nextColor.b && testColor.alpha == nextColor.alpha);
		
		testColor = nextColor;

		charTexels[index].point2 = { xPos + width - 1, 1 };
		charTexels[index].point1 = { xPos, charTexels[index].point2.y + height - 1 };
		xPos += width;
	}
}

math::irect2& SpriteFont::GetCharRect(char c) {
	if (c >= ' ' && c <= 'z') {
		return charTexels[c - ' '];
	} else {
		Engine::GetLogger().LogError(Part::Entire,"character '" + std::to_string(c) + "' not found in spriteFont");
		return charTexels[0];
	}
}

glm::ivec2 SpriteFont::MeasureText(std::string text) {
	glm::ivec2 size = { 0,0 };
	// Todo: For each character use it's charTexel information to find the width/height of the string
	for (char c : text) {
		math::irect2 charRect = GetCharRect(c);
		size.x += GetCharRect(c).Size().x;
		if (charRect.Size().y > size.y) {
			size.y = charRect.Size().y;
		}
	}
	return size;
}

Texture SpriteFont::DrawTextToTexture(std::string text, unsigned int color, bool drawShadow) {

	glm::ivec2 textSize = MeasureText(text);
	if (drawShadow == true) {
		textSize += glm::ivec2{3, 3};
	}
	Image::begin_drawing_to_image(textSize.x, textSize.y, true); //this starts our rendering to the texture

	math::TransformMatrix matrix;
	if (drawShadow == true) {
		// draw in black using the shadow position
		for (char c : text) {
			DrawChar(matrix, c);
		}
		matrix = math::TranslateMatrix(glm::ivec2{ 3,3 });
	}

	for (char c : text) {
		DrawChar(matrix, c);
	}
	
	return texture;
}

void SpriteFont::DrawChar(math::TransformMatrix& matrix, char c) {
	math::irect2& displayRect = GetCharRect(c);
	glm::ivec2 topLeftTexel = { displayRect.point1.x, displayRect.point2.y };
	if (c != ' ') {
		texture.Draw(matrix, topLeftTexel, displayRect.Size());
	}
	matrix *= math::TranslateMatrix(glm::ivec2{ displayRect.Size().x, 0 });
}