#pragma once
#include <chrono>
#include "glslshader.h"
#include "Window.h"
#include "Logger.h"
#include "ImageManager.h"
#include "TextureManager.h"
#include "GameStateManager.h"
#include "Input.h"
#include "Texture.h"
#include "SpriteFont.h"
#include "../Game/Fonts.h"

class Engine
{
public:
	static Engine& Instance()
	{
		static Engine instance;
		return instance;
	}
	static Window& GetWindow() { return Instance().window; }
	static Logger& GetLogger() { return Instance().logger; }
	static Input& GetInput() { return Instance().input; }
	static coconut::ImageManager& GetImageManager() { return Instance().imageManager; }
	static coconut::TextureManager& GetTextureManager() { return Instance().textureManager; }
	static coconut::GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }
	static coconut::SpriteFont& GetSpriteFont(int index) { return Instance().fonts[index]; }
	
	void Init(GLint w, GLint h, std::string windowName);
	void Shutdown();
	void Update();
	bool HasGameEnded();

	void AddSpriteFont(const char* fileName);

private:
	Engine();
	~Engine();

	std::chrono::system_clock::time_point lastTick;
	std::chrono::system_clock::time_point fpsCalcTime;
	int frameCount;

	Window window;
	Logger logger;
	Input input;
	std::vector<coconut::SpriteFont> fonts;
	coconut::ImageManager imageManager;
	coconut::TextureManager textureManager;
	coconut::GameStateManager gameStateManager;

	static constexpr double Target_FPS = 30.0;
	static constexpr int FPS_IntervalSec = 5;
	static constexpr int FPS_IntervalFrameCount = static_cast<int>(FPS_IntervalSec * Target_FPS);
};