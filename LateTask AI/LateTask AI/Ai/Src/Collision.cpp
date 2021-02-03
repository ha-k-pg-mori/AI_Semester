#include"Collision.h"

Collision::Collision()
{

}
Collision::~Collision()
{

}

//‰~‚Æ‰~‚Ì“–‚½‚è”»’è
bool Collision::OnCollisionCircleAndCircle(Vec2 obj1_pos, Vec2 obj1_size, Vec2 obj2_pos, Vec2 obj2_size)
{
	//’†‰›
	Vec2 center_pos[] =
	{
		Vec2(obj1_pos.X + obj1_size.X / 2.0f,obj1_pos.Y + obj1_size.Y / 2.0f),
		Vec2(obj2_pos.X + obj2_size.X / 2.0f,obj2_pos.Y + obj2_size.Y / 2.0f),
	};

	//”¼Œa
	float obj1_radius = obj1_size.X / 2;
	float obj2_radius = obj2_size.Y / 2;

	//‹——£
	float a = center_pos[0].X - center_pos[1].X;
	float b = center_pos[0].Y - center_pos[1].Y;
	float c = sqrt(a * a + b * b);

	//”»’è
	if (c <= obj1_radius + obj2_radius)
	{
		//“–‚½‚Á‚Ä‚é
		return true;
	}
	//“–‚½‚Á‚Ä‚È‚¢
	return false;
}

bool Collision::OnCollisionArcAndPoint(Vec2 arcPos, Vec2 itemPos, float arcDegree, float rotateDegree, float lengh, Vec2 itemSize)
{
	Vec2 pointPos = Vec2(itemPos.X + ItemSize.X / 2, itemPos.Y + ItemSize.Y / 2);

	//‹——£
	float x = arcPos.X - pointPos.X;
	float y = arcPos.Y - pointPos.Y;
	float c = sqrt(x * x + y * y);

	//‰~‚Ì”ÍˆÍ“à‚©‚Ì”»’è
	if (lengh < c)
	{
		return false;
	}

	//îŒ^ŠJŽnü‚ÌŠp“x
	float sRad = D3DXToRadian(rotateDegree - arcDegree / 2);
	//îŒ^I—¹ü‚ÌŠp“x
	float eRad = D3DXToRadian(rotateDegree + arcDegree / 2);

	//‚»‚ê‚¼‚ê‚Ìsin,cos•ÏŠ·
	float sx = (float)sin(sRad);
	float sy = (float)cos(sRad);
	float ex = (float)sin(eRad);
	float ey = (float)cos(eRad);

	//Šp“x‚Ì”»’è
	if (sx * ey - ex * sy > 0) {
		if (sx * y - x * sy < 0) return false;
		if (ex * y - x * ey > 0) return false;
		return true;
	}
	else {
		if (sx * y - x * sy > 0) return true; 
		if (ex * y - x * ey < 0) return true; 
		return false;
	}
}