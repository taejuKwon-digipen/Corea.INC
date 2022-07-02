#pragma once
#include "../Engine/GameObject.h"
#include "GameObjectTypes.h"
#include "../Engine/Input.h"
#include "../Engine/Sprite.h"
#include "FieldNpcAnim.h"
#include "Music.h"

#include <filesystem>

using namespace coconut::math;

class NPC : public coconut::GameObject
{

public:
	NPC(glm::vec2 start_pos);
	virtual void Draw(coconut::math::TransformMatrix displayMatrix) override;
	void Update([[maybe_unused]] double dt);
	virtual void Destroy() { destroyObject = true; }


	glm::vec2 endpos = { 0,0 };
	GameObjectType GetObjectType() override { return GameObjectType::NPC; }
	std::string GetObjectTypeName() override { return "NPC"; }

	bool for_viewcheck = false;
	bool drawNPC = false;
	bool update = false;

	int isReleased = 0;
	InputMouse mouse;
	
private:

	class State_none : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "none"; }
	};

	class State_move : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "move"; }
	};

	bool destroyObject;
	bool changeState;
	State_none statenone;
	State_move statemove;

	Music sound;
};

class ITEM : public coconut::GameObject
{

public:
	ITEM(glm::vec2 start_pos);
	virtual void Draw(coconut::math::TransformMatrix displayMatrix) override;
	void Update([[maybe_unused]] double dt);
	virtual void Destroy() { destroyObject = true; }
	GameObjectType GetObjectType() override { return GameObjectType::ITEM; }
	std::string GetObjectTypeName() override { return "ITEM"; }
	int verifying_num = 0;
	bool drawItem = false;
private:
	bool destroyObject;
	glm::vec2 endpos;
	InputMouse mouse;

	bool update = false;

	class State_none : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "none"; }
	};
	class State_move : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "move"; }
	};
	State_none statenone;
	State_move statemove;
	bool changeState;

	Music sound;
};


class FIX : public coconut::GameObject
{

public:
	FIX(glm::vec2 start_pos);
	virtual void Draw(TransformMatrix displayMatrix) override;
	void Update([[maybe_unused]] double dt);
	virtual void Destroy() { destroyObject = true; }
	GameObjectType GetObjectType() override { return GameObjectType::FIX; }
	std::string GetObjectTypeName() override { return "FIX"; }

	bool drawfix = false;
	bool update = false;
	InputMouse mouse;

private:
	bool destroyObject;
	glm::vec2 endpos;

	class State_none : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "none"; }
	};
	class State_move : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "move"; }
	};
	State_none statenone;
	State_move statemove;
	bool changeState;

	Music sound;
};