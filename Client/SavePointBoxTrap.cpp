#include "PreCompiledHeader.h"
#include "SavePointBoxTrap.h"

SavePointBoxTrap::SavePointBoxTrap(GameObject* object) :
	ItemBox(object, 1),
	mTrigger(false),
	mTimer(0.f),
	mMoveDist(0.f),
	mIsCreated(false),
	mIsDone(false),
	mCheckPoint(nullptr)
{
	mCheckPoint = new CheckPoint();
}

SavePointBoxTrap::~SavePointBoxTrap()
{

}

void SavePointBoxTrap::TriggerEvent()
{
	ItemBox::TriggerEvent();

	mCheckPoint->GetTransform()->SetPosition(mTransform->GetPosition());

	mTrigger = true;
}

void SavePointBoxTrap::Update()
{
	ItemBox::Update();

	if (mTrigger)
	{
		float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

		mTimer += delta;

		// 마요네즈가 튀어 나가고 3초 뒤에 떨어질 것이다.
		if ((mTimer >= CREATE_TIME) && (!mIsCreated))
		{
			Game::GetInstance().GetCurrentScene()->AddGameObject(mCheckPoint);

			mIsCreated = true;
		}

		if ((mIsCreated) && (!mIsDone))
		{
			mCheckPoint->GetTransform()->SetPosition(mCheckPoint->GetTransform()->GetPosition() - Vector2D(0.f, MOVE_DELTA));

			mMoveDist += MOVE_DELTA;

			// 이 박스의 모든 작업을 끝낸다.
			if (mMoveDist >= TILE_HEIGHT)
			{
				mCheckPoint = nullptr;
				mIsDone = true;
			}
		}
	}
}

void SavePointBoxTrap::Release()
{
	ItemBox::Release();

	if (mCheckPoint != nullptr)
		delete mCheckPoint;
}
