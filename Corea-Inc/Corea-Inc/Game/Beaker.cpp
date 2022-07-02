#include "Beaker.h"
#include "GameObjectTypes.h"
#include "../Engine/Engine.h"
#include <iostream>

Beaker::Beaker(glm::vec2 pos, int littersize, std::vector<const char*> beaker1, std::vector<const char*> beaker2) : position(pos), littersize(littersize) {
	
	if (littersize == 3 || littersize == 5) {
		for (int i = 0; i <= littersize; i++) {
			beakerPtr.push_back(Engine::GetTextureManager().Load(beaker1[i]));
			beakerPtr1.push_back(Engine::GetTextureManager().Load(beaker2[i]));
		}
	}
	else {
		beakerPtr.push_back(Engine::GetTextureManager().Load(beaker1[0]));
		beakerPtr1.push_back(Engine::GetTextureManager().Load(beaker2[0]));
	}
	remain = 0;

	beakerRect = { position, glm::vec2(position.x + beakerPtr[0]->GetSize().x, position.y + beakerPtr[0]->GetSize().y) };

	sound.water_pour();
}

void Beaker::Update(double dt) {
	const double X = Engine::GetWindow().mouseX;
	const double Y = Engine::GetWindow().mouseY;

	ismouseover = (X >= beakerRect.Left() && X <= beakerRect.Right() && Y >= beakerRect.Bottom() && Y <= beakerRect.Top());

	if (Engine::GetInput().IsMouseReleased(InputMouse::MouseButtons::Left) == true) {
		if (ismouseover == true) {
			if (ischoiced == false) {
				ischoiced = true;
			}
			else if (ischoiced == true) {
				ischoiced = false;			}
		}
	}
}

void Beaker::Draw() {
	if (ischoiced) {
		beakerPtr1[remain]->Draw(coconut::math::TranslateMatrix(position));
	}
	else {
		beakerPtr[remain]->Draw(coconut::math::TranslateMatrix(position));
	}
}

bool Beaker::didClicked() {
	const double mouseX = Engine::GetWindow().mouseX;
	const double mouseY = Engine::GetWindow().mouseY;

	const bool XmouseOn = beakerRect.Left() < mouseX && beakerRect.Right() > mouseX;
	const bool YmouseOn = beakerRect.Bottom() < mouseY && beakerRect.Top() > mouseY;

	ismouseover = XmouseOn && YmouseOn;
	const bool clickedIt = ismouseover && wasclicked && !Engine::GetWindow().mouseIsPressed;
	wasclicked = Engine::GetWindow().mouseIsPressed;

	return clickedIt;
}

void Beaker::Into(Beaker* beaker) {
	int _remain = 0;

	if (beaker->getSize() == 10) {
		remain = littersize;
	}
	else if (beaker->getSize() == 0) {
		remain = 0;
	}
	else if (littersize == 3 || littersize == 5 || beaker->getSize() == 3 || beaker->getSize() == 5) {
		_remain = beaker->getRemain();
 		remain += _remain;

		if (remain > littersize) {
			_remain = remain - littersize;
			remain = littersize;
		}
		else {
			_remain = 0;
		}
	}


	ischoiced = false;
	beaker->makeUnchoiced();

	left = _remain;
}

int Beaker::getLeft() {
	return left;
}

bool Beaker::IsChoiced() {
	return ischoiced;
}

int Beaker::getRemain() {
	return remain;
}

int Beaker::getSize() {
	return littersize;
}

void Beaker::makeUnchoiced() {
	ischoiced = false;
}

void Beaker::updateRemain(int _remain) {
	remain = _remain;
}