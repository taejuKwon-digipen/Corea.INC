//taeju kwon

#pragma once

#include "GameObjectTypes.h"
#include "../Engine/GameObject.h"
#include "../Engine/Input.h"
#include "../Engine/Sprite.h"

class FieldWorker : public GameObject
{
public:
	FieldWorker(math::vec2 startPos);
	GameObjectType GetObjectType() override;
	std::string GetObjectTypeName() override;
	std::string GetInformName(int idx);
	int return_type = 0;
	InputKey Downkey;
	void Update(double dt) override;
	void Draw(math::TransformMatrix displayMatrix) override;

private:
	class state_none : public State
	{
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "none"; }
	};
	class state_down : public State
	{
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "UP"; }
	};

	state_none statenone;
	state_down statedown;
	static constexpr double velocity = 700;

	math::vec2 workerpos{ 1000.0, 600.0 };
	bool is_down;
	bool draw_worker;
};