#include "GreatPeople.h"
#include "../Engine/Sprite.h"

GreatPeople::GreatPeople(glm::ivec2 startPos, int whoWillBe) :
	GameObject(static_cast<glm::vec2>(startPos)), position(startPos)
{
	switch (static_cast<GreatPeoples>(whoWillBe))
	{
	case GreatPeoples::LeeSunsin:
		AddGOComponent(new coconut::Sprite("assets/Human-Resources/Great-People/LeeSunSin.spt", this));
		employerInfo = Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/LeeSunsin-Info.png");
		break;

	case GreatPeoples::LeeHwang:
		AddGOComponent(new coconut::Sprite("assets/Human-Resources/Great-People/LeeHwang.spt", this));
		employerInfo = Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/LeeHwang-Info.png");
		break;

	case GreatPeoples::DaeJanggeum:
		AddGOComponent(new coconut::Sprite("assets/Human-Resources/Great-People/DaeJanggeum.spt", this));
		employerInfo = Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/DaeJanggeum-Info.png");
		break;

	case GreatPeoples::KimGu:
		AddGOComponent(new coconut::Sprite("assets/Human-Resources/Great-People/KimGu.spt", this));
		employerInfo = Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/KimGu-Info.png");
		break;
	}
}

void GreatPeople::Draw(coconut::math::TransformMatrix displayMatrix)
{
	GameObject::Draw(displayMatrix);
	double mouseX = Engine::GetInput().get_mouse_x();
	double mouseY = Engine::GetInput().get_mouse_y();	
	if (mouseX > position.x - size.x / 2 && mouseX < position.x + size.x / 2
		&& mouseY > position.y - size.y / 2 && mouseY < position.y + size.y / 2)
	{
		if (Engine::GetWindow().mouseIsPressed)
		{
			employerInfo->Draw(coconut::math::TranslateMatrix(glm::ivec2{ (Engine::GetWindow().GetSize().x/2 - employerInfo->GetSize().x, Engine::GetWindow().GetSize().y/2 - employerInfo->GetSize().y)}));
		}
	}
}
