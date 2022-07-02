//#include "../Header/Engine.h"
//#include "../Header/SpriteFont.h"
//#include "../Header/Image.h"
//
//using namespace coconut;
//
//SpriteFont::SpriteFont(const std::filesystem::path& fileName) : texture(fileName) {
//	unsigned int white = 0xFFFFFFFF;
//
//	unsigned int color = texture.GetPixel({ 0, 0 });
//	if (color != white) {
//		Engine::GetLogger().LogError(Part::Entire, "Sprite font " + fileName.string() + " not setup correctly");
//		return;
//	}
//
//	SetupCharRects();
//}
//
//void SpriteFont::SetupCharRects() {
//	unsigned int testColor = texture.GetPixel({ 0, 0 });
//	unsigned int nextColor;
//
//	int height = texture.GetSize().y;
//
//	int xPos = 0;
//	testColor = texture.GetPixel({ xPos, 0 });
//	for (int index = 0; index < SpriteFont::numOfChars; index++) {
//		int width = 0;
//
//		do {
//			width++;
//			nextColor = texture.GetPixel({ xPos + width, 0 });
//		} while (testColor == nextColor);
//
//		testColor = nextColor;
//
//		charTexels[index].point2 = { xPos + width - 1, 1 };
//		charTexels[index].point1 = { xPos, charTexels[index].point2.y + height - 1 };
//		xPos += width;
//	}
//}
//
//math::irect2& SpriteFont::GetCharRect(char c) {
//	if (c >= ' ' && c <= 'z') {
//		return charTexels[c - ' '];
//	}
//	else {
//		Engine::GetLogger().LogError(Part::Entire,"character '" + std::to_string(c) + "' not found in spriteFont");
//		return charTexels[0];
//	}
//}
//
//glm::ivec2 SpriteFont::MeasureText(std::string text) {
//	glm::ivec2 size = { 0,0 };
//
//	for (char c : text) {
//		math::irect2 charRect = GetCharRect(c);
//		size.x += GetCharRect(c).Size().x;
//		if (charRect.Size().y > size.y) {
//			size.y = charRect.Size().y;
//		}
//	}
//	return size;
//}
//
//Texture SpriteFont::DrawTextToTexture(std::string text, unsigned int color, bool drawShadow) {
//
//	glm::ivec2 textSize = MeasureText(text);
//	if (drawShadow == true) {
//		textSize += glm::ivec2{ 3, 3 };
//	}
//	//doodle::begin_drawing_to_image(textSize.x, textSize.y, true); //this starts our rendering to the texture
//
//	glm::mat3 matrix;
//	if (drawShadow == true) {
//		// draw in black using the shadow position
//		//doodle::set_tint_color(doodle::HexColor(0x000000FF)); -> tint
//		for (char c : text) {
//			DrawChar(matrix, c);
//		}
//		//matrix =glm::mat3(glm::ivec2{ 3,3 }); -?
//	}
//
//	// draw in white using the shadow position
//	//doodle::set_tint_color(doodle::HexColor(color));
//	for (char c : text) {
//		DrawChar(matrix, c);
//	}
//	// Reset the tint color incase it changed
//	//doodle::set_tint_color(doodle::HexColor(0xFFFFFFFF));
//	//return Texture(doodle::end_drawing_to_image());
//}
//
//void SpriteFont::DrawChar(glm::mat3& matrix, char c) {
//	math::irect2& displayRect = GetCharRect(c);
//	glm::ivec2 topLeftTexel = { displayRect.point1.x, displayRect.point2.y };
//	if (c != ' ') {
//		texture.Draw(matrix, topLeftTexel, displayRect.Size());
//	}
//	//matrix *= math::TranslateMatrix(math::ivec2{ displayRect.Size().x, 0 });
//}