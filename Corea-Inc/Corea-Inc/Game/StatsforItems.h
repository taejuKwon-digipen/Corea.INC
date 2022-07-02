//#pragma once
//#include "../Engine/GameObject.h"
//#include "GameObjectTypes.h"
//
//enum class SfI /* stats for items */ {
//	Power = 0,         // 체력
//	Depence,
//	HP,
//	Heal,
//	Inteligence,
//	AttackSp,   // 공격속도
//	Dexterity,   // 민첩성
//	Luck,
//	Accuracy,   // 정확도
//	Critical,
//	BossAttack,
//	BadStatus,
//	AmplBuff,   // Amplification Buff 버프증가
//	IncreaseItem,
//	Revival_ND,   // Revival without debuff 디버프효과 없이 부활
//};
//
//class StatsforItem : public GameObject {
//public:
//	StatsforItem(math::vec2 startPos, SfI stat);
//	GameObjectType GetObjectType() override { return GameObjectType::Stats; }
//	std::string GetObjectTypeName() override { return "StatsforItems"; }
//};