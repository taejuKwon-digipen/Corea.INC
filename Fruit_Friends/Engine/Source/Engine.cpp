#include "../Header/Engine.h"

using namespace coconut;

Engine::Engine() : frameCount(0), lastTick(std::chrono::system_clock::now()),
#ifdef _DEBUG				
logger(Logger::Severity::Debug, Part::Entire, true, lastTick)
#else 						
logger(Logger::Severity::Event, false, lastTick)
#endif
{}

Engine::~Engine() {}

void Engine::Init(GLint w, GLint h, std::string windowName) {
	fpsCalcTime = lastTick;
	int seed = static_cast<unsigned int>(time(NULL));
	srand(seed);

	window.Init(w, h, windowName);
}

void Engine::Shutdown() {
	glfwTerminate();
}

void Engine::Update() {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();

#ifdef _DEBUG
	if (dt > 2 / Engine::Target_FPS) {
		dt = 1 / Engine::Target_FPS;
		Engine::GetLogger().LogEvent(Part::Entire,"Long Frame detected!");
	} // Does it really needed?
#endif

	if (dt >= 1 / Engine::Target_FPS) {
		logger.LogVerbose(Part::Entire,"Engine Update");
		lastTick = now;

		if (++frameCount >= Engine::FPS_IntervalFrameCount) {
			double actualTime = std::chrono::duration<double>((now - fpsCalcTime)).count();
			logger.LogEvent(Part::Entire,"FPS:  " + std::to_string(frameCount / actualTime));
			frameCount = 0;
			fpsCalcTime = now;
		}
		gameStateManager.Update(dt);
		input.Update();
		glfwSwapBuffers(Window::ptr_window);
	}
	glfwPollEvents();
	//window.Update();
}

bool Engine::HasGameEnded() {
	return gameStateManager.HasGameEnded();
}

//void Engine::AddSpriteFont(const std::filesystem::path& fileName) {
//	fonts.push_back(SpriteFont(fileName));
//}