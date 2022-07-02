#include "../../library/include/doodle/drawing.hpp"	//draw_image
#include "Texture.h"
#include "TransformMatrix.h"

Texture::Texture(const std::filesystem::path& filePath) {
	image = doodle::Image{ filePath };
}
Texture::Texture(doodle::Image&& doodleImage) {
	image = std::move(doodleImage);
}

void Texture::Draw(math::TransformMatrix displayMatrix, math::ivec2 texelPos, math::ivec2 frameSize) {
	doodle::push_settings();
	doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
	doodle::draw_image(image, 0, 0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
	doodle::pop_settings();
}

void Texture::Draw(math::TransformMatrix displayMatrix, math::ivec2 frameSize) {
	doodle::push_settings();
	doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
	doodle::draw_image(image, 0, 0, frameSize.x, frameSize.y);
	doodle::pop_settings();
}

void Texture::Draw(math::TransformMatrix displayMatrix) {
	doodle::push_settings();
	doodle::apply_matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
	doodle::draw_image(image, 0, 0);
	doodle::pop_settings();
}

math::ivec2 Texture::GetSize() { return { image.GetWidth(), image.GetHeight() }; }

unsigned int Texture::GetPixel(math::ivec2 pos) {
	int index = pos.y * GetSize().x + pos.x;
	return (static_cast<int>(image[index].red)) << 24 |
		(static_cast<int>(image[index].green)) << 16 |
		(static_cast<int>(image[index].blue)) << 8 |
		(static_cast<int>(image[index].alpha));
}