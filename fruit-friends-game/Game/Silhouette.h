// Geonhwi Sim

#pragma once
#include "../../library/include/doodle/input.hpp"
#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"
#include "../Engine/Engine.h"
#include "GameObjectTypes.h"
#include "Music.h"

class Silhouette : public Component
{	
public:
	struct Applicants
	{
		math::ivec2 side_feature;
		math::ivec2 pos;
		Texture* App;
	};
	std::vector<Applicants> appVec0;
	std::vector<Applicants> appVec1;
	
	enum class Back
	{
		SlanderMan = 0,
		SturdyMan,
		SturdyWoman,
		count,
	};

	enum class Front
	{
		SlanderMan = 0,
		SturdyMan,
		StudyWoman,
		count,
	};

	Silhouette();
	void Add(int stageNumb, Applicants app);
	void Draw(int stageNumb);
	void Update(double dt);
	void GetSilhouette();
	void checkAnswer();
	void checkAnswerHelper(bool whichOne, math::irect2 area, math::irect2 n0, math::irect2 n1, math::irect2 n2);
	std::vector<Applicants> GetCurrApp(int stageNumb);
	bool GetAnswerBool();
	void SetAnswerBool(bool setBool);
	bool GetIsDeadBool();
	void SetIsDeadBool(bool setBool);

private:
	int currStage;
	int lives;
	std::vector<Texture*> heartPtr;
	Texture* stampN;
	Texture* stamp;
	std::vector<Texture*> silPtr;
	bool showApp0{false}, showApp1{false}, showApp2{false}, showApp3{false};
	bool setComplelte{ false };
	bool AnswerBool{ false };
	bool isDead{ false };
	std::vector<bool> AnswerBoolVec;
	math::irect2 HRrect{ {760, 360}, {910, 470} };
	math::irect2 ITRect{ {912, 360}, {1060, 470} };
	math::irect2 ENRect{ {760, 210}, {910, 320} };
	math::irect2 FIRect{ {912, 210}, {1060, 320} };

	Music sfx;
};