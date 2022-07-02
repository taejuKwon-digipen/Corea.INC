#include <stdexcept>	//std::exception
#include <iostream>		//std::cerr

#include "Engine/Engine.h"
#include "Game/Splash.h"
#include "Game/MainGame.h"
#include "Game/HeadQuarters.h"
#include "Game/HumanResources.h"
#include "Game/Lose.h"
#include "Game/Screens.h"
#include "Game/MainMenu.h"
#include "Game/Win.h"
#include "Game/ItemPart.h"
#include "Game/FieldPart.h"
//#include "Game/UI.h"
#include "Game/EnemyPart.h"
#include "Game/Music.h"

class FieldHero;

int main(void) {
	try {
		Hero* hero = new Hero({ 1000.0, 500.0 });

		Engine& engine = Engine::Instance();
		engine.Init(1440, 880, "Fruits Friend",);
		Splash splash;
		MainMenu mainmenu;
		MainGame maingame(hero);
		HeadQuarters headQuarters;
		HumanResources humanResources;

		Win win;
		Lose lose;
		FieldHero* fieldhero = new FieldHero({ 700,400 });
		Item_First item_first(hero, 1);
		//ItemPart items(*hero);
		FieldPart fields(*fieldhero);
		//EnemyPart enemies;
		//UI UIs;

		Music bgm;
		bgm.mainmenu_bgm();
		bgm.MAINMENU_BGM.play();

		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(mainmenu);
		engine.GetGameStateManager().AddGameState(maingame);
		//engine.GetGameStateManager().AddGameState(headQuarters);
		engine.GetGameStateManager().AddGameState(humanResources);
		engine.GetGameStateManager().AddGameState(win);
		engine.GetGameStateManager().AddGameState(lose);
		engine.GetGameStateManager().AddGameState(item_first);
		engine.GetGameStateManager().AddGameState(fields);
		//engine.GetGameStateManager().AddGameState(enemies);
		//engine.GetGameStateManager().AddGameState(UIs);
		engine.AddSpriteFont("assets/font.png");
		engine.AddSpriteFont("assets/font2.png");

		while (engine.HasGameEnded() == false) {
			engine.Update();
		}
		engine.Shutdown();
		return 0;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << "\n";
		return -1;
	}
}
