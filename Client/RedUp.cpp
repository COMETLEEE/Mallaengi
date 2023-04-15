#include "PreCompiledHeader.h"
#include "RedUp.h"

#include "Player.h"

RedUp::RedUp(Vector2D dir, float moveSpeed):
	mGamePlayer(Game::GetInstance().GetPlayer()),
	mDirrection(dir),
	mMoveSpeed(moveSpeed),
	mTrigger(false),
	mHasLength(false)
{
	AddSpriteRenderer();

	AddAABBCollision();
}

RedUp::RedUp(Vector2D dir, float moveSpeed, float lengthDetection):
	mGamePlayer(Game::GetInstance().GetPlayer()),
	mDirrection(dir),
	mMoveSpeed(moveSpeed),
	mTrigger(false),
	mLengthDetection(lengthDetection),
	mHasLength(true)
{
	AddSpriteRenderer();

	AddAABBCollision();
}

RedUp::~RedUp()
{

}

void RedUp::Update()
{
	GameObject::Update();

	if (!mTrigger)
	{
		Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

		Vector2D myPos = mTransform->GetPosition();

		float dotProd = (playerPos - myPos).DotProduct(mDirrection);

		if ((0 <= dotProd) && (abs(playerPos.mX - myPos.mX) <= DETECTING))
		{
			if (!mHasLength)
				mTrigger = true;
			else
			{
				if (abs(playerPos.mY - myPos.mY) <= mLengthDetection)
					mTrigger = true;
			}
		}
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
