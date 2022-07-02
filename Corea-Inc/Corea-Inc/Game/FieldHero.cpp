#include "FieldHero.h"
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "FieldHeroine_Anim.h"
//#include "FieldWorker.h"


FieldHero::FieldHero(glm::vec2 startPos) : //add key for moving abd hero position vector
	GameObject(heroPos),
	heroPos(startPos),
	drawHero(true),
	heart(3)
{
	AddGOComponent(new coconut::Sprite("assets/FieldPart/Heroine/FieldHeroine.spt", this));
	currState = &Dot;
	currState->Enter(this);
}

GameObjectType FieldHero::GetObjectType() {
	return GameObjectType::FieldHero;
}

std::string FieldHero::GetObjectTypeName()
{
	return "FieldHero";
}

//void FieldHero::SethInform() {
//	hero_stats.push_back({ FieldHero_status::HP,"HP", 100 });
//	hero_stats.push_back({ FieldHero_status::Power, "Power", 100 });
//	hero_stats.push_back({ FieldHero_status::Depence, "Depence", 100 });
//	hero_stats.push_back({ FieldHero_status::Heal, "Heal", 100 });
//	hero_stats.push_back({ FieldHero_status::Inteligence, "Inteligence", 100 });
//	hero_stats.push_back({ FieldHero_status::AttackSp, "Attack Speed", 100 });
//	hero_stats.push_back({ FieldHero_status::Dexterity, "Dexterity", 100 });
//	hero_stats.push_back({ FieldHero_status::Luck, "Luck", 100 });
//	hero_stats.push_back({ FieldHero_status::Accuracy, "Accuracy", 100 });
//	hero_stats.push_back({ FieldHero_status::Critical, "Critical", 100 });
//	hero_stats.push_back({ FieldHero_status::BossAttack, "Boss Attack", 100 });
//	hero_stats.push_back({ FieldHero_status::BadStatus, "Bad Status", 100 });
//	hero_stats.push_back({ FieldHero_status::AmplBuff, "Amplification Buff", 100 });
//	hero_stats.push_back({ FieldHero_status::IncreaseItem, "Increase Item Drop", 100 });
//	hero_stats.push_back({ FieldHero_status::Revival_ND, "Revival without Debuff", 100 });
//
//}

int FieldHero::GethInform(int idx) {
	return hero_stats[idx].value;
}

std::string FieldHero::GetInformName(int idx) {
	return hero_stats[idx].name;
}


int FieldHero::check_status(GameObject* object)
{
	FieldHero* hero = static_cast<FieldHero*>(object);

	if (hero->currState == &hero->none)
	{
		return 0;
	}
	if (hero->currState == &hero->Dot)
	{
		return 1;
	}
	/*else if (hero->currState == &hero->Quest)
	{
		return 2;
	}
	else if (hero->currState == &hero->Bang)
	{
		return 3;
	}*/
}

//add hero basic function
void FieldHero::Update(double dt)
{
	drawHero = true;
	SetVelocity({ 0, 0 });
	SetPosition({ heroPos.x, heroPos.y });

	GameObject::Update(dt);
}

void FieldHero::Draw(coconut::math::TransformMatrix displayMatrix)
{
	if (drawHero == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

void FieldHero::state_none::Enter(GameObject* object) {
	FieldHero* hero = static_cast<FieldHero*>(object);
	hero->return_type = 0;
	hero->check_status(hero);
	hero->GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldHero_Anim::None_Anim));
}
void FieldHero::state_none::Update(GameObject* object, double dt) {
	timer += dt;
	if (timer >= 10)
	{
		change = true;
		timer = 0;
	}
}
void FieldHero::state_none::TestForExit(GameObject* object) {
	FieldHero* hero = static_cast<FieldHero*>(object);
	if (change == true)
	{
		hero->ChangeState(&hero->Dot);
	}
}

//////DOT///////

void FieldHero::state_Dot::Enter(GameObject* object) {
	FieldHero* hero = static_cast<FieldHero*>(object);
	hero->check_status(hero);
	hero->GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldHero_Anim::Walk_Anim));
}
void FieldHero::state_Dot::Update(GameObject* object, double dt) {
	timer += dt;
	if (timer >= 10)
	{
		change = true;
		timer = 0;
	}
}

void FieldHero::state_Dot::TestForExit(GameObject* object) {
	FieldHero* hero = static_cast<FieldHero*>(object);
	if (change == true)
	{
		//hero->ChangeState(&hero->Quest);
	}
}

//////Quest///////

//void FieldHero::state_Question::Enter(GameObject* object) {
//	FieldHero* hero = static_cast<FieldHero*>(object);
//	hero->return_type = 1;
//	hero->check_status(hero);
//	hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(FieldHero_Anim::Question_Anim));
//}
//void FieldHero::state_Question::Update(GameObject* object, double dt) {
//	timer += dt;
//}
//void FieldHero::state_Question::TestForExit(GameObject* object) {
//	FieldHero* hero = static_cast<FieldHero*>(object);
//	if (timer >= 10)
//	{
//		hero->ChangeState(&hero->Bang);
//	}
//}
//
////////Bang///////
//
//void FieldHero::state_Bang::Enter(GameObject* object) {
//	FieldHero* hero = static_cast<FieldHero*>(object);
//	hero->return_type = 1;
//	hero->check_status(hero);
//	hero->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(FieldHero_Anim::Bang_Anim));
//}
//void FieldHero::state_Bang::Update(GameObject* object, double dt) {
//	timer += dt;
//}
//void FieldHero::state_Bang::TestForExit(GameObject* object) {
//	FieldHero* hero = static_cast<FieldHero*>(object);
//	if (timer >= 10)
//	{
//		hero->ChangeState(&hero->none);
//	}
//}