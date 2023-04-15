#include "PreCompiledHeader.h"
#include "FallingTriggerTrap.h"

#include "Player.h"

#define SPEED_OF_FALLING 1300.f

FallingTriggerTrap::FallingTriggerTrap(float speed):
TriggerTrap(),
mTrigger(false),
mSpeed(speed)
{
	// 플레이어의 위치를 감시하기 위해서.
	mGamePlayer = Game::GetInstance().GetPlayer();

	// 떨어지는 것이니까 ..
	GetSpriteRenderer()->SetSortOrder(8);
}

FallingTriggerTrap::~FallingTriggerTrap()
{
}

void FallingTriggerTrap::Update()
{
	// 아직 발동이 안되었다면 플레이어의 위치를 감시한다. 플레이어의 위치를 감사히다가 조건이 맞아서 발동되면 낙하 ..!
	if (!mTrigger)
	{
		// y 좌표는 나보다 아래에 있어야 하며 => 플레이어 y가 더 커야함
		// x 좌표가 겹쳐야함. => 그러면 트리거되서 떨어진다.
		Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

		Vector2D myPos = GetTransform()->GetPosition();

		D2D1_SIZE_F playerSize = dynamic_cast<AABBCollision*>(mGamePlayer->GetCollision())->GetSize();

		D2D1_SIZE_F mySize = dynamic_cast<AABBCollision*>(this->GetCollision())->GetSize();

		if ((playerPos.mY >= myPos.mY) && (abs(myPos.mX - playerPos.mX) <= playerSize.width / 2 + mySize.width / 2))
			mTrigger = true;
	}
	else if (mTrigger)
	{
		// 낙하를 실시한다.
		mTransform->SetPosition(mTransform->GetPosition() + (Timer::GetInstance().GetDeltaTime() / 1000.f) * mSpeed * Vector2D::Down);

		TriggerTrap::Update();
	}
}