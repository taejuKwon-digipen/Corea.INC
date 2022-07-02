#pragma once

#include <list>
#include "GameObject.h"
#include "Component.h"

class GameObjectManager : public Component {
public:
	~GameObjectManager();
	void Add(GameObject* obj);

	void Update(double dt) override;
	void DrawAll(math::TransformMatrix& cameraMatrix);
	const std::list<GameObject*>& Objects() { return gameObjects; }
private:
	std::list<GameObject*> gameObjects;
};