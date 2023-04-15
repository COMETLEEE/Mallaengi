#pragma once

class Player;

/**
 * \brief 스테이지 플레이 중 최상단에서 플레이어의 몸무게를 표시하는 UI
 *
 * 2022. 02. 19. Comet
 */
class BodyScale : public GameObject
{
public:
	BodyScale();
	virtual ~BodyScale();

private:
	Player* mGamePlayer;

	std::vector<GameObject*> mNumbers;

public:
	virtual void LateUpdate() override;
};