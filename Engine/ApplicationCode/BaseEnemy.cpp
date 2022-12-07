#include "BaseEnemy.h"

const float BaseEnemy::targetReactionTime = 60.0f;

void BaseEnemy::OnCollision()
{
	hp--;
}
