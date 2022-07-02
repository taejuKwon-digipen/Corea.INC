#include "GreatPeople.h"
#include "../Engine/Sprite.h"

GreatPeople::GreatPeople(math::ivec2 startPos, int whoWillBe) :
	GameObject(static_cast<math::vec2>(startPos)), position(startPos)
{
	switch (static_cast<GreatPeoples>(whoWillBe))
	{
	case GreatPeoples::LeeSunsin:
		AddGOComponent(new Sprite("assets/Human-Resources/Great-People/LeeSunSin.spt", this));
		employerInfo = Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/LeeSunsin-Info.png");
		break;

	case GreatPeoples::LeeHwang:
		AddGOComponent(new Sprite("assets/Human-Resources/Great-People/LeeHwang.spt", this));
		employerInfo = Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/LeeHwang-Info.png");
		break;

	case GreatPeoples::DaeJanggeum:
		AddGOComponent(new Sprite("assets/Human-Resources/Great-People/DaeJanggeum.spt", this));
		employerInfo = Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/DaeJanggeum-Info.png");
		break;

	case GreatPeoples::KimGu:
		AddGOComponent(new Sprite("assets/Human-Resources/Great-People/KimGu.spt", this));
		employerInfo = Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/KimGu-Info.png");
		break;
	}
}

void GreatPeople::Draw(math::TransformMatrix displayMatrix)
{
	GameObject::Draw(displayMatrix);
	double mouseX = doodle::get_mouse_x();
	double mouseY = doodle::get_mouse_y();
	
	if (mouseX > position.x - size.x / 2 && mouseX < position.x + size.x / 2
		&& mouseY > position.y - size.y / 2 && mouseY < position.y + size.y / 2)
	{
		if (doodle::MouseIsPressed == true)
		{
			employerInfo->Draw(math::TranslateMatrix({ (Engine::GetWindow().GetSize() - employerInfo->GetSize()) / 2.f }));
		}
	}
}
