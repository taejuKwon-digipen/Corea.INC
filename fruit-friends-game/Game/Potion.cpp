#include "Potion.h"

#include <iostream>

#include "GameObjectTypes.h"
#include "../Engine/Engine.h"

Potion::Potion(math::vec2 position, int stat, std::filesystem::path potion1, std::filesystem::path potion2) : position(position), stat(stat) {

	potionPtr = Engine::GetTextureManager().Load(potion1);
	potionPtr1 = Engine::GetTextureManager().Load(potion2);

	potionRect = { position, math::vec2(position.x + potionPtr->GetSize().x, position.y + potionPtr->GetSize().y) };
	//sound.glass();
}

bool Potion::didClicked()
{
	const double mouseX = doodle::get_mouse_x();
	const double mouseY = doodle::get_mouse_y();

	const bool XmouseOn = potionRect.Left() < mouseX && potionRect.Right() > mouseX;
	const bool YmouseOn = potionRect.Bottom() < mouseY && potionRect.Top() > mouseY;

	ismouseover = XmouseOn && YmouseOn;
	const bool clickedIt = ismouseover && wasclicked && !doodle::MouseIsPressed;
	wasclicked = doodle::MouseIsPressed;

	return clickedIt;
}

void Potion::Update(double dt) {
	double X = doodle::get_mouse_x();
	double Y = doodle::get_mouse_y();
	
	ismouseover = (X >= potionRect.Left() && X <= potionRect.Right() && Y >= potionRect.Bottom() && Y <= potionRect.Top());
	
	if (Engine::GetInput().IsMouseReleased(InputMouse::Mouse::Left) == true) {
		if (ismouseover == true) {
			if (ischoiced == false) {
				ischoiced = true;
				Engine::GetLogger().LogVerbose("choiced");
			}
			else if (ischoiced == true) {
				ischoiced = false;
				Engine::GetLogger().LogVerbose("not choiced");
			}
		}
	}

	//if (didClicked() == true) {

	//	sound.WATER_DROP.play();
	//}
}

void Potion::Draw() {	
	if (ischoiced)
	{
		potionPtr1->Draw(math::TranslateMatrix(position));
	} else
	{
		potionPtr->Draw(math::TranslateMatrix(position));
	}

	if (didClicked() == true) {
		//sound.GLASS.play();
	}
}

Hero::herostat Potion::GetStat() {
	return (Hero::herostat)stat;
}

bool Potion::IsChoiced() {
	return ischoiced;
}

void Potion::makeUnchoiced() {
	ischoiced = false;
}