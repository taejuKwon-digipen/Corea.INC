#include "FieldWorker.h"
#include "../Engine/Engine.h"
#include "FieldWorker_Anim.h"

FieldWorker::FieldWorker(glm::vec2 startPos) : Downkey(InputKey::KeyboardButtons::Down),
GameObject(workerpos), workerpos(startPos){
	draw_worker = false;
	AddGOComponent(new coconut::Sprite("assets/FieldPart/FieldWorker.spt", this));
	GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldWorker_Anim::None_Anim));
	currState = &statenone;
	currState->Enter(this);
	is_down = false;
}

void FieldWorker::state_none::Enter(GameObject* object)
{
	FieldWorker* worker = static_cast<FieldWorker*>(object);
	worker->GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldWorker_Anim::None_Anim));
	worker->return_type = 1;
}

void FieldWorker::state_none::Update(GameObject* object, double dt){}
void FieldWorker::state_none::TestForExit(GameObject* object)
{
	FieldWorker* worker = static_cast<FieldWorker*>(object);
	if (worker->Downkey.IsKeyDown() == true)
	{
		worker->return_type = 2;
		worker->ChangeState(&worker->statedown);
	}
}



void FieldWorker::state_down::Enter(GameObject* object)
{
	FieldWorker* worker = static_cast<FieldWorker*>(object);
	worker->return_type = 2;
	worker->GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldWorker_Anim::Down_Anim));
}

void FieldWorker::state_down::Update(GameObject* object, double dt){}

void FieldWorker::state_down::TestForExit(GameObject* object)
{
	FieldWorker* worker = static_cast<FieldWorker*>(object);
	if (worker->Downkey.IsKeyReleased() == true)
	{	
		worker->ChangeState(&worker->statenone);
	}
}

GameObjectType FieldWorker::GetObjectType()
{
	return GameObjectType::FieldWorker;
}

std::string FieldWorker::GetObjectTypeName()
{
	return "FieldWorker";
}

void FieldWorker::Update(double dt)
{
	draw_worker = true;
	SetVelocity({ 0, 0 });
	SetPosition({ workerpos.x, workerpos.y });
	GameObject::Update(dt);
}

void FieldWorker::Draw(coconut::math::TransformMatrix displayMatrix)
{
	if (draw_worker == true)
	{
		GameObject::Draw(displayMatrix);
	}
}