#pragma once

/**
 * \brief : 스테이지 플레이 중 시계를 나타내는 녀석
 */
class Watch : public GameObject
{
public:
	Watch();
	virtual ~Watch();

private:
	Player* mGamePlayer;

	std::vector<GameObject*> mNumbers;

public:
	virtual void LateUpdate() override;
};