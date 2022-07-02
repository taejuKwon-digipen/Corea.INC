//Taeju Kwon
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <array>
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"

using namespace coconut;

Image::GLModel Image::mdl;
Image::Vertex vertex;
std::vector<Image::Vertex> Image::vertices;

GLuint setup_texobj(const std::filesystem::path& _pathname) {
	//unsigned int VBO, EBO;
	int w = static_cast<int>(Image::GetSize().x);
	int h = static_cast<int>(Image::GetSize().y);
	int nrChannels;
	unsigned int texture = Image::GetTextureInt();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(_pathname.string().c_str(), &w, &h, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return texture;
}

Image::Image() : filepath("Assets/mainGame.png")
{
	width = 800;
	height = 500;
	vaoid = 0;
	xPos = 0;
	yPos = 0;
	tex = false;
	texobj_hdl = setup_texobj("Assets/mainGame.png");
}

Image::Image(const char* _filepath) : filepath(_filepath)
{
	width = 800;
	height = 500;
	vaoid = 0;
	xPos = 0;
	yPos = 0;
	texobj_hdl = setup_texobj(_filepath);
}

Image::Image(const char* _filepath, int w, int h) : filepath(_filepath)
{
	width = w;
	height = h;
	vaoid = 0;
	xPos = 0;
	yPos = 0;
	texobj_hdl = setup_texobj(_filepath);
}

void Image::init(int x, int y, int w, int h) {
	//Left Bottom
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glViewport(x, y, w, h);
	xPos = x;
	yPos = y;
	width = w;
	height = h;
	mdl.setup_vao();
	mdl.setup_shdrpgm();
	mdl.shdr_pgm.Use();
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Image::drawImage() {
	glClear(GL_COLOR_BUFFER_BIT);
	mdl.draw(texobj_hdl);
}

void Image::GLModel::setup_vao()
{
	unsigned int VBO, EBO;

	std::array<glm::vec2, 4> pos_vtx{
		glm::vec2(1.f, 1.f), glm::vec2(1.f, -1.f),
		glm::vec2(-1.f, -1.f), glm::vec2(-1.f, 1.f)
	};

	std::array<glm::vec3, 4> clr_vtx{
	glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f),
	glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f)
	};
	std::array<glm::vec2, 4> tex_vtx{
	glm::vec2(0.f, 0.f), glm::vec2(0.f, 1.f),
	glm::vec2(1.f, 1.f), glm::vec2(1.f, 0.f)
	};

	vertices.push_back({ pos_vtx[0],clr_vtx[0],tex_vtx[0] });
	vertices.push_back({ pos_vtx[1],clr_vtx[1],tex_vtx[1] });
	vertices.push_back({ pos_vtx[2],clr_vtx[2],tex_vtx[2] });
	vertices.push_back({ pos_vtx[3],clr_vtx[3],tex_vtx[3] });

	primitive_type = GL_TRIANGLE_STRIP;
	std::array<GLushort, 4> idx_vtx{ 1,2,0,3 };
	idx_elem_cnt = (GLuint)idx_vtx.size();

	glGenVertexArrays(1, &vaoid);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(vaoid);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx_vtx.size() * sizeof(unsigned int), &idx_vtx[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Image::GLModel::setup_shdrpgm()
{
	std::vector<std::pair<GLenum, std::string>> shdr_files;
	shdr_files.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/image.vert"));
	shdr_files.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/image.frag"));
	shdr_pgm.CompileLinkValidate(shdr_files);

	if (GL_FALSE == shdr_pgm.IsLinked()) {
		std::cout << "Unable to compile/link/validate shader programs" << "\n";
		std::cout << shdr_pgm.GetLog() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void Image::GLModel::draw(GLuint texobj_hdl)
{
	shdr_pgm.Use();
	glBindVertexArray(Image::mdl.vaoid);
	glBindTextureUnit(6, texobj_hdl);
	GLuint tex_loc = glGetUniformLocation(Image::mdl.shdr_pgm.GetHandle(), "uTex2d");
	glUniform1i(tex_loc, 6);
	glDrawElements(primitive_type, idx_elem_cnt, GL_UNSIGNED_SHORT, NULL);
	glBindVertexArray(0);
	shdr_pgm.UnUse();
}

glm::vec2 Image::GetPos()
{
	return glm::vec2{ xPos ,yPos };
}

glm::vec2 Image::GetSize()
{
	return glm::vec2{ width ,height };
}

unsigned Image::GetTextureInt()
{
	return texture;
}

void Image::begin_drawing_to_image(int x, int y, bool _tex)
{
	// standard => bottom left
	xPos = x - width / 2;
	yPos = y + height / 2;
}