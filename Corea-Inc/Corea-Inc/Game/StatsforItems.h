//#pragma once
//#include "../Engine/GameObject.h"
//#include "GameObjectTypes.h"
//
//enum class SfI /* stats for items */ {
//	Power = 0,         // ü��
//	Depence,
//	HP,
//	Heal,
//	Inteligence,
//	AttackSp,   // ���ݼӵ�
//	Dexterity,   // ��ø��
//	Luck,
//	Accuracy,   // ��Ȯ��
//	Critical,
//	BossAttack,
//	BadStatus,
//	AmplBuff,   // Amplification Buff ��������
//	IncreaseItem,
//	Revival_ND,   // Revival without debuff �����ȿ�� ���� ��Ȱ
//};
//
//class StatsforItem : public GameObject {
//public:
//	StatsforItem(math::vec2 startPos, SfI stat);
//	GameObjectType GetObjectType() override { return GameObjectType::Stats; }
//	std::string GetObjectTypeName() override { return "StatsforItems"; }
//};