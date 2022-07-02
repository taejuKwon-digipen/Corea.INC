#include "Engine.h"
#include "GameObject.h"
#include "Sprite.h"

GameObject::GameObject() : GameObject({ 0,0 }) {}

GameObject::GameObject(math::vec2 position) : GameObject(position, 0, { 1, 1 }) {}

GameObject::GameObject(math::vec2 position, double rotation, math::vec2 scale)
	: velocity{ 0,0 }, position(position), updateMatrix(true),
	scale(scale), rotation(rotation), currState(&state_nothing) {
}

GameObject::~GameObject() {
	ClearGOComponents();
}

void GameObject::Update(double dt) {
	currState->Update(this, dt);
	if (velocity.x != 0 || velocity.y != 0) {
		UpdatePosition(velocity * dt);
	}
	UpdateGOComponents(dt);
	currState->TestForExit(this);
}

void GameObject::ChangeState(State* newState) {
	currState = newState;
	currState->Enter(this);
}

void GameObject::Draw(math::TransformMatrix displayMatrix) {
	Sprite* spritePtr = GetGOComponent<Sprite>();
	if (spritePtr != nullptr) {
		spritePtr->Draw(displayMatrix * GetMatrix());
	}
}

const math::vec2& GameObject::GetPosition() const { return position; }
const math::vec2& GameObject::GetVelocity() const { return velocity; }
const math::vec2& GameObject::GetScale() const { return scale; }
double GameObject::GetRotation() const { return rotation; }
const math::TransformMatrix& GameObject::GetMatrix() {
	if (updateMatrix == true) {
		objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotation) * math::ScaleMatrix(scale);
		updateMatrix = false;
	}
	return objectMatrix;
}

void GameObject::SetPosition(math::vec2 newPosition) {
	position = newPosition;
	updateMatrix = true;
}

void GameObject::SetVelocity(math::vec2 newVelocity) {
	velocity = newVelocity;
}

void GameObject::UpdateVelocity(math::vec2 newVelocity) {
	velocity += newVelocity;
}

void GameObject::UpdatePosition(math::vec2 addPosition) {
	position += addPosition;
	updateMatrix = true;
}

void GameObject::SetScale(math::vec2 newScale) {
	scale = newScale;
	updateMatrix = true;
}

void GameObject::SetRotation(double newRotationAmount) {
	rotation = newRotationAmount;
	updateMatrix = true;
}
void GameObject::UpdateRotation(double adjustRotation) {
	rotation += adjustRotation;
	updateMatrix = true;
}