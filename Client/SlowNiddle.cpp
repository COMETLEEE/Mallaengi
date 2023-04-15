#include "PreCompiledHeader.h"
#include "SlowNiddle.h"

SlowNiddle::SlowNiddle():
	mTrigger(false),
	mGamePlayer(Game::GetInstance().GetPlayer()),
	mTimer(0.f)
{
	AddSpriteRenderer()->SetOpacity(0.f);

	AddAABBCollision();
}

SlowNiddle::~SlowNiddle()
{

}

void SlowNiddle::Update()
{
	Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

	Vector2D myPos = mTransform->GetPosition();

	if ((!mTrigger) && (abs(playerPos.mX - myPos.mX) <= 1.5 * TILE_WIDTH) && (abs(playerPos.mY - myPos.mY) <= 1 * TILE_HEIGHT))
	{
		mTrigger = true;

		GetSpriteRenderer()->SetOpacity(1.f);
	}

	if (mTrigger)
	{
		mTimer += Timer::GetInstance().GetDeltaTime() / 1000.f;

		std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

		for (GameObject* object : info)
		{
			if (object->GetTag() == "Player")
			{
				mGamePlayer->SetHp(0);
			}
		}
	}

	if (mTimer >= DELETE_TIME)
	{
		float opa = GetSpriteRenderer()->GetOpacity() - 0.02f;

		GetSpriteRenderer()->SetOpacity(opa);

		if (GetSpriteRenderer()->GetOpacity() <= 0.f)
			Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);
	}
}