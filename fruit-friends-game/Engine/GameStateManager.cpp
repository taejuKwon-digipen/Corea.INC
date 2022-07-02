#include "Engine.h"			//logger
#include "GameStateManager.h"
#include "GameState.h"
#include "GameObjectManager.h"

GameStateManager::GameStateManager() : currGameState(nullptr), nextGameState(nullptr), state(State::START) {}

void GameStateManager::AddGameState(GameState& gameState) {
	gameStates.push_back(&gameState);
}

void GameStateManager::Update(double dt) {
	switch (state) {
	case State::START:
		if (gameStates.size() == 0) {
			Engine::GetLogger().LogError("No States have been loaded");
			state = State::SHUTDOWN;
		} else {
			nextGameState = gameStates[0];
			state = State::LOAD;
		}
		break;
	case State::LOAD:
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete");
		state = State::UPDATE;
		break;
	case State::UPDATE:
		if (currGameState != nextGameState) {
			state = State::UNLOAD;
		} else {
			Engine::GetLogger().LogVerbose("Update " + currGameState->GetName());
			currGameState->Update(dt);
			currGameState->Draw();
		}
		break;
	case State::UNLOAD:
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());
		currGameState->Unload();
		if (nextGameState != currGameState) {
			Engine::GetTextureManager().Unload();
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
