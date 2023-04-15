#include "PreCompiledHeader.h"
#include "RidingNacho.h"

#include "Player.h"
#include "Platform.h"

RidingNacho::RidingNacho():
	mTrigger(false),
	mMoveDistance(0.f),
	mIsDone(false),
	mTimer(0.f)
{

}

RidingNacho::~RidingNacho()
{

}

void RidingNacho::Update()
{
	GameObject::Update();


	if (!mTrigger)
	{
		std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

		for (GameObject* object : info)
		{
			if ((object->GetTag() == "Player") && (mCollisionDir == CollisionDir::UP))
			{
				mTrigger = true;

				break;
			}
		}
	}

	if ((mTrigger) && (!mIsDone))
	{
		mTimer += Timer::GetInstance().GetDeltaTime() / 1000.f;

		if (mTimer <= 1.f)
			return;

		float dist = MOVE_SPEED * Timer::GetInstance().GetDeltaTime() / 1000.f;

		mTransform->SetPosition(mTransform->GetPosition() + dist * Vector2D::Up);

		mMoveDistance += dist;

		std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

		for (GameObject* object : info)
		{
			if ((object->GetTag() == "Player") && (mCollisionDir == CollisionDir::UP))
			{
				Player* player = Game::GetInstance().GetPlayer();

				player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + dist * Vector2D::Up);

				break;
			}
		}

		if (mMoveDistance >= 16 * TILE_HEIGHT)
		{
			mIsDone = true;
		}
	}
}