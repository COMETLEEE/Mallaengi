#include "PreCompiledHeader.h"
#include "JumpEnemy.h"

JumpEnemy::JumpEnemy():
FreeEnemy("Dum")
{
}

JumpEnemy::~JumpEnemy()
{
}

void JumpEnemy::Update()
{
	FreeEnemy::Update();
}
