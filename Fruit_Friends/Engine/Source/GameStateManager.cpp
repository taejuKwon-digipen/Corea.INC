#include "../Header/Engine.h"
#include "../Header/GameStateManager.h"
#include "../Header/GameState.h"
#include "../Header/GameObjectManager.h"

using namespace coconut;

GameStateManager::GameStateManager() : currGameState(nullptr), nextGameState(nullptr), state(State::START) {}

void GameStateManager::AddGameState(GameState& gameState) {
	gameStates.push_back(&gameState);
}

void GameStateManager::Update(double dt) {
	switch (state) {
	case State::START:
		if (gameStates.size() == 0) {
			Engine::GetLogger().LogError(Part::Entire, "No States have been loaded");
			state = State::SHUTDOWN;
		}
		else {
			nextGameState = gameStates[0];
			state = State::LOAD;
		}
		break;
	case State::LOAD:
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent(Part::Entire, "Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent(Part::Entire, "Load Complete");
		state = State::UPDATE;
		break;
	case State::UPDATE:
		if (currGameState != nextGameState) {
			state = State::UNLOAD;
		}
		else {
			Engine::GetLogger().LogVerbose(Part::Entire,"Update " + currGameState->GetName());
			currGameState->Update(dt);
			if (GetGSComponent<GameObjectManager>() != nullptr) {
				/*GetGSComponent<GameObjectManager>()->CollideTest();*/
			}
			currGameState->Draw();
		}
		break;
	case State::UNLOAD:
		Engine::GetLogger().LogEvent(Part::Entire, "Unload " + currGameState->GetName());
		currGameState->Unload();
		if (nextGameState != currGameState) {
			//Engine::GetTextureManager().Unload();
		}
		if (nextGameState == nullptr) {
			state = State::SHUTDOWN;
			break;
		}
		state = State::LOAD;
		break;
	case State::SHUTDOWN:
		state = State::EXIT;
		break;
	case State::EXIT:
		break;
	}
}

void GameStateManager::SetNextState(int initState) {
	nextGameState = gameStates[initState];
}

void GameStateManager::ReloadState() {
	state = State::UNLOAD;
}

void GameStateManager::Shutdown() {
	state = State::UNLOAD;
	nextGameState = nullptr;
}