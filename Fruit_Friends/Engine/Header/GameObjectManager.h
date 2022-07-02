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
		// void DrawAll(math::TransformMatrix& cameraMatrix); glm���� transtorm matrix �����ߵɵ�
		void CollideTest();
		const std::list<GameObject*>& Objects() { return gameObjects; }
	private:
		std::list<GameObject*> gameObjects;
	};
}