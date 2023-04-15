#pragma once
#include "EnemyBase.h"
#include "random"

#define ENEMY_MOVE_SPEED 150.f

/// <summary>
/// 자유형 몬스터 FSM, 플레이어 발에 머리를 밟히면 죽음.
///
///	2022. 02. 20. Comet
/// </summary>
class FreeEnemy : public EnemyBase
{
public:
	FreeEnemy(std::string type);
	FreeEnemy(std::string type,bool IsUpper);
	FreeEnemy(std::string type, int IsFalling, float MoveSpeed = 150.f);
	virtual ~FreeEnemy();

	// 햄버거냐 샌드백이냐
	std::string mType;

	// -1 : 왼쪽 / +1 : 오른쪽
	int mDirrection;

	// -1 : falling
	int mIsFalling;

	// Idle 상태일 때 멈춰있을 시간
	float mPauseTime;

	// Run 상태일 때 움직일 거리
	float mDistance;

	// 처음으로 이 상태에 들어왔는가.
	bool mIsFirstLoop;

	bool mIsUpper;

	// FAlling, Upper
	float mMoveSpeed;

	std::mt19937 mMt;

	std::uniform_int_distribution<int> mPauseDist;

	std::uniform_int_distribution<int> mDistanceDist;

private:
	virtual void LoadAnimationProcess() override;

	virtual void Idle() override;

	virtual void Run() override;

	virtual void Die() override;

public:
	std::string GetType() { return mType; }
};