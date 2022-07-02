#pragma once

#include <list>
#include "GameObject.h"
#include "Component.h"

namespace coconut {

	class GameObjectManager : public Component {
	public:
		~GameObjectManager();
		void Add(GameObject* obj);

		void Update(double dt) override;
		// void DrawAll(math::TransformMatrix& cameraMatrix); glm으로 transtorm matrix 만들어야될듯
		void CollideTest();
		const std::list<GameObject*>& Objects() { return gameObjects; }
	private:
		std::list<GameObject*> gameObjects;
	};
}