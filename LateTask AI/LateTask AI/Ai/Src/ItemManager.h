#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "Engine/Engine.h"
#include "Item.h"

class ItemManager
{
public:
	// インスタンスを取得するためのゲッター
	static ItemManager* Instance()
	{
		// この変数がこのクラスの唯一のインスタンス
		static ItemManager instance;

		return &instance;
	}

public:
	void Initialize();
	void Draw();
	Item* CreateItem(float x, float y);

public:
	Item Items[5];

private:
	ItemManager(){}
};

#endif // !ITEM_MANAGER_H
