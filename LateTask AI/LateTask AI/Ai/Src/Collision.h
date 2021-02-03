#ifndef COLLISION_H
#define COLLISION_H

#include"Engine/Engine.h"

class Collision
{
public:
	Collision();
	~Collision();

public:
	//â~Ç∆â~ÇÃìñÇΩÇËîªíË
	bool OnCollisionCircleAndCircle(Vec2 obj1_pos, Vec2 obj1_size, Vec2 obj2_pos, Vec2 obj2_size);
	//ì_Ç∆êÓÇÃìñÇΩÇËîªíË
	bool OnCollisionArcAndPoint(Vec2 fanPos, Vec2 pointPos, float arcDegree, float rotateDegree, float lengh, Vec2 itemSize);

public:
	const Vec2 ItemSize = Vec2(45.0f, 45.0f);
	const Vec2 AiSize = Vec2(50.0f, 50.0f);
};

#endif // !COLLISION_H

