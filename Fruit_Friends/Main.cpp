//TajuKwon

#include <iostream>
#include "Engine/Header/Engine.h"
#include "Engine/Header/Logger.h"
#include "Engine/Header/Window.h"
#include "Engine/Header/Image.h"
#include "Test.h"

using namespace coconut;
int main(void)
{
	//Image image;
	Engine& engine = Engine::Instance();
	engine.Init(800, 500, "Hello");
	//image.init();
	//engine.GetLogger().LogError(Part::Enemy, "Test");
	Test test;

	engine.GetGameStateManager().AddGameState(test);
	while (engine.HasGameEnded() == false)
	{
		engine.Update();
		//image.drawImage();
	}

	engine.Shutdown();
	return 0;
}
