#ifndef ITEM_H
#define ITEM_H

#include "Engine/Engine.h"

class Item
{
public:
	void Initialize(float x, float y);

	void Draw();

public:
	Vec2 Pos;
	bool IsActive;
};

#endif // !ITEM_H
