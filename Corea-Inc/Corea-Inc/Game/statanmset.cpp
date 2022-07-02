#include "statanmset.h"

statanm::statanm(math::vec2 startpos)
{
	/*switch (status)
	{
	case Hero::herostat::hp:
		AddGOComponent(new Sprite("assets/stat/hp.spt", this));
		break;
	case Hero::herostat::attack:
		AddGOComponent(new Sprite("assets/stat/attack.spt", this));
		break;
	case Hero::herostat::luck:
		AddGOComponent(new Sprite("assets/stat/luck.spt", this));
		break;
	case Hero::herostat::intelligence:
		AddGOComponent(new Sprite("assets/stat/intel.spt", this));
		break;
	}*/
	GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::None_Anim));
}

std::string statanm::GetInformName(int idx)
{
	return std::string();
}

std::string statanm::GetObjectTypeName()
{
	return "change_stat";
}

void statanm::Update(double dt)
{
	GameObject::Update(dt);
}

void statanm::Draw(math::TransformMatrix displayMatrix)
{
	GameObject::Draw(displayMatrix);
}

void statanm::changestats(Hero::herostat stat, int value)
{
	switch (stat)
	{
	case Hero::herostat::hp:
		AddGOComponent(new Sprite("assets/stat/hp.spt", this));
		break;
	case Hero::herostat::attack:
		AddGOComponent(new Sprite("assets/stat/attack.spt", this));
		break;
	case Hero::herostat::luck:
		AddGOComponent(new Sprite("assets/stat/luck.spt", this));
		break;
	case Hero::herostat::intelligence:
		AddGOComponent(new Sprite("assets/stat/intel.spt", this));
		break;
	}

	int num = value / 10;

	switch (num)
	{
	case 0:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::None_Anim));
		break;
	case 1:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::plus1_Anim));
		break;
	case 2:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::plus2_Anim));
		break;
	case 3:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::plus3_Anim));
		break;
	case 4:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::plus4_Anim));
		break;
	case 5:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::plus5_Anim));
		break;
	case 6:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::plus6_Anim));
		break;
	case 7:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::plus7_Anim));
		break;
	case 8:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::plus8_Anim));
		break;
	case 9:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::plus9_Anim));
		break;
	case 10:
		GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(statAnim::plus10_Anim));
		break;
	}
}
