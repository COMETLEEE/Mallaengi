#include "PreCompiledHeader.h"
#include "Food.h"

#include "Player.h"

#define MOVE_DELTA 90.f

float Food::mMallaengBar = -3.0f;

#define UP_DOWN_DIST 15.f

Food::Food(float weight, int ID,Vector2D pos, bool isInBox):
	mMoveDist(0.f),
mWeight(weight),
mID(ID),
mPos(pos),
mIsInBox(isInBox),
mDirrection(1),
mIsEaten(false),
mTotalMoveDist(0.f)
{
	AddAABBCollision();

	// 일단 도넛을 넣는다.
	AddSpriteRenderer()->SetSprite(new Sprite(mID, Vector2D(0.5f, 0.5f), {TILE_WIDTH, TILE_HEIGHT}, 0.f, mPos));

	GetSpriteRenderer()->SetSortOrder(7);
}

Food::~Food()
{
	
}

void Food::Update()
{
	GameObject::Update();

	float _delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

	if (mIsEaten)
	{
		if (GetSpriteRenderer()->GetOpacity() <= 0)
		{
			Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);
		}

		GetSpriteRenderer()->SetOpacity(GetSpriteRenderer()->GetOpacity() - 0.05f);

		return;
	}

	if ((mIsInBox) && (mMoveDist <= TILE_HEIGHT))
	{
		mTransform->SetPosition(mTransform->GetPosition() - _delta * Vector2D(0.f, MOVE_DELTA));
		
		mMoveDist += _delta * MOVE_DELTA;
	}
	else
	{
		// 위아래로 움직여
		mTransform->SetPosition(mTransform->GetPosition() + mDirrection * Vector2D(0.f, 0.15f));

		mTotalMoveDist += 0.15f;

		if (mTotalMoveDist >= UP_DOWN_DIST)
		{
			mDirrection *= -1;

			mTotalMoveDist = 0.f;
		}
	}

	std::vector<GameObject*> collisionInfo = GetCollision()->GetCollisionInfo();

	for (GameObject* object : collisionInfo)
	{
		if (object->GetTag() == "Player")
		{
			Game::GetInstance().GetPlayer()->PlusBodyWeight(mMallaengBar);
			SoundManager::GetInstance()->Play(500021);
			mIsEaten = true;
		}
	}
}