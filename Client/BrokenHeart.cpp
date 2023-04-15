#include "PreCompiledHeader.h"
#include "BrokenHeart.h"

#include "Player.h"

BrokenHeart::BrokenHeart() :
	mGamePlayer(Game::GetInstance().GetPlayer()),
	mTrigger(false),
	mChangeSprite(nullptr)
{
	AddSpriteRenderer();

	AddAABBCollision();
}

BrokenHeart::~BrokenHeart()
{

}

void BrokenHeart::Update()
{
	if (!mTrigger)
	{
		Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

		Vector2D myPos = mTransform->GetPosition();

		if ((playerPos.mY >= myPos.mY) && (abs(playerPos.mX - myPos.mX) <= 30.f))
		{
			mTrigger = true;

			if (mChangeSprite != nullptr)
			{
				delete GetSpriteRenderer()->GetSprite();
				GetSpriteRenderer()->SetSprite(mChangeSprite);
				mChangeSprite = nullptr;
			}
		}
	}
	else
	{
		mTransform->SetPosition(mTransform->GetPosition() + Timer::GetInstance().GetDeltaTime() / 1000.f * SPEED * Vector2D::Down);

		std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

		for (GameObject* object : info)
		{
			if (object->GetTag() == "Player")
			{
				mGamePlayer->SetHp(0);
			}
		}
	}
}

void BrokenHeart::Release()
{
	if (mChangeSprite != nullptr)
		delete mChangeSprite;
}