#include"Run.h"
#include <time.h>
#include "ItemManager.h"

Run::Run()
{
	ItemManager::Instance()->Initialize();
	timer = 0;
	srand((unsigned int)time(NULL));
}
Run::~Run()
{

}

void Run::Update()
{
	timer++;
	if (timer >= 30)
	{
		ItemManager::Instance()->CreateItem(rand() % 590, rand() % 430);
		timer = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		if (Collision.OnCollisionCircleAndCircle(
			ItemManager::Instance()->Items[i].Pos,
			Collision.ItemSize,
			RuleBaseAI.Pos,
			Collision.AiSize) == true)
		{
			ItemManager::Instance()->Items[i].IsActive = false;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (Collision.OnCollisionCircleAndCircle(
			ItemManager::Instance()->Items[i].Pos,
			Collision.ItemSize,
			StateBaseAI.Pos,
			Collision.AiSize) == true)
		{
			ItemManager::Instance()->Items[i].IsActive = false;
		}
	}
	
	RuleBaseAI.Update();
	StateBaseAI.Update();
}
void Run::Draw()
{
	//•`‰æ
	Engine::StartDrawing(0);
	RuleBaseAI.Draw();
	StateBaseAI.Draw();
	ItemManager::Instance()->Draw();
	Engine::FinishDrawing();
}
