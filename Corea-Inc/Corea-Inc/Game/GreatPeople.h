#pragma once
#include "../Engine/Engine.h"
#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"
#include "GameObjectTypes.h"

class GreatPeople : public coconut::GameObject
{
public:
	enum class GreatPeoples
	{
		LeeSunsin = 0,
		LeeHwang,
		DaeJanggeum,
		KimGu,
		count,
	};
	
	GreatPeople(glm::ivec2 startPos, int whoWillBe);
	void Draw(coconut::math::TransformMatrix displayMatrix) override;
	GameObjectType GetObjectType() override { return GameObjectType::GreatPeople; }
	std::string GetObjectTypeName() override { return "GreatPeople"; }

	// void ShowEmployeeInfo(int whoWillBe);

private:
	glm::ivec2 size{ 150, 200 };
	glm::ivec2 position;

	coconut::Texture* employerInfo;
};
