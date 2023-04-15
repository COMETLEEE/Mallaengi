#include "PreCompiledHeader.h"
#include "LRMovingPlatform.h"

// Platforms
#include "Platform.h"
#include "BlockBase.h"

LRMovingPlatform::LRMovingPlatform(Vector2D startPos, int moveTile, int column, float idleTime):
	mPlatforms(std::vector<BlockBase*>(column)),
	mMoveTime(0.f),
	mDirControl(1),
	mMoveTile(moveTile),
	mIdleTime(idleTime),
	mColumn(column)
{
	AddSpriteRenderer()->SetSortOrder(5);

	for (int i = 0; i < mColumn; i++)
	{
		mPlatforms[i] = new BlockBase();

		Transform* transform = mPlatforms[i]->GetTransform();

		transform->SetPosition(startPos + Vector2D(TILE_WIDTH * i, 0.f));

		Game::GetInstance().GetCurrentScene()->AddGameObject(mPlatforms[i]);
	}
}

LRMovingPlatform::~LRMovingPlatform()
{

}

void LRMovingPlatform::FixedUpdate()
{

}

void LRMovingPlatform::Update()
{
	float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

	mIdleTime -= delta;

	if (mIdleTime >= 0)
		return;

	mMoveTime += delta;

	if (LR_MOVING_SPEED * mMoveTime >= TILE_WIDTH * mMoveTile)
	{
		mMoveTime = 0;
		mDirControl *= -1;
	}

	// 모든 플랫폼들을 미리 설정한 초당 이동속도에 맞게 이동시켜줍니다.
	for (BlockBase* platform : mPlatforms)
	{
		Transform* transform = platform->GetTransform();

		transform->SetPosition(transform->GetPosition() + delta * mDirControl * Vector2D(LR_MOVING_SPEED, 0.f));
	}

	mTransform->SetPosition(mTransform->GetPosition() + delta * mDirControl * Vector2D(LR_MOVING_SPEED, 0.f));


	// 만약, 플랫폼 중, 플레이어와 상단 충돌 중인 녀석이 있다면, 플레이어의 위치도 옮겨줍니다.
	for (BlockBase* platform : mPlatforms)
	{
		std::vector<GameObject*> info = platform->GetCollision()->GetCollisionInfo();

		bool isChecked = false;

		for (GameObject* object : info)
		{
			// 플레이어와 충돌이 조금이라도 있었다면
			if ((object->GetTag() == "Player") && (platform->GetCollisionDir() == CollisionDir::UP))
			{
				object->GetTransform()->SetPosition(object->GetTransform()->GetPosition() + delta * mDirControl * Vector2D(LR_MOVING_SPEED, 0.f));

				isChecked = true;

				break;
			}
		}

		if (isChecked)
			break;
	}
}