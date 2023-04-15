#pragma once

// 움직이는 플랫폼은 등속운동으로 떨어집니다.
#define UD_MOVING_SPEED 70.f
#define UD_COLUMN_COUNT 2
#define UD_MOVING_TIME 5.5f

class BlockBase;
class Platform;

/// <summary>
/// 위, 아래로 움직이는 Platform ..
/// 
/// 2022. 02. 11. Comet Lee
/// </summary>
class UDMovingPlatform : public GameObject
{
public:
	UDMovingPlatform(Vector2D startPos, int moveTile, int column, float idleTime, std::string type);
	virtual ~UDMovingPlatform();

private:
	std::vector<GameObject*> mPlatforms;

	float mMoveTime;

	int mDirControl;

	int mMoveTile;

	int mColumn;

	float mIdleTime;

	std::string mType;

public:
	std::vector<GameObject*>& GetPlatforms() { return mPlatforms; }

	virtual void FixedUpdate() override;

	virtual void Update() override;
};