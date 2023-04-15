#pragma once

/**
 * 먹으면 몸무게의 변화 Food. 아이템 박스를 때리면 생성된다.
 *
 * 2022. 02. 17. Comet
 */
class Food : public GameObject
{
public:
	Food(float weight, int ID, Vector2D pos, bool isInBox);
	virtual ~Food();

	// 이걸 먹을 시 늘어나거나, 감소되는 몸무게
	float mWeight;

	// 이 친구가 사용하는 이미지 아이디
	int mID;

	// 이 친구가 사용하는 이미지 시트에서의 좌상단
	Vector2D mPos;

	// 타일 크기의 절반만큼 이동하면 됨
	float mMoveDist;

	// 박스에서 젠이 된 녀석인지, 아닌지.
	bool mIsInBox;

	// 위, 아래로 움직일 때 사용하는 변수
	int mDirrection;

	// 위, 아래로 움직일 때 얼마나 움직였는가.
	float mTotalMoveDist;

	// 먹혔는가.
	bool mIsEaten;

	static float mMallaengBar;

public:
	virtual void Update() override;
};