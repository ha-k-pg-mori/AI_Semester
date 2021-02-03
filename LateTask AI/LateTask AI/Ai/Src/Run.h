#ifndef RUN_H
#define RUN_H

#include "RuleBaseAI.h"
#include "StateBaseAI.h"
#include "Collision.h"

class Run
{
public:
	Run();
	~Run();
	void Update();
	void Draw();

private:
	int timer;

	RuleBaseAi  RuleBaseAI;
	StateBaseAi StateBaseAI;
	Collision Collision;
};


#endif // !RUN_H

