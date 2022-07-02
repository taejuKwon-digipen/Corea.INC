#include "FieldButton.h"
#include "../Engine/Engine.h"
#include <iostream>

NPC::NPC(glm::vec2 start_pos) : GameObject(start_pos), mouse(InputMouse::MouseButtons::Left)
{
	AddGOComponent(new coconut::Sprite("assets/FieldPart/npc-top.spt", this));
	glm::vec2 newPosition = { 0,0 };
	SetPosition(newPosition);
	start_pos = { 0.0,0.0 };
	GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldNPC_Anim::None_Anim));
	currState = &statenone;
	changeState = false;
	currState->Enter(this);
	sound.field_button();
}

void NPC::Draw(TransformMatrix displayMatrix)
{
	if (drawNPC == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

void NPC::Update([[maybe_unused]]double dt)
{
	if (Engine::GetWindow().mouseX <= 1230 && Engine::GetWindow().mouseX >= 1080 &&
		Engine::GetWindow().mouseY <= 671 && Engine::GetWindow().mouseY >= 521)
	{
		if (mouse.IsMouseClicked())
		{
			sound.FIELD_BUTTON.play();
			update = true;
		}
	}

	if (update == true)
	{
		GameObject::Update(dt);
	}
	
}

void NPC::State_none::Enter(GameObject* object)
{
	NPC* npc = static_cast<NPC*>(object);
	npc->GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldNPC_Anim::None_Anim));
}

void NPC::State_none::Update(GameObject* object, double dt)
{
	NPC* npc = static_cast<NPC*>(object);
	if (npc->mouse.IsMouseClicked())
	{
		npc->drawNPC = false;
		npc->changeState = true;
	}
	
}

void NPC::State_none::TestForExit(GameObject* object)
{
	NPC* npc = static_cast<NPC*>(object);

	if (npc->changeState == true)
	{
		npc->drawNPC = false;
		npc->ChangeState(&npc->statemove);
	}
}

//======================//
void NPC::State_move::Enter(GameObject* object)
{
	NPC* npc = static_cast<NPC*>(object);
	npc->GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldNPC_Anim::None_Anim));
}

void NPC::State_move::Update(GameObject* object, double dt)
{
	NPC* npc = static_cast<NPC*>(object);

	if (npc->mouse.IsMouseClicked() && npc->drawNPC == false)
	{
		npc->drawNPC = true;
		while (npc->mouse.IsMouseReleased() && npc->drawNPC == true)
		{
			npc->UpdatePosition(glm::vec2((double)npc->mouse.MousePositionX(), (double)npc->mouse.MousePositionY()));
		}
	}
	if (npc->mouse.IsMouseClicked() && npc->drawNPC == true)
	{
		npc->endpos = glm::vec2((double)npc->mouse.MousePositionX(), (double)npc->mouse.MousePositionY());
		npc->SetPosition(npc->endpos);
		npc->for_viewcheck = true;
	}
	npc->changeState = false;

}

void NPC::State_move::TestForExit(GameObject* object)
{
	NPC* npc = static_cast<NPC*>(object);

	if (npc->mouse.IsMouseReleased())
	{
		npc->update = false;
		npc->ChangeState(&npc->statenone);
	}
}

//===================//

ITEM::ITEM(glm::vec2 start_pos) : GameObject(start_pos), mouse(InputMouse::MouseButtons::Left)
{
	AddGOComponent(new coconut::Sprite("assets/FieldPart/item.spt", this));
	currState = &statenone;
	glm::vec2 newPosition = { 0,0 };
	SetPosition(newPosition);
	start_pos = { 0.0,0.0 };
	GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldITEM_Anim::None_Anim));
	sound.field_button();
}

void ITEM::Draw(TransformMatrix displayMatrix)
{
	if (drawItem == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

void ITEM::Update(double dt)
{
	if (Engine::GetWindow().mouseX >= 1000 && Engine::GetWindow().mouseX <= 1150 &&
		Engine::GetWindow().mouseY >= 102 && Engine::GetWindow().mouseY <= 252)
	{
		if (mouse.IsMouseClicked())
		{
			sound.FIELD_BUTTON.play();
			update = true;
		}
	}

	if (update == true)
	{
		GameObject::Update(dt);
	}
}

void ITEM::State_none::Enter(GameObject* object)
{
	ITEM* item = static_cast<ITEM*>(object);
	item->GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldITEM_Anim::None_Anim));
}

void ITEM::State_none::Update(GameObject* object, double dt)
{
	ITEM* item = static_cast<ITEM*>(object);
	if (item->mouse.IsMouseClicked())
	{
		item->drawItem = false;
		item->changeState = true;
	}
}

void ITEM::State_none::TestForExit(GameObject* object)
{
	ITEM* item = static_cast<ITEM*>(object);

	if (item->changeState == true)
	{
		item->drawItem = false;
		item->ChangeState(&item->statemove);
	}
}

//======================//
void ITEM::State_move::Enter(GameObject* object)
{
	ITEM* item = static_cast<ITEM*>(object);
	item->GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldITEM_Anim::None_Anim));
}

void ITEM::State_move::Update(GameObject* object, double dt)
{
	ITEM* item = static_cast<ITEM*>(object);

	if (item->mouse.IsMouseClicked() && item->drawItem == false)
	{
		item->drawItem = true;
		while (item->mouse.IsMouseReleased() && item->drawItem == true)
		{
			item->UpdatePosition(glm::vec2((double)item->mouse.MousePositionX(), (double)item->mouse.MousePositionY()));
		}
	}
	if (item->mouse.IsMouseClicked() && item->drawItem == true)
	{
		item->endpos = glm::vec2((double)item->mouse.MousePositionX(), (double)item->mouse.MousePositionY());
		item->SetPosition(item->endpos);

	}
	item->changeState = false;
}

void ITEM::State_move::TestForExit(GameObject* object)
{
	ITEM* item = static_cast<ITEM*>(object);

	if (item->mouse.IsMouseReleased())
	{
		item->update = false;
		item->ChangeState(&item->statenone);
	}
}

//==========================//

FIX::FIX(glm::vec2 start_pos) : GameObject(start_pos), mouse(InputMouse::MouseButtons::Left)
{
	AddGOComponent(new coconut::Sprite("assets/FieldPart/fix.spt", this));
	currState = &statenone;
	glm::vec2 newPosition = { 0,0 };
	SetPosition(newPosition);
	start_pos = { 0.0,0.0 };
	GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldITEM_Anim::None_Anim));
	sound.field_button();
}

void FIX::Draw(TransformMatrix displayMatrix)
{
	if (drawfix == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

void FIX::Update(double dt)
{
	if (Engine::GetWindow().mouseX >= 200 && Engine::GetWindow().mouseX <= 350 &&
		Engine::GetWindow().mouseY >= 102 && Engine::GetWindow().mouseY <= 252)
	{
		if (mouse.IsMouseClicked())
		{
			sound.FIELD_BUTTON.play();
			update = true;
		}
	}

	if (update == true)
	{
		GameObject::Update(dt);
	}
}

void FIX::State_none::Enter(GameObject* object)
{
	FIX* fix = static_cast<FIX*>(object);
	fix->GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldITEM_Anim::None_Anim));
}

void FIX::State_none::Update(GameObject* object, double dt)
{
	FIX* fix = static_cast<FIX*>(object);
	if (fix->mouse.IsMouseClicked())
	{
		fix->drawfix = false;
		fix->changeState = true;
	}
}

void FIX::State_none::TestForExit(GameObject* object)
{
	FIX* fix = static_cast<FIX*>(object);
	if (fix->changeState == true)
	{
		fix->drawfix = false;
		fix->ChangeState(&fix->statemove);
	}
}

void FIX::State_move::Enter(GameObject* object)
{
	FIX* fix = static_cast<FIX*>(object);
	fix->GetGOComponent<coconut::Sprite>()->PlayAnimation(static_cast<int>(FieldITEM_Anim::None_Anim));
}

void FIX::State_move::Update(GameObject* object, double dt)
{
	FIX* fix = static_cast<FIX*>(object);

	if (fix->mouse.IsMouseClicked() && fix->drawfix == false)
	{
		fix->drawfix = true;
		while (fix->mouse.IsMouseReleased() && fix->drawfix == true)
		{
			fix->UpdatePosition(glm::vec2((double)fix->mouse.MousePositionX(), (double)fix->mouse.MousePositionY()));
		}
	}
	if (fix->mouse.IsMouseClicked() && fix->drawfix == true)
	{
		fix->endpos = glm::vec2((double)fix->mouse.MousePositionX(), (double)fix->mouse.MousePositionY());
		fix->SetPosition(fix->endpos);
	}
	fix->changeState = false;
}

void FIX::State_move::TestForExit(GameObject* object)
{
	FIX* fix = static_cast<FIX*>(object);

	if (fix->mouse.IsMouseReleased())
	{
		fix->update = false;
		fix->ChangeState(&fix->statenone);
	}
}