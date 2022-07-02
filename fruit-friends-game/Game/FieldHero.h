//taeju Kwon
#pragma once
#include <vector>
#include <string>

#include "../Engine/GameObject.h"
#include "GameObjectTypes.h"
//#include "../Engine/Input.h"

//enum class FieldHero_status {
//	HP = 0,
//	Power,
//	Depence,
//	Heal,
//	Inteligence,
//	AttackSp,
//	Dexterity,
//	Luck,
//	Accuracy,
//	Critical,
//	BossAttack,
//	BadStatus,
//	AmplBuff,
//	IncreaseItem,
//	Revival_ND,
//};

//class FieldWorker;

class FieldHero : public GameObject
{
public:
	FieldHero(math::vec2 startPos);
	GameObjectType GetObjectType() override;
	std::string GetObjectTypeName() override;
	std::string GetInformName(int idx);

	int hero_random_status();
	int check_status(GameObject* object);

	void Update(double dt) override;
	void Draw(math::TransformMatrix displayMatrix) override;
	void SethInform();
	int GethInform(int idx);

	math::vec2 heroPos{ 0.f,0.f };

	struct HeroStatInform {
		//FieldHero_status stat; // Name should be changed
		std::string name;
		int value;
	};

	int return_type = 0;

private:
	class state_none : public State
	{
	private:
		bool change = false;
		double timer = 0;
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "state_none"; }
	};

	class state_Dot : public State
	{
	private:
		bool change = false;
		double timer = 0;
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "state_think"; }
	};

	/*class state_Question : public State
	{
	private:
		bool change = false;
		double timer = 0;
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "state_check"; }
	};

	class state_Bang : public State
	{
	private:
		bool change = false;
		double timer = 0;
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "state_check"; }
	};*/

	state_none none;
	state_Dot Dot;
	/*state_Question Quest;
	state_Bang Bang;*/
	std::vector<HeroStatInform> hero_stats;
	bool drawHero;
	int heart;
};