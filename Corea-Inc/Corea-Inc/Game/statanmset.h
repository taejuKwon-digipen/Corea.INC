#pragma once
#include "GameObjectTypes.h"
#include "Hero.h"
#include "../Engine/GameObject.h"
#include "../Engine/Sprite.h"

enum  class statAnim
{
	None_Anim,
	plus1_Anim,
	plus2_Anim,
	plus3_Anim,
	plus4_Anim,
	plus5_Anim,
	plus6_Anim,
	plus7_Anim,
	plus8_Anim,
	plus9_Anim,
	plus10_Anim,
};

class statanm : public coconut::GameObject
{
public:
	statanm(glm::vec2 startpos);
	GameObjectType override;
	std::string GetInformName(int idx);
	std::string GetObjectTypeName() override;
	void Update(double dt) override;
	void Draw(coconut::math::TransformMatrix displayMatrix) override;

	void changestats(Hero::herostat stat, int value);
	Hero::herostat status;
};