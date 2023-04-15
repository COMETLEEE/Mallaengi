#include "PreCompiledHeader.h"
#include "FallingBlockTriggerTrap.h"

#include "Player.h"
#include "BlockBase.h"

// 추락형 함정은 등속운동으로 떨어집니다.
#define MAX_FALLING_SPEED 3000.f
#define PLUS_SPEED_PER_FRAME 1000.f

FallingBlockTriggerTrap::FallingBlockTriggerTrap(Vector2D startPos, int column) :
	GameObject(),
	mBlocks(std::vector<BlockBase*>(column)),
	mColumn(column),
	mTrigger(false),
	mGamePlayer(Game::GetInstance().GetPlayer()),
	mFallingSpeed(0.f),
	mTimer(0.f)
{
	AddSpriteRenderer();

	for (int i = 0 ; i < mColumn ; i++)
	{
		mBlocks[i] = new BlockBase();

		mBlocks[i]->GetTransform()->SetPosition(startPos + Vector2D(i * TILE_WIDTH, 0.f));

		Game::GetInstance().GetCurrentScene()->AddGameObject(mBlocks[i]);
	}
}

FallingBlockTriggerTrap::~FallingBlockTriggerTrap()
{

}

void FallingBlockTriggerTrap::Update()
{
	GameObject::Update();

	if (!mTrigger)
	{
		Vector2D myPos = mTransform->GetPosition();

		Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

		int halfWidth = mColumn * TILE_WIDTH / 2;

		if ((playerPos.mY >= myPos.mY + TILE_HEIGHT / 2) &&
			(abs(playerPos.mX - myPos.mX) <= PLAYER_WIDTH * PLAYER_SCALE / 2 + halfWidth - 20.f))
			mTrigger = true;
	}
	else
	{
		float deltaTime = Timer::GetInstance().GetDeltaTime() / 1000.f;
		mTimer += deltaTime;

		if (mTimer >= 10.f)
		{
			for (int i = 0; i < mColumn; i++)
			{
				Game::GetInstance().GetCurrentScene()->ReserveDestroy(mBlocks[i]);
			}

			Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);

			return;
		}

		if (mFallingSpeed < MAX_FALLING_SPEED)
			mFallingSpeed += PLUS_SPEED_PER_FRAME * deltaTime;

		mTransform->SetPosition(mTransform->GetPosition() + mFallingSpeed * Vector2D::Down * deltaTime);

		for (int i = 0 ; i < mColumn ; i++)
		{
			mBlocks[i]->GetTransform()->SetPosition(mBlocks[i]->GetTransform()->GetPosition() + mFallingSpeed * Vector2D::Down * deltaTime);

			std::vector<GameObject*> info = mBlocks[i]->GetCollision()->GetCollisionInfo();

			for (GameObject* object : info)
			{
				if (object->GetTag() == "Player")
				{
					mGamePlayer->SetHp(0);

					break;
				}
			}
		}
	}
}