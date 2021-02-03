#include"RuleBaseAI.h"
#include"ItemManager.h"
#include <time.h>
#include <math.h>

RuleBaseAi::RuleBaseAi()
{
	Pos = Vec2(350.0f, 200.0f);

	Speed = 1.0f;
	Angle = 0.0f;
	Timer = 0;
	Step = 0;

	Direction = Vec2(0.0f, 0.0f);

	NowRules = Rule::Noen;
	ItemNumber = 0;
	FanItemNumber = 0;
	CircleItemNumber = 0;

	HitFan = false;
	HitCircle = false;
	HitLastTime = Rule::Noen;

	srand((unsigned int)time(NULL));
}
RuleBaseAi::~RuleBaseAi()
{

}

void RuleBaseAi::Update()
{
	switch (Step)
	{
	case 0:
		Wait();
		break;
	case 1:
		Move();
		break;
	default:
		break;
	}
}
void RuleBaseAi::Draw()
{
	Vec2 CenterPos = Vec2(Pos.X + Collision.AiSize.X / 2, Pos.Y + Collision.AiSize.Y / 2);

	//円
	Engine::DrawFan(CenterPos, 360.0f, CircleRadius, Angle, 0x900000ff);

	Engine::DrawTexture(Pos.X, Pos.Y, "Enemy", 255, 0.0f, 1.0f, 1.0f);
	//扇
	Engine::DrawFan(CenterPos, FanDegree, FanLengh, Angle, 0x90ff0000);
}

//待機
void RuleBaseAi::Wait()
{
	Timer++;
	if (Timer >= 120)
	{
		NowRules = Rule::Noen;
		HitFan = false;
		HitCircle = false;
		Timer = 298;
		Step = 1;
	}
}
//移動
void RuleBaseAi::Move()
{
	if (NowRules == Rule::Noen)
	{
		NowRules = OnOff();

		Timer++;

		if (Timer >= 300)
		{
			//角度
			Angle = rand() % 360;

			//ラジアン変換
			float rad = Angle * 3.14 / 180;

			Direction = Vec2(cosf(rad), sinf(rad));

			Timer = 0;
		}
		//移動
		Pos.X += Direction.X * Speed;
		Pos.Y += Direction.Y * Speed;

		//画面外にいかなくする
		if (Pos.X < 0.0f)   Pos.X = 0.0f;
		if (Pos.X > 592.0f) Pos.X = 592.0f;
		if (Pos.Y < 0.0f)   Pos.Y = 0.0f;
		if (Pos.Y > 432.0f) Pos.Y = 432.0f;
	}
	else if (NowRules == Rule::HitFanArea || NowRules == Rule::HitCircleArea)
	{
		//ベクトルの算出
		Vec2 Vector =
			Vec2((ItemManager::Instance()->Items[ItemNumber].Pos.X + Collision.ItemSize.X / 2.0f) - (Pos.X + Collision.AiSize.X / 2.0f),
				 (ItemManager::Instance()->Items[ItemNumber].Pos.Y + Collision.ItemSize.Y / 2.0f) - (Pos.Y + Collision.AiSize.Y / 2.0f));
		//単位ベクトルの算出
		float Length = sqrtf(Vector.X * Vector.X + Vector.Y * Vector.Y);
		Vec2 Normal = Vec2(Vector.X / Length, Vector.Y / Length);
	
		//移動
		Pos.X += Normal.X * Speed;
		Pos.Y += Normal.Y * Speed;

		//移動終了
		if (ItemManager::Instance()->Items[ItemNumber].IsActive == false)
		{
			Timer = 0;
			Step = 0;
		}

		//向いている角度
		Angle = atan(Vector.Y / Vector.X) * (180.0f / 3.14);
		if (Vector.X < 0)
		{
			Angle += 180;
		}
	}
}

//ルール(オン・オフ法)
Rule RuleBaseAi::OnOff()
{
	Vec2 CenterPos = Vec2(Pos.X + Collision.AiSize.X / 2, Pos.Y + Collision.AiSize.Y / 2);

	Vec2 CirclePos = Vec2(Pos.X + Collision.AiSize.X / 2.0f - CircleRadius,
						  Pos.Y + Collision.AiSize.Y / 2.0f - CircleRadius);
	Vec2 CircleSize = Vec2(CircleRadius * 2, CircleRadius * 2);
	
	//扇の探索判定
	for (int i = 0; i < 5; i++)
	{
		if (Collision.OnCollisionArcAndPoint(
			CenterPos,
			ItemManager::Instance()->Items[i].Pos,
			FanDegree,
			Angle,
			FanLengh,
			Collision.ItemSize) == true)
		{
			FanItemNumber = i;
			HitFan = true;
			break;
		}
	}
	
	//円の探索判定
	for (int i = 0; i < 5; i++)
	{
		if (Collision.OnCollisionCircleAndCircle(
			ItemManager::Instance()->Items[i].Pos,
			Collision.ItemSize,
			CirclePos,
			CircleSize) == true)
		{
			CircleItemNumber = i;
			HitCircle = true;
			break;
		}
	}

	//OnOffで返す
	if (HitFan == true && HitCircle == true)
	{
		if (HitLastTime != Rule::HitFanArea)
		{
			ItemNumber = FanItemNumber;
			HitLastTime = Rule::HitFanArea;
			return Rule::HitFanArea;
		}
		else
		{
			ItemNumber = CircleItemNumber;
			HitLastTime = Rule::HitCircleArea;
			return Rule::HitCircleArea;
		}
	}
	else if (HitFan == true)
	{
		ItemNumber = FanItemNumber;
		return Rule::HitFanArea;
	}
	else if (HitCircle == true)
	{
		ItemNumber = CircleItemNumber;
		return Rule::HitCircleArea;
	}
	
	return Rule::Noen;
}