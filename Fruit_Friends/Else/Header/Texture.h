/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once

namespace math {
	class TransformMatrix;
}

namespace CS230 {
	class Texture {
		friend class TextureManager;
		friend class SpriteFont;
	public:
		Texture() {}
		void Draw(math::TransformMatrix displayMatrix);
		void Draw(math::TransformMatrix displayMatrix, glm::ivec2 texelPos, glm::ivec2 frameSize);
		glm::ivec2 GetSize();
		unsigned int GetPixel(glm::ivec2 pos);
	private:
		Texture(const std::filesystem::path& filePath);
		std::array<glm::vec2, 4> tex_vtx{};
	};
}
