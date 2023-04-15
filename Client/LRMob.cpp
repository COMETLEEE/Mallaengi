#include "PreCompiledHeader.h"
#include "LRMob.h"

#include "BlockBase.h"
#include "Platform.h"


LRMob::LRMob(std::string type, float moveSpeed) :
	OneWayMob(type, moveSpeed)
{

}

LRMob::~LRMob()
{

}

void LRMob::Update()
{
	OneWayMob::Update();

	if (mCurrentState != EnemyState::Run)
		return;

	std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

	for (GameObject* object : info)
	{
		BlockBase* block = dynamic_cast<BlockBase*>(object);

		if ((mDirrection.mX <= -0.f) && (block != nullptr) && (block->GetCollisionDir() == CollisionDir::RIGHT))
		{
			mDirrection.mX = 1.f;
		}
		else if ((mDirrection.mX >= 0.f) && (block != nullptr) && (block->GetCollisionDir() == CollisionDir::LEFT))
		{
			mDirrection.mX = -1.f;
		}
	}
}