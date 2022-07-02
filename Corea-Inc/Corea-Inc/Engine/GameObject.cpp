#include "Engine.h"
#include "GameObject.h"
#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

coconut::GameObject::GameObject() : GameObject({0, 0}) {}

coconut::GameObject::GameObject(glm::vec2 position) : GameObject(position, 0, {1, 1}) {}

coconut::GameObject::GameObject(glm::vec2 position, float rotation, glm::vec2 scale)
	: currState(&state_nothing), updateMatrix(true),
	rotation(rotation), scale(scale), position(position), velocity{ 0, 0 } {}

coconut::GameObject::~GameObject()
{
	ClearGOComponent();
}

void coconut::GameObject::Update(double dt)
{
	currState->Update(this, dt);
	if (velocity.x != 0 || velocity.y != 0)
	{
		UpdatePosition(velocity);
	}
	UpdateGOComponent(dt);
	currState->TestForExit(this);
}

void coconut::GameObject::ChangeState(State* newState)
{
	currState = newState;
	currState->Enter(this);
}

void coconut::GameObject::Draw(math::TransformMatrix displayMatrix)
{
	Sprite* spritePtr = GetGOComponent<Sprite>();
	if (spritePtr != nullptr)
	{
		spritePtr->Draw(displayMatrix * GetMatrix());
	}
}

const glm::vec2& coconut::GameObject::GetPosition() const { return position; }
const glm::vec2& coconut::GameObject::GetVelocity() const { return velocity; }
const glm::vec2& coconut::GameObject::GetScale() const { return scale; }
float coconut::GameObject::GetRotation() const {	return rotation; }

const coconut::math::TransformMatrix& coconut::GameObject::GetMatrix()
{
	glm::mat3 Position = glm::scale(glm::mat4(1.f), glm::vec3(GetPosition().x, GetPosition().y, 1));
	if (updateMatrix == true)
	{
		objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotation) * math::ScaleMatrix(scale);
		updateMatrix = false;
	}
	return objectMatrix;
}

void coconut::GameObject::SetPosition(glm::vec2 newPosition)
{
	position = newPosition;
	updateMatrix = true;
}

void coconut::GameObject::SetVelocity(glm::vec2 newVelocity)
{
	velocity = newVelocity;
}

void coconut::GameObject::UpdateVelocity(glm::vec2 newVelocity)
{
	velocity += newVelocity;
}

void coconut::GameObject::UpdatePosition(glm::vec2 addPosition)
{
	position += addPosition;
	updateMatrix = true;
}

void coconut::GameObject::SetScale(glm::vec2 newScale)
{
	scale = newScale;
	updateMatrix = true;
}

void coconut::GameObject::SetRotation(float newRotationAmount)
{
	rotation = newRotationAmount;
	updateMatrix = true;
}

void coconut::GameObject::UpdateRotation(float adjustRotation)
{
	rotation += adjustRotation;
	updateMatrix = true;
}