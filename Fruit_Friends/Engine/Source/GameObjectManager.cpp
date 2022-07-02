#include "../Header/Engine.h"        //LogEvent
//#include "../Header/TransformMatrix.h"
#include "../Header/GameObjectManager.h"
#include "../Header/GameObject.h"
//#include "../Header/Collision.h"

using namespace coconut;
class GameObject;

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
		if (object->ShouldDestroy() == true) {
			destroyList.push_back(object);
		}
	}
	for (GameObject* object : destroyList) {
		gameObjects.remove(object);
		delete object;
	}
}

//void GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix) {
//	for (GameObject* object : gameObjects) {
//		object->Draw(cameraMatrix);
//	}
//}

//void GameObjectManager::CollideTest() {
//	for (GameObject* objectA : gameObjects) {
//		for (GameObject* objectB : gameObjects) {
//			if (objectA != objectB && objectA->CanCollideWith(objectB->GetObjectType()) && objectB->GetGOComponent<Collision>() != nullptr) {
//				if (objectA->DoesCollideWith(objectB)) {
//					Engine::GetLogger().LogEvent(Part::Entire, "Collision Detected: " + objectA->GetObjectTypeName() + " and " + objectB->GetObjectTypeName());
//					//Engine::GetLogger().LogEvent("Collision Detected: " + objectA->GetObjectTypeName() + " and " + objectB->GetObjectTypeName());
//					objectA->ResolveCollision(objectB);
//				}
//			}
//		}
//	}
//}