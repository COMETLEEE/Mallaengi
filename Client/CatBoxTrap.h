#pragma once

/// <summary>
/// 아이템 박스 내부에 reserve 되어 있다가, 이벤트 터지면 나와서
///
///	애니메이션 틀고 플레이어 ㅃㅇ 2022. 02. 23. Comet
/// </summary>
class CatBoxTrap : public GameObject
{
public:
	CatBoxTrap();
	virtual ~CatBoxTrap();

private:
	void LoadAnimation();

	float mTimer;

public:
	virtual void Update() override;
};