#include "Engine.h"

Engine::Engine() : frameCount(0), lastTick(std::chrono::system_clock::now()),
#ifdef _DEBUG				
                   logger(Logger::Severity::Debug, true, lastTick)
#else 						
logger(Logger::Severity::Event, false, lastTick)
#endif
{}

Engine::~Engine() {}

void Engine::Init(std::string windowName) {
	logger.LogEvent("Engine Init");
	window.Init(windowName);
	fpsCalcTime = lastTick;

	int seed = static_cast<unsigned int>(time(NULL));
	srand(seed);
	Engine::GetLogger().LogEvent("Seed = " + std::to_string(seed));
}

void Engine::Shutdown() {
	logger.LogEvent("Engine Shutdown");
}

void Engine::Update() {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();

#ifdef _DEBUG
	if (dt > 2 / Engine::Target_FPS) {
		dt = 1 / Engine::Target_FPS;
		Engine::GetLogger().LogEvent("Long Frame detected!");
	}
#endif

	if (dt >= 1 / Engine::Target_FPS) {
		logger.LogVerbose("Engine Update");
		lastTick = now;

		if (++frameCount >= Engine::FPS_IntervalFrameCount) {
			double actualTime = std::chrono::duration<double>((now - fpsCalcTime)).count();
			logger.LogEvent("FPS:  " + std::to_string(frameCount / actualTime));
			frameCount = 0;
			fpsCalcTime = now;
		}
		gameStateManager.Update(dt);


		input.Update();
		window.Update();
	}
}

bool Engine::HasGameEnded() {
	return gameStateManager.HasGameEnded();
}

void Engine::AddSpriteFont(const std::filesystem::path& fileName) {
	fonts.push_back(SpriteFont(fileName));
}