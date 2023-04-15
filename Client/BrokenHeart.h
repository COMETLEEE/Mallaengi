#pragma once

#define SPEED 1500.f

/// <summary>
/// 브로큰 하트. 아래에 캐릭터가 인식되면 스프라이트 변경 후 하강. 닿으면 즉사
/// 
/// 2022. 02. 24. Comet
/// </summary>
class BrokenHeart : public GameObject
{
public:
	BrokenHeart();
	virtual ~BrokenHeart();

	Player* mGamePlayer;

	bool mTrigger;

	Sprite* mChangeSprite;

public:
	virtual void Update() override;
	virtual void Release() override;
};