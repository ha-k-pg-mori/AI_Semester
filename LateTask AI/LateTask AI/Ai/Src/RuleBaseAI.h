#ifndef RULEBASEAI_H
#define RULEBASEAI_H

#include "Engine/Engine.h"
#include "Collision.h"

enum class Rule
{
	HitFanArea,
	HitCircleArea,
	Noen,
};

class RuleBaseAi
{
public:
	RuleBaseAi();
	~RuleBaseAi();

	void Update();
	void Draw();

private:
	//待機
	void Wait();
	//移動
	void Move();

	//ルール(オン・オフ法)
	Rule OnOff();

public:
	Vec2 Pos;

private:
	float Speed;
	float Angle;//角度
	int Timer;
	int Step;

	Vec2 Direction;//移動時に使う向き
 
	Rule NowRules;//現在のルール
	int ItemNumber;//発見したアイテムの番号
	int FanItemNumber;//扇の発見したアイテムの番号
	int CircleItemNumber;//円の発見したアイテムの番号

	bool HitFan;
	bool HitCircle;
	Rule HitLastTime;

	const float FanLengh  = 200.0f;
	const float FanDegree = 30.0f;
	const float CircleRadius = 80.0f;

	Collision Collision;

	Vec2 ItemsPos[5];
};

#endif // !RULEBASEAI_H

