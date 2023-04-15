#pragma once

class Platform;

/// <summary>
/// 밟으면 플레이어와 함께 나락을 가는 함정
/// 
/// 내부의 블럭들이 플레이어와 충돌했다면 트리거를 키고 y좌표가 감소하면서 추락한다.
/// 
/// 이 때, 플레이어도 같이 붙은 채로 이동해야하니 플레이어의 y좌표도 함께 감소시켜준다.
/// 
/// 2022. 02. 09. Comet
/// </summary>
class FallingTrap : public GameObject
{
public:
	FallingTrap(Vector2D startPos);
	virtual ~FallingTrap();

private:
	bool mIsTriggered;					// 트리거 되었는지 변수
	GameObject* mPlayer;				// 트리거되면 여기에 플레이어를 저장합니다.

	std::vector<Platform*> mPlatforms;	// 밟긴 해야하니까 플랫폼들로 체크한다. 이 녀석들이 씬에 추가되어야 함.

	float mFallingSpeed;				// 떨어지는 속도를 컨트롤한다. 중력을 받는 것처럼 연출합니다.

public:
	
	// 추락형 함정은 게임 오브젝트이지만 그 안에 있는 게임 오브젝트들이 메인입니다.
	std::vector<Platform*>& GetPlatforms() { return mPlatforms; }

	virtual void FixedUpdate() override;
	virtual void Update() override;
}; 