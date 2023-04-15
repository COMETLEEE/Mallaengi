#pragma once

/// <summary>
/// 2022. 02. 21. MG
/// 
/// 케찹 방해물 만들기
/// </summary>
class KetchapTrap : public GameObject
{
public:
	KetchapTrap();
	virtual ~KetchapTrap();

private:
	// 게임 플레이어
	Player* mGamePlayer;

	bool mTrigger;

	// 초당 어느 정도의 거리를 이동하는가
	Vector2D mVelocity;

	// 케찹 먹을시 변동될 몸무게
	float mWeight;

	//	이 시간이 지나면, 케찹통 위치에서 케찹을 생성해낸다.
	float mCreateTime;

	float mTimer;
	
	// 중력
	float mGravity;

public:
	virtual void Update() override;
};