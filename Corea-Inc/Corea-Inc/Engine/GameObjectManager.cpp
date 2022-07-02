#include "Engine.h"
#include "MatrixOperator.h"
#include "GameObjectManager.h"
#include "GameObject.h"

void coconut::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

coconut::GameObjectManager::~GameObjectManager()
{
	for (GameObject* obj : gameObjects)
	{
		delete obj;
	}
	gameObjects.clear();
}

void coconut::GameObjectManager::Update(double dt)
{
	std::vector<GameObject*> destroyList;
	for (GameObject* object : gameObjects)
	{
		object->Update(dt);
		if (object->ShouldDestroy() == true)
		{
			destroyList.push_back(object);
		}
	}
	for (GameObject* object : destroyList)
	{
		gameObjects.remove(object);
		delete object;
	}
}

void coconut::GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix)
{
	for (GameObject* object : gameObjects) {
		object->Draw(cameraMatrix);
	}
}