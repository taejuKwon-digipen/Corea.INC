////Jihyeon Song
//
//#pragma once
//#include <filesystem>
//#include "Fonts.h"
//#include "../Engine/Engine.h"
//#include "../Engine/Component.h"
//#include "../Engine/Vec2.h"
//#include "../Engine/Texture.h"
//
//class GameObjectManager;
//
//class UI : public Component
//{
//public:
//    UI();
//    UI(math::vec2 pos, const std::filesystem::path& spriteInfoFile);
//
//    void partManager();
//    void playerManager();
//    void stageManager(double dt);
//
//    int stageNum = 1; //1 to 3
//
//private:
//    math::ivec2 location{ 100, 100 };
//
//    double stageTimer = 0;
//    const int startTime = 3;
//    double gameTimer = 100;
//
//    unsigned int stats = 100;
//
//    Fonts fontToUse;
//
//    InputKey nextKey; //right
//    InputKey preKey; //left
//    InputKey skipKey; //space
//    InputKey actionKey; //enter
//
//    Texture partTexture;
//    Texture statsTexture;
//    Texture timerTexture;
//
//    void setStage();
//
//	GameObjectManager* GOM;
//};
//
//class Timer : public UI
//{
//public:
//	Timer(int time);
//	void Update(double dt) override;
//	void Draw(math::ivec2 location);
//	bool hasEnded();
//
//private:
//	double timer;
//	Texture timeTexture;
//};
//
////class Stats : public UI
////{
////public:
////	Stats(int num);
////	void Update(double dt) override;
////	void Draw(math::ivec2 location);
////
////private:
////	double timer;
////	Texture timeTexture;
////};