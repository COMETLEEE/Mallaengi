#pragma once

/// <summary>
/// 스테이지 3를 위한 포탈 (3-1 => ...)
/// 
/// 2022. 02. 24. Comet
/// </summary>
class ExitPortal : public GameObject
{
public:
	ExitPortal();
	virtual ~ExitPortal();
	
	bool mTrigger;

	float mTimer;

	bool mIsDone;

	Player* mGamePlayer;

public:
	virtual void Update() override;
};