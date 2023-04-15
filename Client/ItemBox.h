#pragma once
#include "BoxBase.h"

/// <summary>
/// 밑에서 치면 아이템이 나오는 박스
/// </summary>
class ItemBox : public BoxBase
{
public:
	ItemBox(GameObject* reserveObject, int stage);
	virtual ~ItemBox();

	// 이 친구는 트리거가 되었을 때 만들어질 오브젝트입니다.
	GameObject* mReserveObject;

	int mStage;

public:

	virtual void TriggerEvent() override;
	virtual void Release() override;
};