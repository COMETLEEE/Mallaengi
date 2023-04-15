#pragma once
#include "BlockBase.h"

/// <summary>
/// 블럭이 파괴되었을 때 이펙트용 파편 객체
/// 
/// 2022. 02. 21
/// </summary>
class BlockFragment : public GameObject
{
	Vector2D		mDirection;		// 이동 방향
	float			mEffectSpeed;	// 이동 속도
	float			mDuration;		// 출력 시간
	float			mGravity;		// 중력

public:
	BlockFragment(Vector2D pos);
	virtual ~BlockFragment();

	virtual void Update() override;

	void SetDirection(Vector2D direction);
};

/// <summary>
/// 부술 수 있는 블록
/// 
/// 플레이어가 밑에서 위로 이동하는 이동 모션 중 (== 점프) 충돌을 감지했을 때 파괴된다.
/// 
/// 2022. 02. 08. Comet
/// </summary>
class BreakableBlock : public BlockBase
{
public:
	BreakableBlock();
	virtual ~BreakableBlock();

public:
	virtual void FixedUpdate() override;
	
	virtual void Update() override;

	void BreakBlock();
};