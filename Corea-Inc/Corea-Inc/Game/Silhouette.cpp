// Geonhwi Sim

#include "Silhouette.h"
#include "../Engine/Sprite.h"

#include <iostream>

using namespace coconut;

Silhouette::Silhouette()
{
	lives = 3;
	showApp0 = false;
	showApp1 = false;
	showApp2 = false;
	showApp3 = false;
	setComplelte = false;
	AnswerBool = false;
	isDead = false;
	AnswerBoolVec.clear();

	stamp = Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/stamp.png");
	stampN = Engine::GetTextureManager().Load("assets/Human-Resources/Applicant/stamp_notyet.png");

	for (int i = 0; i != lives; i++)
	{
		heartPtr.push_back(Engine::GetTextureManager().Load("assets/life.png"));
	}

	sfx.page_turn();
	sfx.stamp();
}

void Silhouette::Add(int stageNumb, Applicants app)
{
	currStage = stageNumb;
	switch(stageNumb)
	{
	case 0:
		appVec0.push_back(app);
		break;

	case 1:
		appVec1.push_back(app);
		break;
	}
}

void Silhouette::Update(double dt)
{
	double X = Window::mouseX, Y = Window::mouseY;
	if (Window::mouseIsPressed == true)
	{
		if (Y > 470 && Y < 520) // Open the application document by clicking silhouette
		{
			sfx.PAGE_TURN.play();
			if (X > GetCurrApp(currStage)[0].pos.x + 120 && X < GetCurrApp(currStage)[0].pos.x + 200)
			{
				sfx.PAGE_TURN.play();
				showApp0 = true;
			}
			else if (X > GetCurrApp(currStage)[1].pos.x + 120 && X < GetCurrApp(currStage)[1].pos.x + 200)
			{
				sfx.PAGE_TURN.play();
				showApp1 = true;
			}
			else if (X > GetCurrApp(currStage)[2].pos.x + 120 && X < GetCurrApp(currStage)[2].pos.x + 200)
			{
				sfx.PAGE_TURN.play();
				showApp2 = true;
			}
			else if (X > GetCurrApp(currStage)[3].pos.x + 120 && X < GetCurrApp(currStage)[3].pos.x + 200)
			{
				sfx.PAGE_TURN.play();
				showApp3 = true;
			}
		}
		
		else if (Y > 525 && Y < 565 && X > 1060 && X < 1100) // Close by pressing X key
		{
			if (showApp0 == true || showApp1 == true || showApp2 == true || showApp3 == true)
			{
				showApp0 = false;
				showApp1 = false;
				showApp2 = false;
				showApp3 = false;
			}
		}
	}
	if (Window::mouseIsPressed == true && X < 10)
	{
		for (int i = 0; i != AnswerBoolVec.size(); i++)
		{
			//std::cout << AnswerBoolVec[i] << AnswerBoolVec.size() << std::endl;
		}
	}
	checkAnswer();
	if (lives == 0)
	{
		isDead = true;
		lives = 3;
	}
}


void Silhouette::Draw(int stageNumb)
{
	double X = Window::mouseX, Y = Window::mouseY;

	GetSilhouette();
	for (int i = 0; i < GetCurrApp(currStage).size(); i++)
	{
		silPtr[i]->Draw(coconut::math::TranslateMatrix(GetCurrApp(currStage)[i].pos));
	}

	if (showApp0 == true)
	{
		GetCurrApp(currStage)[0].App->Draw(coconut::math::TranslateMatrix(glm::ivec2{ 240, 40 }));
		showApp1 = false;
		showApp2 = false;
		showApp3 = false;
		if (setComplelte == true)
		{
			showApp0 = false;
			setComplelte = false;
		}
	}
	if (showApp1 == true)
	{
		GetCurrApp(currStage)[1].App->Draw(coconut::math::TranslateMatrix(glm::ivec2{ 240, 40 }));
		showApp0 = false;
		showApp2 = false;
		showApp3 = false;
		if (setComplelte == true)
		{
			showApp1 = false;
			setComplelte = false;
		}
	}
	if (showApp2 == true)
	{
		GetCurrApp(currStage)[2].App->Draw(coconut::math::TranslateMatrix(glm::ivec2{ 240, 40 }));
		showApp0 = false;
		showApp1 = false;
		showApp3 = false;
		if (setComplelte == true)
		{
			showApp2 = false;
			setComplelte = false;
		}
	}
	if (showApp3 == true)
	{
		GetCurrApp(currStage)[3].App->Draw(coconut::math::TranslateMatrix(glm::ivec2{ 240, 40 }));
		showApp0 = false;
		showApp1 = false;
		showApp2 = false;
		if (setComplelte == true)
		{
			showApp3 = false;
			setComplelte = false;
		}
	}

	switch (currStage)
	{
	case 0:
		checkAnswerHelper(showApp0, HRrect, ITRect, ENRect, FIRect);
		checkAnswerHelper(showApp1, ENRect, ITRect, HRrect, FIRect);
		checkAnswerHelper(showApp2, ITRect, HRrect, ENRect, FIRect);
		checkAnswerHelper(showApp3, FIRect, ITRect, HRrect, ENRect);
		break;

	case 1:
		checkAnswerHelper(showApp0, HRrect, ITRect, ENRect, FIRect);
		checkAnswerHelper(showApp1, FIRect, ITRect, HRrect, ENRect);
		checkAnswerHelper(showApp2, ENRect, HRrect, ITRect, FIRect);
		checkAnswerHelper(showApp3, ITRect, FIRect, HRrect, ENRect);
		break;
	}

	for (int i = 0; i != heartPtr.size(); i++)
	{
		heartPtr[i]->Draw(coconut::math::TranslateMatrix{ glm::ivec2{50 + i * 50, 710} });
	}
}

void Silhouette::GetSilhouette()
{
	for (int i = 0; i != GetCurrApp(currStage).size(); i++)
	{
		if (GetCurrApp(currStage)[i].side_feature.x == 0)
		{
			if (GetCurrApp(currStage)[i].side_feature.y == 0)
			{
				silPtr.push_back(Engine::GetTextureManager().Load("assets/Human-Resources/Silhouette/Slander_back.png"));
			}
			else if (GetCurrApp(currStage)[i].side_feature.y == 1)
			{
				silPtr.push_back(Engine::GetTextureManager().Load("assets/Human-Resources/Silhouette/Sturdy_back.png"));
			}
		}
	}
}

std::vector<Silhouette::Applicants> Silhouette::GetCurrApp(int stageNumb)
{
	std::vector<Applicants> currApp;
	switch (stageNumb)
	{
	case 0:
		currApp = appVec0;
		break;

	case 1:
		currApp = appVec1;
		break;
	}

	return currApp;
}

void Silhouette::checkAnswer()
{
	if(AnswerBoolVec.size() == 4)
	{
		if (AnswerBoolVec[0] == true && AnswerBoolVec[1] == true && AnswerBoolVec[2] == true && AnswerBoolVec[3] == true)
		{
			AnswerBool = true;
			AnswerBoolVec.clear();
		}
		else
		{
			AnswerBool = false;
			AnswerBoolVec.clear();
			lives--;
			heartPtr.pop_back();
		}
	}
}

void Silhouette::checkAnswerHelper(bool whichOne, math::irect2 area, math::irect2 n0, math::irect2 n1, math::irect2 n2) // I could fix this by using initializer list
{
	double X = Window::mouseX, Y = Window::mouseY;
	
	if (whichOne == true)
	{
		if (X > area.Left() && X < area.Right() && Y > area.Bottom() && Y < area.Top())
		{
			stampN->Draw(coconut::math::TranslateMatrix(glm::ivec2{ area.Left() + 5, area.Bottom() + 3 }));
			if (Window::mouseIsPressed == true) {
				stamp->Draw(coconut::math::TranslateMatrix(glm::ivec2{ area.Left() + 5, area.Bottom() + 3 }));
				AnswerBoolVec.push_back(true);
				setComplelte = true;
			}
		}
		else if (X > n0.Left() && X < n0.Right() && Y > n0.Bottom() && Y < n0.Top())
		{
			stampN->Draw(coconut::math::TranslateMatrix(glm::ivec2{ n0.Left() + 5, n0.Bottom() + 3 }));
			if (Window::mouseIsPressed == true) {
				stamp->Draw(coconut::math::TranslateMatrix(glm::ivec2{ n0.Left() + 5, n0.Bottom() + 3 }));
				AnswerBoolVec.push_back(false);
				setComplelte = true;
			}
		}
		else if (X > n1.Left() && X < n1.Right() && Y > n1.Bottom() && Y < n1.Top())
		{
			stampN->Draw(coconut::math::TranslateMatrix(glm::ivec2{ n1.Left() + 5, n1.Bottom() + 3 }));
			if (Window::mouseIsPressed == true) {
				stamp->Draw(coconut::math::TranslateMatrix(glm::ivec2{ n1.Left() + 5, n1.Bottom() + 3 }));
				AnswerBoolVec.push_back(false);
				setComplelte = true;
			}
		}
		else if (X > n2.Left() && X < n2.Right() && Y > n2.Bottom() && Y < n2.Top())
		{
			stampN->Draw(coconut::math::TranslateMatrix(glm::ivec2{ n2.Left() + 5, n2.Bottom() + 3 }));
			if (Window::mouseIsPressed == true) {
				stamp->Draw(coconut::math::TranslateMatrix(glm::ivec2{ n2.Left() + 5, n2.Bottom() + 3 }));
				AnswerBoolVec.push_back(false);
				setComplelte = true;
			}
		}
	}
}

bool Silhouette::GetAnswerBool()
{
	return AnswerBool;
}

void Silhouette::SetAnswerBool(bool setBool)
{
	AnswerBool = setBool;
}

bool Silhouette::GetIsDeadBool()
{
	return isDead;
}

void Silhouette::SetIsDeadBool(bool setBool)
{
	isDead = setBool;
}
