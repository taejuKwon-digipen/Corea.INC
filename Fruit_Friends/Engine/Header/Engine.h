#pragma once
#include <chrono>
#include <vector>
#include "glslshader.h"
#include "GameStateManager.h"
#include "Input.h"
#include "Logger.h"
#include "Window.h"
#include "ImageManager.h"
//#include "SpriteFont.h"
#include "Scenepart.h"

namespace coconut {
    class Engine {
    public:
        static Engine& Instance() { static Engine instance; return instance; }
        static Logger& GetLogger() { return Instance().logger; }
        static Input& GetInput() { return Instance().input; }
        static Window& GetWindow() { return Instance().window; }
        static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }
        static ImageManager& GetImageManager() { return Instance().imageManager; 
        //static SpriteFont& GetSpriteFont(int index) { return Instance().fonts[index]; }

        void Init(GLint w, GLint h, std::string windowName);
        void Shutdown();
        void Update();
        bool HasGameEnded();

        //void AddSpriteFont(const std::filesystem::path& fileName);

        template<typename T>
        static T* GetGSComponent() { return GetGameStateManager().GetGSComponent<T>(); }
    private:
        Engine();
        ~Engine();

        std::chrono::system_clock::time_point lastTick;
        std::chrono::system_clock::time_point fpsCalcTime;
        int frameCount;

        Logger logger;
        ImageManager imageManager;
        GameStateManager gameStateManager;
        Input input;
        Window window;
        // GLFWcursor* cursor;
        //std::vector<SpriteFont> fonts;

        static constexpr double Target_FPS = 30.0;
        static constexpr int FPS_IntervalSec = 5;
        static constexpr int FPS_IntervalFrameCount = static_cast<int>(FPS_IntervalSec * Target_FPS);
    };

};