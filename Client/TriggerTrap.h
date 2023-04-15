#pragma once

/// <summary>
/// 2. 캐릭터 충돌 트리거형 함정
/// 
/// 캐릭터와 충돌하면 캐릭터를 즉사시킨다. 즉, hp = 0을 만듭니다.
/// 
/// 2022. 02. 11. Comet Lee
/// </summary>
class TriggerTrap : public GameObject
{
public:
	TriggerTrap();
	TriggerTrap(Sprite* nextSprite);
	TriggerTrap(bool IsUp);
	virtual ~TriggerTrap();

	// 트리거가 되면 변동할 스프라이트
	Sprite* mNextSprite;

	// 튀어나오는 트리거인가
	bool mIsUp;

public:
	void FixedUpdate() override;

	void Update() override;

	virtual void Release() override;
};