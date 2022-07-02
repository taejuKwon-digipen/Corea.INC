// Geonhwi Sim

#include "../Header/Window.h"
#include "../Header/Engine.h"

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
		std::cout << "GLFW init has failed." << std::endl; // It'll be better to show this in logger system.
		std::exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	ptr_window = glfwCreateWindow(w, h, windowName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(ptr_window);
	if(!ptr_window)
	{
		std::cerr << "GLFW unable to create OpenGL context" << std::endl;
		glfwTerminate();
	}

	glfwSetFramebufferSizeCallback(ptr_window, fbsize_callback);
	glfwSetKeyCallback(ptr_window, key_callback);
	glfwSetMouseButtonCallback(ptr_window, mouse_callback);
	glfwSetCursorPosCallback(ptr_window, mousePosition_callback);
	glfwSetScrollCallback(ptr_window, mouseScroll_callback);

	glfwSetInputMode(ptr_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		coconut::Engine::GetLogger().LogError(Part::Window, "Unable to initialize GLFW - error: ");
	}
	if (!GLEW_VERSION_4_5) {
		coconut::Engine::GetLogger().LogError(Part::Window, "Driver supports OpenGL 4.5");
	}
}

void Window::Resize(GLFWwindow* window, int newWidth, int newHeight)
{
	windowSize = { newWidth, newHeight };
}

glm::ivec2 Window::GetSize()
{
	return windowSize;
}

void Window::Update()
{
	glfwPollEvents();
}

void Window::fbsize_callback(GLFWwindow* ptr_window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::key_callback(GLFWwindow* ptr_window, int key, [[maybe_unused]] int scancode, int action, int mod)
{
	if (GLFW_PRESS == action)
	{
#ifdef _DEBUG
		std::cout << "key pressed" << std::endl;
#endif
	} else if (GLFW_RELEASE == action)
	{
#ifdef _DEBUG
		std::cout << "key released" << std::endl;
#endif
	}

	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(ptr_window, GLFW_TRUE);
	}
}

void Window::mouse_callback(GLFWwindow* ptr_window, int button, int action, int mod)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
#ifdef _DEBUG
		std::cout << "Left Mouse" << std::endl;
#endif
		break;

	case GLFW_MOUSE_BUTTON_RIGHT:
#ifdef _DEBUG
		std::cout << "Right Mouse" << std::endl;
#endif
		break;
	}

	switch (action)
	{
	case GLFW_PRESS:
#ifdef _DEBUG
		std::cout << "Mouse Pressed" << std::endl;
#endif
		break;

	case GLFW_RELEASE:
#ifdef _DEBUG
		std::cout << "Mouse Released" << std::endl;
#endif
		break;
	}
}

void Window::mousePosition_callback(GLFWwindow* ptr_window, double xpos, double ypos)
{
}

void Window::mouseScroll_callback(GLFWwindow* ptr_window, double xOffset, double yOffset)
{
}
