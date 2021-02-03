#include"ItemManager.h"

void ItemManager::Initialize()
{
	for (int i = 0; i < 5; i++)
	{
		Items[i].Initialize(0.0f, 0.0f);
	}
}

void ItemManager::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		if (Items[i].IsActive == false)
		{
			continue;
		}
		Items[i].Draw();
	}
}
Item* ItemManager::CreateItem(float x, float y)
{
	for (int i = 0; i < 5; i++)
	{
		if (Items[i].IsActive == false)
		{
			Items[i].Initialize(x, y);
			Items[i].IsActive = true;
			return &Items[i];
		}
	}
	return nullptr;
}

