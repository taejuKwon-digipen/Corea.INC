#include "Engine.h"        //LogEvent
#include "TransformMatrix.h"
#include "GameObjectManager.h"
#include "GameObject.h"

void GameObjectManager::Add(GameObject* obj) {
	gameObjects.push_back(obj);
}

GameObjectManager::~GameObjectManager() {
	for (GameObject* obj : gameObjects) {
		delete obj;
	}
	gameObjects.clear();
}

void GameObjectManager::Update(double dt) {
	std::vector<GameObject*> destroyList;
	for (GameObject* object : gameObjects) {
		object->Update(dt);
	}
	for (GameObject* object : destroyList) {
		gameObjects.remove(object);
		delete object;
	}
}

void GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix) {
	for (GameObject* object : gameObjects) {
		object->Draw(cameraMatrix);
	}
}