#include "PreCompiledHeader.h"
#include "RedRight.h"

#include "Player.h"

RedRight::RedRight(Vector2D dir, float moveSpeed) :
mGamePlayer(Game::GetInstance().GetPlayer()),
mDirrection(dir),
mMoveSpeed(moveSpeed),
mTrigger(false)
{
	AddSpriteRenderer();

	AddAABBCollision();
}

RedRight::~RedRight()
{
}

void RedRight::Update()
{
	GameObject::Update();

	if (!mTrigger)
	{
		Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

		Vector2D myPos = mTransform->GetPosition();

		float dotProd = (playerPos - myPos).DotProduct(mDirrection);

		if ((0 <= dotProd) && (abs(playerPos.mY - myPos.mY) <= DETECTING))
			mTrigger = true;
	}
	else
	{
		mTransform->SetPosition(mTransform->GetPosition() + Timer::GetInstance().GetDeltaTime() / 1000.f * mMoveSpeed * mDirrection);

		std::vector<GameObject*> info = mCollision->GetCollisionInfo();

		for (GameObject* object : info)
		{
			if (object->GetTag() == "Player")
			{
				mGamePlayer->SetHp(0);
			}
		}
	}
}