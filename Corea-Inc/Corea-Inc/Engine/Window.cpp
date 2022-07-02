#include "Window.h"

GLint Window::width;
GLint Window::height;
std::string Window::title;
GLFWwindow* Window::ptr_window;
glm::ivec2 Window::windowSize;

void Window::Init(GLint w, GLint h, std::string windowName)
{
	width = w;
	height = h;
	title = windowName;
	windowSize = { width, height };

	if (!glfwInit())
	{
		// we should fix here with logger
		std::cout << "GLFW Init has failed." << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	ptr_window = glfwCreateWindow(w, h, windowName.c_str(), NULL, NULL);
	if (!ptr_window)
	{
		// fix this with logger
		std::cerr << "GLFW unable to create OpenGL context." << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(ptr_window);

	glfwSetFramebufferSizeCallback(ptr_window, fbsize_callback);
	glfwSetKeyCallback(ptr_window, key_callback);
	glfwSetMouseButtonCallback(ptr_window, mouse_callback);
	glfwSetCursorPosCallback(ptr_window, mousePosition_callback);
	glfwSetScrollCallback(ptr_window, mouseScroll_callback);

	glfwSetInputMode(ptr_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glViewport(0, 0, width, height);
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// fix this with logger
		std::cout << "Unable to initializer GLFW - error: " << std::endl;
	}
	if (GLEW_VERSION_4_5)
	{
		// fix this with logger
		std::cout << "Driver supports OpenGL 4.5." << std::endl;
	}
}

void Window::Resize(GLFWwindow* ptr_window, int newWidth, int newHeight)
{
	windowSize = { newWidth, newHeight };
}

void Window::Update()
{
	glfwPollEvents();
}

void Window::Clear(float r, float g, float b, float alpha)
{
	glClearColor(r, g, b, alpha);
}

glm::ivec2 Window::GetSize()
{
	return windowSize;
}

void Window::fbsize_callback([[maybe_unused]] GLFWwindow* ptr_window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::key_callback(GLFWwindow* ptr_window, int key, [[maybe_unused]] int scancode, int action, int mod)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(ptr_window, GLFW_TRUE);
	}
}

void Window::mouse_callback(GLFWwindow* ptr_window, int button, int action, int)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		switch (action)
		{
		case GLFW_PRESS:
			mouseIsPressed = true;
			break;
		case GLFW_RELEASE:
			mouseIsPressed = false;
			break;
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		switch (action)
		{
		case GLFW_PRESS:
			mouseIsPressed = true;
			break;
		case GLFW_RELEASE:
			mouseIsPressed = false;
			break;
		}
		break;
	}
	
}

void Window::mousePosition_callback(GLFWwindow* ptr_window, double xPos, double yPos)
{
	mouseX = xPos;
	mouseY = yPos;
}

void Window::mouseScroll_callback(GLFWwindow* ptr_window, double xOffset, double yOffset)
{}