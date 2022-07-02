#ifndef GLSLSHADER_H
#define GLSLSHADER_H

#pragma once
#include <GL/glew.h> // for access to OpenGL API declarations 
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>

class GLSLShader
{
public:
  GLSLShader() : pgm_handle(0), is_linked(GL_FALSE) {
  }

  GLboolean CompileLinkValidate(std::vector<std::pair<GLenum, std::string>>);
  GLboolean CompileShaderFromFile(GLenum shader_type, std::string const& file_name);
  GLboolean CompileShaderFromString(GLenum shader_type, std::string const& shader_src);
  GLboolean Link();

  void Use();
  void UnUse();

  GLboolean Validate();
  GLuint GetHandle() const;
  GLboolean IsLinked() const;

  std::string GetLog() const;
  void BindAttribLocation(GLuint index, GLchar const *name);
  void BindFragDataLocation(GLuint color_number, GLchar const *name);
  void DeleteShaderProgram();

	void SetUniform(GLchar const *name, GLboolean val);
  void SetUniform(GLchar const *name, GLint val);
  void SetUniform(GLchar const *name, GLfloat val);
  void SetUniform(GLchar const *name, GLfloat x, GLfloat y);
  void SetUniform(GLchar const *name, GLfloat x, GLfloat y, GLfloat z);
  void SetUniform(GLchar const *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void SetUniform(GLchar const *name, glm::vec2 &val);
  void SetUniform(GLchar const *name, glm::vec3 &val);
  void SetUniform(GLchar const *name, glm::vec4 &val);
  void SetUniform(GLchar const *name, glm::mat3 &val);
  void SetUniform(GLchar const *name, glm::mat4 &val);

  void PrintActiveAttribs() const;

  void PrintActiveUniforms() const;

private:
  enum ShaderType {
    VERTEX_SHADER = GL_VERTEX_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
    GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
    TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
  };

  GLuint pgm_handle = 0;
  GLboolean is_linked = GL_FALSE;
  std::string log_string;

private:
  GLint GetUniformLocation(GLchar const *name);
  
  GLboolean FileExists(std::string const& file_name);
};

#endif /* GLSLSHADER_H */
