#pragma once
#include <string>
#include "Texture.h"
#include "Rect.h"

namespace coconut {
	class SpriteFont {
	public:
		SpriteFont(const char* fileName);
		Texture DrawTextToTexture(std::string text, unsigned int color, bool drawShadow);
	private:
		void SetupCharRects();
		math::irect2& GetCharRect(char c);
		glm::ivec2 MeasureText(std::string text);
		void DrawChar(math::TransformMatrix& matrix, char c);

		Texture texture;
		static constexpr int numOfChars = 'z' - ' ' + 1;
		std::vector<math::irect2> charTexels;
	};
}