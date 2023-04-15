#pragma once

class BlockBase;
class Platform;

// 움직이는 플랫폼은 등속운동으로 떨어집니다.
#define LR_MOVING_SPEED 70.f
#define LR_COLUMN_COUNT 4
#define LR_MOVING_TIME 3.f

/// <summary>
/// 좌, 우로 움직이는 Platform ..
/// 
/// 2022. 02. 10. Comet Lee
/// </summary>
class LRMovingPlatform : public GameObject
{
public:
	// 첫 블럭이 시작하는 위치를 받아서 가로로 정해진 갯수의 플랫폼을 설치합니다.
	LRMovingPlatform(Vector2D startPos, int moveTile, int column, float idleTime);
	virtual ~LRMovingPlatform();

private:
	std::vector<BlockBase*> mPlatforms;	// 밟긴 해야하니까 플랫폼들로 체크한다. 이 녀석들이 씬에 추가되어야 함.

	// 일정한 시간동안 우로 가고, 일정한 시간동안 좌로 가고 반복
	float mMoveTime;
	// 방향을 Control 합니다 ..
	int mDirControl;

	int mMoveTile;

	int mColumn;

	float mIdleTime;

	// 플레이어가 만약 이 플랫폼들 중 하나랑 충돌 중이라면, 좌표를 옮겨준다.

public:
	std::vector<BlockBase*>& GetPlatforms() { return mPlatforms; }

	virtual void FixedUpdate() override;

	virtual void Update() override;
};