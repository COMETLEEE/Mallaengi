#include "PreCompiledHeader.h";
#include "KillMayo.h"

KillMayo::KillMayo() :
	mMoveDist(0.f),
	mIsDone(false),
	mVelocityY(0.f),
	mTimer(0.f)
{
	AddAABBCollision();

	AddSpriteRenderer()->SetSortOrder(6);

	GetSpriteRenderer()->SetSprite(new Sprite(20103, Vector2D(0.5f, 0.5f), { TILE_WIDTH, TILE_HEIGHT }, 0.f, Vector2D(1200, 483)));
}

KillMayo::~KillMayo()
{
}

void KillMayo::Update()
{
	GameObject::Update();

	if (!mIsDone)
	{
		mTransform->SetPosition(mTransform->GetPosition() - Vector2D(0.f, MOVE_DELTA));

		mMoveDist += MOVE_DELTA;

		if (mMoveDist >= TILE_HEIGHT)
		{
			mIsDone = true;
		}
	}

	if (mIsDone)
	{
		float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

		mVelocityY = mVelocityY + GRAVITY * delta;

		mTimer += delta;

		mTransform->SetPosition(mTransform->GetPosition() + Vector2D(0.f, mVelocityY * delta));

		std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

		for (GameObject* object : info)
		{
			if (object->GetTag() == "Player")
			{
				Game::GetInstance().GetPlayer()->SetHp(0);
			}
		}

		if (mTimer >= 4.f)
			Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);
	}
}