#pragma once

/// <summary>
/// 다음 스테이지로 이동을 시키는 포탈
/// 
/// Next Stage로딩 씬으로 이동하면 될듯 ? (내러티브)
/// 
/// 2022. 02. 22. Comet
/// </summary>
class Portal : public GameObject
{
public:
	Portal();
	virtual ~Portal();

	bool mTrigger;

	float mTimer;

	bool mIsDone;

	Player* mGamePlayer;

public:
	virtual void Update() override;
};