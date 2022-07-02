#include "Potion.h"

#include <iostream>

#include "GameObjectTypes.h"
#include "../Engine/Engine.h"

Potion::Potion(glm::vec2 position, int stat, const char* potion1, const char* potion2) : position(position), stat(stat) {
	potionPtr = Engine::GetTextureManager().Load(potion1);
	potionPtr1 = Engine::GetTextureManager().Load(potion2);

	potionRect = { position, glm::vec2(position.x + potionPtr->GetSize().x, position.y + potionPtr->GetSize().y) };
	sound.glass();
}

bool Potion::didClicked()
{
	const double mouseX = Engine::GetWindow().mouseX;
	const double mouseY = Engine::GetWindow().mouseY;

	const bool XmouseOn = potionRect.Left() < mouseX && potionRect.Right() > mouseX;
	const bool YmouseOn = potionRect.Bottom() < mouseY && potionRect.Top() > mouseY;

	ismouseover = XmouseOn && YmouseOn;
	const bool clickedIt = ismouseover && wasclicked && !Engine::GetWindow().mouseIsPressed;
	wasclicked = Engine::GetWindow().mouseIsPressed;

	return clickedIt;
}

void Potion::Update(double dt) {
	double X = Engine::GetWindow().mouseX;
	double Y = Engine::GetWindow().mouseY;
	
	ismouseover = (X >= potionRect.Left() && X <= potionRect.Right() && Y >= potionRect.Bottom() && Y <= potionRect.Top());
	
	if (Engine::GetInput().IsMouseReleased(InputMouse::MouseButtons::Left) == true) {
		if (ismouseover == true) {
			if (ischoiced == false) {
				ischoiced = true;
				Engine::GetLogger().LogVerbose(Part::Item, "choiced");
			}
			else if (ischoiced == true) {
				ischoiced = false;
				Engine::GetLogger().LogVerbose(Part::Item, "not choiced");
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
		potionPtr1->Draw(coconut::math::TranslateMatrix(position));
	}
	else
	{
		potionPtr->Draw(coconut::math::TranslateMatrix(position));
	}

	if (didClicked() == true) {
		sound.GLASS.play();
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