// Geonhwi Sim

#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <glm/vec2.hpp>

class Window
{
public:
	static void Init(GLint w, GLint h, std::string windowName);
	static void Resize(GLFWwindow* window, int newWidth, int newHeight);
	static void Update();
	static glm::ivec2 GetSize();
	
	static void fbsize_callback(GLFWwindow* ptr_window, int width, int height);
	static void key_callback(GLFWwindow* ptr_window, int key, int scancode, int action, int mod);
	static void mouse_callback(GLFWwindow* ptr_window, int button, int action, int mod);
	static void mousePosition_callback(GLFWwindow* ptr_window, double xpos, double ypos);
	static void mouseScroll_callback(GLFWwindow* ptr_window, double xOffset, double yOffset);

	static GLFWwindow* ptr_window;
	
	static glm::ivec2 windowSize;
	static GLint width, height;
	static std::string title;
};