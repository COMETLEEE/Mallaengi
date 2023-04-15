#include "PreCompiledHeader.h"
#include "DoorOpen.h"

#include "TriggerTrap.h"

DoorOpen::DoorOpen() :
	ItemBox(nullptr, 2),
	mTriggerTraps(std::vector<TriggerTrap*>(3)),
	mIsDone(false)
{
	for (int i = 0 ; i < mTriggerTraps.size() ; i++)
		mTriggerTraps[i] = new TriggerTrap();
}

DoorOpen::~DoorOpen()
{
}

void DoorOpen::Update()
{
	ItemBox::Update();

	// 트리거가 되면 삭제시킨다. 무엇을 ? 가로막고 있던 트리거 함정을
	if ((mTrigger) && (!mIsDone))
	{
		mTriggerTraps[1]->GetSpriteRenderer()->SetOpacity(mTriggerTraps[1]->GetSpriteRenderer()->GetOpacity() - 0.02f);

		if (mTriggerTraps[1]->GetSpriteRenderer()->GetOpacity() <= 0.f)
		{
			for (int i = 0 ; i < 3 ; i ++)
				Game::GetInstance().GetCurrentScene()->ReserveDestroy(mTriggerTraps[i]);

			mIsDone = true;
		}
	}
}