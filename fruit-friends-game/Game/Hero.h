// Juhong Mo, Jihyeon Song
#pragma once
#include <vector>
#include <string>
#include "../Engine/GameObject.h"
#include "GameObjectTypes.h"
#include "../Engine/Input.h"

class Hero : public GameObject  {
public:
	enum class herostat {
		attack = 2,
		defence,
		hp,
		heal,
		intelligence,
		attspeed,
		agility,
		luck,
		accuracy,
		critical,
		bossattack,
		debuff,
		buff,
		increasetem,
		revival,
		count,
	};
	
	Hero(math::vec2 startPos);
	GameObjectType GetObjectType() override;
	std::string GetObjectTypeName() override;
	std::string GetInformName(int idx);

	void setStat(herostat stat, int value);
	int getStat(herostat stat);

	void Update(double dt) override;
	void Draw(math::TransformMatrix displayMatrix) override;
	int GethInform(int idx);
	
	math::vec2 heroPos{ 1000.0, 600.0 };

private:
	//std::vector<HeroStatInform> hero_stats;

	bool drawHero;
	int hero_stats[static_cast<int>(herostat::count)];

	InputKey rightKey;
	InputKey leftKey;
	InputKey jumpKey; //up
};
