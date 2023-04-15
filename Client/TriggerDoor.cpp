#include "PreCompiledHeader.h"
#include "TriggerDoor.h"

TriggerDoor::TriggerDoor() :
	mTotalWait(0.f)
{
}

TriggerDoor::~TriggerDoor()
{
}

void TriggerDoor::Update()
{
	BlockBase::Update();

	mTotalWait += Timer::GetInstance().GetDeltaTime() / 1000.f;

	// 4초 + 2초 20개 + 1초
	if (mTotalWait >= 4.f + 2.f * 20 + 1.f)
	{
		GetSpriteRenderer()->SetOpacity(GetSpriteRenderer()->GetOpacity() - 0.02f);

		if (GetSpriteRenderer()->GetOpacity() <= 0.f)
			Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);
	}
}