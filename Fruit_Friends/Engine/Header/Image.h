#pragma once
#include <string>
#include <memory>
#include <GL/glew.h>
#include "glslshader.h"
#include <filesystem>

namespace coconut {
	class Image {
	private:
		int width, height, nrChannels, xpos, ypos;
		const char* filepath;
		GLSLShader shdr_pgm;
		GLuint texobj_hdl0;
		GLuint vaoid;
		bool tex;
	public:
		Image();
		Image(const char* _filepath);
		Image(const char* _filepath, int w, int h);
		void init(const char* _filepath, int x, int y, int w, int h);
		void drawImage();
		
		struct GLModel
		{
			GLenum primitive_type;
			GLSLShader shdr_pgm;
			GLuint vaoid;
			GLuint idx_elem_cnt;
			void setup_vao();
			void setup_shdrpgm();
			void draw(GLuint texobj_hdl);
		};

		struct Vertex {
			glm::vec2 Position;
			glm::vec3 Color;
			glm::vec2 TexCoords;
		};

		struct Texture {
			unsigned int id;
			std::string type;
		};

		static std::vector<Vertex> vertices;
		static GLModel mdl;

		glm::vec2 getPos();
		glm::vec2 GetSize();
		void begin_drawing_to_image(float x, float y, bool _tex);
		void end_drawing_to_image();
	};
}