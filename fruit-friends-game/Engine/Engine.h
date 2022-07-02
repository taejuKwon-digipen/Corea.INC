#pragma once
#include <chrono>
#include "GameStateManager.h"
#include "Input.h"
#include "Window.h"
#include "Logger.h"
#include "TextureManager.h"
#include "SpriteFont.h"

class Engine {
public:
    static Engine& Instance() { static Engine instance; return instance; }
    static Logger& GetLogger() { return Instance().logger; };
    static Input& GetInput() { return Instance().input; }
    static Window& GetWindow() { return Instance().window; }
    static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }
    static TextureManager& GetTextureManager() { return Instance().textureManager; }
    static SpriteFont& GetSpriteFont(int index) { return Instance().fonts[index]; }

    void Init(std::string windowName);
    void Shutdown();
    void Update();
    bool HasGameEnded();

    void AddSpriteFont(const std::filesystem::path& fileName);

    template<typename T>
    static T* GetGSComponent() { return GetGameStateManager().GetGSComponent<T>(); }
private:
    Engine();
    ~Engine();

    std::chrono::system_clock::time_point lastTick;
    std::chrono::system_clock::time_point fpsCalcTime;
    int frameCount;
    
    Logger logger;
    TextureManager textureManager;
    GameStateManager gameStateManager;
    Input input;
    Window window;
    std::vector<SpriteFont> fonts;

    static constexpr double Target_FPS = 30.0;
    static constexpr int FPS_IntervalSec = 5;
    static constexpr int FPS_IntervalFrameCount = static_cast<int>(FPS_IntervalSec * Target_FPS);
};
