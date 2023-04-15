#pragma once


#define FALLING_SPEED 6 * TILE_HEIGHT

// 스테이지 시작 후 4초 뒤부터 1.5초 간격으로 떨어진다.

/// <summary>
/// 3-5 대망의 Falling 
/// 
/// 2022. 02. 24. Comet
/// </summary>
class FiveFalling : public GameObject
{
public:
	FiveFalling(D2D1_SIZE_F collisionSize, float dropTime);

	virtual ~FiveFalling();

	float mDropTime;

public:
	virtual void Update() override;
};