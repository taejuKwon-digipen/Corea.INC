#include "../Header/Engine.h"
#include "../Header/GameObject.h"
#include "../Header/Sprite.h"
//#include "../Header/Collision.h"
//#include "../Header/Header.h"
//#include "../Header/ShowCollision.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace coconut;

GameObject::GameObject() : GameObject({ 0,0 }) {}

GameObject::GameObject(glm::vec2 position) : GameObject(position, 0, { 1, 1 }) {}

GameObject::GameObject(glm::vec2 position, float rotation, glm::vec2 scale)
	: velocity{ 0,0 }, position(position), updateMatrix(true),
	scale(scale), rotation(rotation), currState(&state_nothing) {}

GameObject::~GameObject() {
	ClearGOComponents();
}

void GameObject::Update(double dt) {
	currState->Update(this, dt);
	if (velocity.x != 0 || velocity.y != 0) {
		UpdatePosition(velocity/* * dt*/);
	}
	UpdateGOComponents(dt);
	currState->TestForExit(this);
}

void GameObject::ChangeState(State* newState) {
	currState = newState;
	currState->Enter(this);
}

void GameObject::Draw(glm::mat3 displayMatrix) {
	Sprite* spritePtr = GetGOComponent<Sprite>();
	if (spritePtr != nullptr) {
		spritePtr->Draw(displayMatrix * GetMatrix());
	}
	ShowCollision* showCollisionPtr = Engine::GetGSComponent<ShowCollision>();
	if (showCollisionPtr != nullptr && showCollisionPtr->IsEnabled() == true) {
		Collision* collisionPtr = GetGOComponent<Collision>();
		if (collisionPtr != nullptr) {
			collisionPtr->Draw(displayMatrix);
		}
	}
}

const glm::vec2& GameObject::GetPosition() const { return position; }
const glm::vec2& GameObject::GetVelocity() const { return velocity; }
const glm::vec2& GameObject::GetScale() const { return scale; }
float GameObject::GetRotation() const { return rotation; }

//const glm::mat3& GameObject::GetMatrix() {
//	glm::mat3 Position = glm::scale(glm::mat4(1.0f), glm::vec3(GetPosition().x, GetPosition().y, 1));
//	glm::mat4 Roatate;
//	glm::rotate(rotation, Roatate);
//	
//	
//	if (updateMatrix == true) {
//		//objectMatrix = glm::translate(position) * glm::roatate(rotation) * glm::scale(scale);
//		updateMatrix = false;
//	}
//	return objectMatrix;
//}

void GameObject::SetPosition(glm::vec2 newPosition) {
	position = newPosition;
	updateMatrix = true;
}

void GameObject::SetVelocity(glm::vec2 newVelocity) {
	velocity = newVelocity;
}

void GameObject::UpdateVelocity(glm::vec2 newVelocity) {
	velocity += newVelocity;
}

void GameObject::UpdatePosition(glm::vec2 addPosition) {
	position += addPosition;
	updateMatrix = true;
}

void GameObject::SetScale(glm::vec2 newScale) {
	scale = newScale;
	updateMatrix = true;
}

void GameObject::SetRotation(float newRotationAmount) {
	rotation = newRotationAmount;
	updateMatrix = true;
}
void GameObject::UpdateRotation(float adjustRotation) {
	rotation += adjustRotation;
	updateMatrix = true;
}

bool GameObject::CanCollideWith(GameObjectType) {
	return false;
}

//bool GameObject::DoesCollideWith(GameObject* objectB) {
//	return GetGOComponent<Collision>() != nullptr && objectB->GetGOComponent<Collision>() != nullptr
//		&& GetGOComponent<Collision>()->DoesCollideWith(objectB);
//}
//
//bool GameObject::DoesCollideWith(math::vec2 point) {
//	return GetGOComponent<Collision>() != nullptr && GetGOComponent<Collision>()->DoesCollideWith(point);
//}

void GameObject::ResolveCollision(GameObject*) {
	Engine::GetLogger().LogError(Part::Entire,"Base class collision resolution should not be called");
}