#include "Texture.h"

using namespace coconut;

Texture::Texture(const char* filePath) {
	texelImage = TexelImage{ filePath };
}
Texture::Texture(TexelImage&& Image) {
	texelImage = std::move(Image);
}

void Texture::TextureInit(const char* filePath)
{
	FilePath = filePath;
}

void Texture::Draw(/*glm::mat3 displayMatrix,*/ glm::vec2 texelPos, glm::vec2 frameSize) {
	glPushMatrix(); //glpushAttribute?
	//apply_Matrix(displayMatrix[0][0], displayMatrix[1][0], displayMatrix[0][1], displayMatrix[1][1], displayMatrix[0][2], displayMatrix[1][2]);
	texelImage.init(FilePath, 0, 0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
	texelImage.drawTexelImage();
	glPopMatrix()
}

glm::vec2 Texture::GetSize() { return texelImage.GetSize(); }

//GLushort Texture::GetPixel(glm::vec2 pos) {
//	int index = pos.y * GetSize().x + pos.x;
//	return (static_cast<int>(image[index].red)) << 24 |
//		(static_cast<int>(image[index].green)) << 16 |
//		(static_cast<int>(image[index].blue)) << 8 |
//		(static_cast<int>(image[index].alpha));
//}