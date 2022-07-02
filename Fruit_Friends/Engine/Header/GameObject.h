#pragma once
#include <string>
//#include "Vec2.h"	
#include "ComponentManager.h"
//#include "../Header/TransformMatrix.h"

namespace coconut {
	enum class GameObjectType;
	class Component;

	class GameObject {
		friend class Sprite;
	public:
		GameObject();
		GameObject(glm::vec2 position);
		GameObject(glm::vec2 position, float rotation, glm::vec2 scale);
		virtual ~GameObject();
		void Destroy() { destroyObject = true; }
		bool ShouldDestroy() { return destroyObject; }

		virtual void Update(double dt);
		virtual void Draw(glm::mat3 displayMatrix);
		virtual GameObjectType GetObjectType() = 0;
		virtual std::string GetObjectTypeName() = 0;
		virtual bool CanCollideWith(GameObjectType objectBType);
		bool DoesCollideWith(GameObject* objectB);
		bool DoesCollideWith(glm::vec2 point);
		virtual void ResolveCollision(GameObject*);

		const glm::vec2& GetPosition() const;
		const glm::vec2& GetVelocity() const;
		const glm::vec2& GetScale() const;
		float GetRotation() const;
		//const glm::mat3& GetMatrix();

		void SetPosition(glm::vec2 newPosition);

		template<typename T>
		T* GetGOComponent() { return components.GetComponent<T>(); }
	protected:
		void AddGOComponent(Component* component) { components.AddComponent(component); }
		void UpdateGOComponents(double dt) { components.UpdateAll(dt); }
		void ClearGOComponents() { components.Clear(); }
		template<typename T>
		void RemoveGOComponent() { components.RemoveComponent<T>(); }

		class State {
		public:
			virtual void Enter(GameObject* object) = 0;
			virtual void Update(GameObject* object, double dt) = 0;
			virtual void TestForExit(GameObject* object) = 0;
			virtual std::string GetName() = 0;
		};
		class State_Nothing : public State {
		public:
			void Enter(GameObject*) override {}
			void Update(GameObject*, double) override {}
			void TestForExit(GameObject*) override {}
			std::string GetName() override { return ""; }
		};
		State_Nothing state_nothing;

		void UpdatePosition(glm::vec2 addPosition);
		void SetVelocity(glm::vec2 newVelocity);
		void UpdateVelocity(glm::vec2 newVelocity);
		void SetScale(glm::vec2 newScale);
		void SetRotation(float newRotationAmount);
		void UpdateRotation(float adjustRotation);
		void ChangeState(State* newState);

		State* currState;

	private:
		//math::TransformMatrix objectMatrix;
		bool updateMatrix;

		float rotation;
		glm::vec2 scale;
		glm::vec2 position;
		glm::vec2 velocity;
		ComponentManager components;
		bool destroyObject;


	};

}
