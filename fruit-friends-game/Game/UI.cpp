////Jihyeon Song
//
//#include "UI.h"
//#include "Fonts.h"
//#include "../Engine/Engine.h"
//#include "../Engine/GameObjectManager.h"
//
//UI::UI(math::vec2 pos, const std::filesystem::path& spriteInfoFile) :
//    nextKey(InputKey::Keyboard::Right),
//    preKey(InputKey::Keyboard::Left),
//    skipKey(InputKey::Keyboard::Space),
//    actionKey(InputKey::Keyboard::Enter),
//    fontToUse()
//{
//    fontToUse = Fonts::Font2;
//}
//
//void UI::partManager()
//{
//    //alpha box with information and buttons
//    if (actionKey.IsKeyDown() == true && stageNum >= 1 && stageNum <= 3)
//    {
//        std::string partString = "1. Human Resource Part  2. Item Part   3. Enemy Part";
//        partTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(partString, 0xFFFFFFFF, true);
//    }
//}
//
//void UI::playerManager()
//{
//    statsTexture.Draw(math::TranslateMatrix(math::ivec2{ location.x, location.y }));
//
//    std::string statsString = "Player Stats: " + std::to_string(stats);
//    statsTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(statsString, 0xFFFFFFFF, true);
//    std::string timerString = "Time Left: " + std::to_string(gameTimer);
//    timerTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(timerString, 0xFFFFFFFF, true);
//
//    //every new game start & during
//    if (GameStateManager().HasGameEnded() == false)
//    {
//        gameTimer--;
//    }
//}
//
//void UI::stageManager(double dt)
//{
//    stageTimer += dt;
//    if (stageTimer < startTime) {
//        setStage();
//    }
//}
//
//void UI::setStage()
//{
//    Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Stage" + std::to_string(stageNum), 0xFFFFFFFF, true);
//
//    if (nextKey.IsKeyDown() == true && stageNum <= 3)
//    {
//        stageNum++;
//    }
//    else if (preKey.IsKeyDown() == true && stageNum > 1)
//    {
//        stageNum--;
//    }
//
//    //if (skipKey.IsKeyReleased() == true)
//    //{
//    //    //end
//    //}
//}
//
//Timer::Timer(int time) : UI(),
//timer(time), timeTexture()
//{}
//
//void Timer::Update(double dt)
//{
//	timer -= dt;
//}
//
//void Timer::Draw(math::ivec2 location)
//{
//	std::string timersString = "Time: " + std::to_string(static_cast<int>(timer));
//	timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timersString, 0xFFFFFFFF, true);
//	math::ivec2 winSize = Engine::GetWindow().GetSize();
//	location.x = winSize.x - timeTexture.GetSize().x;
//	location.y = winSize.y - timeTexture.GetSize().y - 5;
//	timeTexture.Draw(math::TranslateMatrix(math::ivec2{ location.x, location.y }));
//}
//
//bool Timer::hasEnded()
//{
//	if (timer <= 0)
//	{
//		return true;
//	}
//	return false;
//	//every new game start & during
//
//	//if (GameStateManager().HasGameEnded() == false)
//	//{
//	//	gameTimer--;
//	//}
//}
//
////Stats::Stats(int num)
////{
////}
////
////void Stats::Update(double dt)
////{
////	UI::Update(dt);
////}
////
////void Stats::Draw(math::ivec2 location)
////{
////}
