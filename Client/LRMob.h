#pragma once
#include "EnemyBase.h"
#include "OneWayMob.h"

/// <summary>
/// 왼쪽으로 가다가 벽 만나면 오른쪽으로 이동
/// 
/// 2022. 02. 24. Comet
/// </summary>
class LRMob : public OneWayMob
{
public :
	LRMob(std::string type, float moveSpeed);

	virtual ~LRMob();

public:
	virtual void Update() override;
};