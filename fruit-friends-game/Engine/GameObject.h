#pragma once
#include <string>
#include "Vec2.h"	
#include "TransformMatrix.h"
#include "ComponentManager.h"

enum class GameObjectType;
class Component;

class GameObject {
	friend class Sprite;
public:
	GameObject();
	GameObject(math::vec2 position);
	GameObject(math::vec2 position, double rotation, math::vec2 scale);
	virtual ~GameObject();
	void Destroy() { destroyObject = true; }

	virtual void Update(double dt);
	virtual void Draw(math::TransformMatrix displayMatrix);
	virtual GameObjectType GetObjectType() = 0;
	virtual std::string GetObjectTypeName() = 0;

	const math::vec2& GetPosition() const;
	const math::vec2& GetVelocity() const;
	const math::vec2& GetScale() const;
	double GetRotation() const;
	const math::TransformMatrix& GetMatrix();

	void SetPosition(math::vec2 newPosition);

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

	void UpdatePosition(math::vec2 addPosition);
	void SetVelocity(math::vec2 newVelocity);
	void UpdateVelocity(math::vec2 newVelocity);
	void SetScale(math::vec2 newScale);
	void SetRotation(double newRotationAmount);
	void UpdateRotation(double adjustRotation);
	void ChangeState(State* newState);

	State* currState;

private:
	math::TransformMatrix objectMatrix;
	bool updateMatrix;

	double rotation;
	math::vec2 scale;
	math::vec2 position;
	math::vec2 velocity;
	ComponentManager components;
	bool destroyObject;
};