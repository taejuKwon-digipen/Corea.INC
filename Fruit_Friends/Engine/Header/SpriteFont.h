#pragma once
#include <string>
#include "Texture.h"
#include "Rect.h"

namespace coconut {
	class SpriteFont {
	public:
		SpriteFont(const std::filesystem::path& fileName);
		Texture DrawTextToTexture(std::string text, unsigned int color, bool drawShadow);
	private:
		void SetupCharRects();
		coconut::math::irect2& GetCharRect(char c);
		glm::ivec2 MeasureText(std::string text);
		void DrawChar(glm::mat3& matrix, char c);

		Texture texture;
		static constexpr int numOfChars = 'z' - ' ' + 1;
		math::irect2 charTexels[numOfChars];
	};
}