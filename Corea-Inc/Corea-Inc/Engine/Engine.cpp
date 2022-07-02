#include "Engine.h"

Engine::Engine() : frameCount(0), lastTick(std::chrono::system_clock::now()),
#ifdef _DEBUG
logger(Logger::Severity::Debug, Part::Entire, true, lastTick)
#else
logger(Logger::Severity::Event, Part::Entire, false, lastTick)
#endif

{}

Engine::~Engine() {}

void Engine::Init(GLint w, GLint h, std::string windowName)
{
	fpsCalcTime = lastTick;
	int seed = static_cast<unsigned int>(time(NULL));
	srand(seed);

	window.Init(w, h, windowName);
}

void Engine::Shutdown()
{
	glfwTerminate();
}

void Engine::Update()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();

#ifdef _DEBUG
	if (dt > 2 / Engine::Target_FPS) {
		dt = 1 / Engine::Target_FPS;
		// Long Frame Detected! <- Do we need this? Really?
	}
#endif

	if (dt >= 1 / Engine::Target_FPS)
	{
		lastTick = now;

		if (++frameCount >= Engine::FPS_IntervalFrameCount)
		{
			double actualTime = std::chrono::duration<double>((now - fpsCalcTime)).count();
			// We can check FPS in here by using logger
			frameCount = 0;
			fpsCalcTime = now;
		}
		glfwSwapBuffers(Window::ptr_window);
	}
	glfwPollEvents();
}

bool Engine::HasGameEnded()
{
	return true;
}

void Engine::AddSpriteFont(const char* fileName)
{
	fonts.push_back(coconut::SpriteFont(fileName));
}
