#pragma once


class FreeEnemy;
/**
 * \brief : 덤벨다운 함정. 플레이어가 x좌표 기준 근처에 오면 덤벨을 떨어뜨린다.
 */
class DumbellDown : public GameObject
{
public:
	DumbellDown(std::string type);

	virtual ~DumbellDown();

	bool mTrigger;

	Player* mGamePlayer;

	// 이 녀석을 던져버린다 ~
	FreeEnemy* mReserve;

public:
	virtual void Update();
	virtual void Release();
};