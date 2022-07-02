#pragma once

#include "../Header/Image.h"
#include "../Header/TexelImage.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace coconut {
	class Texture {
		friend class TextureManager;
		friend class SpriteFont;
	public:
		Texture() {}
		void TextureInit(const char* filePath);
		void Draw(glm::mat3 displayMatrix);
		void Draw(/*glm::mat3 displayMatrix,*/ glm::vec2 texelPos, glm::vec2 frameSize);
		glm::vec2 GetSize();
		GLushort GetPixel(glm::ivec2 pos);
	private:
		Texture(const char* filePath);
		Texture(TexelImage&& Image);
		TexelImage texelImage;
		const char* FilePath;
	};
}
