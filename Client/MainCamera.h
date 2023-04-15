#pragma once

class Player;

/**
 * 스테이지에서 게임을 플레이할 때 사용될 카메라
 *
 * 플레이어의 위치를 기준으로 카메라를 Control
 *
 * 2022. 02. 12. Comet
 */
class MainCamera : public GameObject
{
public:
	MainCamera(float mapWidth, float mapHeight);
	virtual ~MainCamera();

	Player* mPlayer;

	float mMapWidth;
	float mMapHeight;

public:
	virtual void LateUpdate() override;
	float GetXMovablePercent();
	float GetYMovablePercent();
};