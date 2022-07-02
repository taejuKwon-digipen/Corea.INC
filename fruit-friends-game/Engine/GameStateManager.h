#pragma once
#include <vector>
#include "GameState.h"

class GameStateManager {
public:
	GameStateManager();

	void AddGameState(GameState& gameState);
	void Update(double dt);
	void SetNextState(int initState);
	void Shutdown();
	void ReloadState();
	bool HasGameEnded() { return state == State::EXIT; }

	template<typename T>
	T* GetGSComponent() { return currGameState->GetGSComponent<T>(); }
private:
	enum class State {
		START,
		LOAD,
		UPDATE,
		UNLOAD,
		SHUTDOWN,
		EXIT,
	};

	std::vector<GameState*> gameStates;
	State state;
	GameState* currGameState;
	GameState* nextGameState;
};