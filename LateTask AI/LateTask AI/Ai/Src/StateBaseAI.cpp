#include"StateBaseAI.h"
#include"ItemManager.h"
#include <time.h>
#include <math.h>

StateBaseAi::StateBaseAi()
{
	Pos = Vec2(250.0f, 200.0f);

	Speed = 1.0f;
	Angle = 180.0f;
	Timer = 0;
	Step = 0;

	Direction = Vec2(0.0f, 0.0f);

	ItemNumber = 0;

	srand((unsigned int)time(NULL));
}
StateBaseAi::~StateBaseAi()
{

}

void StateBaseAi::Update()
{
	switch (Step)
	{
	case 0:
		Wait();
		break;
	case 1:
		Move();
		break;
	case 2:
		MoveItem();
		break;
	default:
		break;
	}
}
void StateBaseAi::Draw()
{
	Vec2 CenterPos = Vec2(Pos.X + 25.0f, Pos.Y + 25.0f);

	Engine::DrawTexture(Pos.X, Pos.Y, "Enemy", 255, 0.0f, 1.0f, 1.0f);
	//扇
	Engine::DrawFan(CenterPos, FanDegree, FanLengh, Angle, 0x9000ff00);
}

//待機
void StateBaseAi::Wait()
{
	Timer++;
	if (Timer >= 120)
	{
		Step = 1;
		Timer = -1;
	}

	Vec2 CenterPos = Vec2(Pos.X + Collision.AiSize.X / 2, Pos.Y + Collision.AiSize.Y / 2);

	if (ItemManager::Instance()->Items[ItemNumber].IsActive == true)
	{
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
				ItemNumber = i;
				Step = 2;
				break;
			}
		}
	}
}
//移動
void StateBaseAi::Move()
{
	Timer++;

	if (Timer == 0)
	{
		//角度
		Angle = rand() % 360;

		//ラジアン変換
		float rad = Angle * 3.14 / 180;

		Direction = Vec2(cosf(rad), sinf(rad));
	}
	//移動
	Pos.X += Direction.X * Speed;
	Pos.Y += Direction.Y * Speed;

	//画面外にいかなくする
	if (Pos.X < 0.0f)   Pos.X = 0.0f;
	if (Pos.X > 592.0f) Pos.X = 592.0f;
	if (Pos.Y < 0.0f)   Pos.Y = 0.0f;
	if (Pos.Y > 432.0f) Pos.Y = 432.0f;

	if (Timer >= 180)
	{
		Timer = 0;
		Step = 0;
	}

	Vec2 CenterPos = Vec2(Pos.X + Collision.AiSize.X / 2, Pos.Y + Collision.AiSize.Y / 2);

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
			ItemNumber = i;
			Step = 2;
			break;
		}
	}
}

void StateBaseAi::MoveItem()
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

		//距離
		Vec2 Distance = Vec2(ItemManager::Instance()->Items[ItemNumber].Pos.X - Pos.X,
			ItemManager::Instance()->Items[ItemNumber].Pos.Y - Pos.Y);

		//向いている角度
		Angle = atan(Vector.Y / Vector.X) * (180.0f / 3.14);
		if (Vector.X < 0)
		{
			Angle += 180;
		}
	
	//移動終了
	if (ItemManager::Instance()->Items[ItemNumber].IsActive == false)
	{
		Timer = -1;
		Step = 0;
	}
}