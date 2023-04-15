#pragma once

/**
 * \brief : 트리거되면 날아가는 피존투 ~ 2022. 02. 21. Comet
 */
class TriggerPigeon : public GameObject
{
public:
	TriggerPigeon(std::string color);
	virtual ~TriggerPigeon();

private:
	std::string mColor;

	bool mTrigger;

	float mTimer;

	// 플레이어를 감시한다.
	Player* mGamePlayer;

	std::vector<AnimationClip*> mAnimationClips;

	void LoadAnimation();
	
public:
	virtual void FixedUpdate() override;
	virtual void Update() override;
};