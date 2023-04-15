#include "PreCompiledHeader.h"
#include "FallingDum.h"

FallingDum::FallingDum(std::string type, int isFalling)
	: FreeEnemy(type, isFalling, 400.f)
{
}

FallingDum::~FallingDum()
{
}

void FallingDum::FixedUpdate()
{
	EnemyBase::FixedUpdate();
}

void FallingDum::Update()
{
	EnemyBase::Update();

	std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

	for (GameObject* object : info)
	{
		if (object->GetTag() == "Player")
			Game::GetInstance().GetPlayer()->SetHp(0);
	}
}