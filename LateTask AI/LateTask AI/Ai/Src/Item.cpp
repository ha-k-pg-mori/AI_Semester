#include"Item.h"

void Item::Initialize(float x, float y)
{
	Pos = Vec2(x, y);
	IsActive = false;
}
void Item::Draw()
{
	Engine::DrawTexture(Pos.X, Pos.Y, "Item", 255, 0.0f, 5.0f, 5.0f);
	Engine::DrawRect(Pos.X + 22.5f, Pos.Y + 22.5f, 3.0f, 3.0f, 0x0000ff);
}