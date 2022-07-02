#pragma once
#include "../../library/include/doodle/input.hpp"
#include "../Engine/Engine.h"
#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"
#include "GameObjectTypes.h"

class GreatPeople : public GameObject
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
	
	GreatPeople(math::ivec2 startPos, int whoWillBe);
	void Draw(math::TransformMatrix displayMatrix) override;
	GameObjectType GetObjectType() override { return GameObjectType::GreatPeople; }
	std::string GetObjectTypeName() override { return "GreatPeople"; }

	// void ShowEmployeeInfo(int whoWillBe);

private:
	math::ivec2 size{ 150, 200 };
	math::ivec2 position;

	Texture* employerInfo;
};
