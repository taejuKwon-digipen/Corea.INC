#include "../Engine/Engine.h"		//DrawTextToTexture
#include "../Engine/TransformMatrix.h"
#include "../Engine/Vec2.h"
#include "Score.h"
#include "Fonts.h"

Score::Score(int startingScore, Fonts fontToUse) : fontToUse(fontToUse), score(startingScore) {
	RenderText();
}

void Score::AddScore(int newPoints) {
	score += newPoints;
	RenderText();
}

void Score::Draw(math::ivec2 location) {
	scoreTexture.Draw(math::TranslateMatrix(location - math::ivec2{ 0, scoreTexture.GetSize().y }));
}

void Score::RenderText() {
	std::string scoreString = "Score: " + std::to_string(score);
	scoreTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}

//===============================================================================//

Boring::Boring(int startingScore, Fonts fontToUse) : fontToUse(fontToUse), bored(startingScore) {
	RenderText();
}

void Boring::Add(int newPoints) {
	bored += newPoints;
	RenderText();
}

void Boring::Draw(math::ivec2 location) {
	boredTexture.Draw(math::TranslateMatrix(location - math::ivec2{ 0, boredTexture.GetSize().y }));
}

void Boring::RenderText() {
	std::string scoreString = "Boring: " + std::to_string(bored);
	boredTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}

//===============================================================================//

Doupting::Doupting(int startingScore, Fonts fontToUse) : fontToUse(fontToUse), Doupt(startingScore) {
	RenderText();
}

void Doupting::Add(int newPoints) {
	Doupt += newPoints;
	RenderText();
}

void Doupting::Draw(math::ivec2 location) {
	douptTexture.Draw(math::TranslateMatrix(location - math::ivec2{ 0, douptTexture.GetSize().y }));
}

void Doupting::RenderText() {
	std::string scoreString = "Doupting: " + std::to_string(Doupt);
	douptTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}

//===============================================================================//

Tired::Tired(int startingScore, Fonts fontToUse) : fontToUse(fontToUse), tired(startingScore) {
	RenderText();
}

void Tired::Add(int newPoints) {
	tired += newPoints;
	RenderText();
}

void Tired::Draw(math::ivec2 location) {
	tiredTexture.Draw(math::TranslateMatrix(location - math::ivec2{ 0, tiredTexture.GetSize().y }));
}

void Tired::RenderText() {
	std::string scoreString = "Tired: " + std::to_string(tired);
	tiredTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}