//Juhong Mo, Jihyeon Song

#include "Hero.h"
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
 

Hero::Hero(math::vec2 startPos) : //add key for moving abd hero position vector
GameObject(heroPos),
rightKey(InputKey::Keyboard::Right),
leftKey(InputKey::Keyboard::Left),
jumpKey(InputKey::Keyboard::Up),
heroPos(startPos),
drawHero(true)
{
	AddGOComponent(new Sprite("assets/heroine.spt", this));

	setStat(herostat::attack, 100);
	setStat(herostat::defence, 10);
	setStat(herostat::hp, 10);
	setStat(herostat::heal, 10);
	setStat(herostat::intelligence, 10);
	setStat(herostat::attspeed, 10);
	setStat(herostat::agility, 10);
	setStat(herostat::luck, 10);
	setStat(herostat::accuracy, 10);
	setStat(herostat::critical, 10);
	setStat(herostat::bossattack, 10);
	setStat(herostat::debuff, 10);
	setStat(herostat::buff, 10);
	setStat(herostat::increasetem, 10);
	setStat(herostat::revival, 10);
}

GameObjectType Hero::GetObjectType() {
	return GameObjectType::Hero;
}

std::string Hero::GetObjectTypeName()
{
	return "Hero";
}

//add hero basic function
void Hero::Update(double dt)
{
	drawHero = true;
	SetVelocity({ 0, 0 });
	SetPosition({ heroPos.x, heroPos.y });

	//moving hero : <-, -> and jump!
	if (rightKey.IsKeyDown() == true)
	{
		SetVelocity({ 10, 0 });
		UpdatePosition({ GetVelocity().x, GetVelocity().y });
	}
	else if (leftKey.IsKeyDown() == true)
	{
		SetVelocity({ -10, 0 });
		UpdatePosition({ GetVelocity().x, GetVelocity().y });
	}
	if (jumpKey.IsKeyDown() == true)
	{
		SetVelocity({ 0, 10 });
		UpdatePosition({ GetVelocity().x, GetVelocity().y });
	}
	GameObject::Update(dt);
}

void Hero::Draw(math::TransformMatrix displayMatrix)
{
	if (drawHero == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

void Hero::setStat(herostat stat, int value) {
	hero_stats[static_cast<int>(stat)] = value;
}

int Hero::getStat(herostat stat) {
	return hero_stats[static_cast<int>(stat)];
}