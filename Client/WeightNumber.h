#pragma once

/// <summary>
/// 체력 증가 / 감소 이펙트 출력용 객체
/// +1, +3, +5, +10 / -1, -3, -5, -10
/// 8가지만 사용 가능
/// 
/// 2022. 02. 25 JK
/// </summary>
class WeightNumber : public GameObject
{
	AnimationClip* mAnimClip;

	std::vector<Sprite*> mSprites;
public:
	WeightNumber(Vector2D pos, int number);
	virtual ~WeightNumber();

	virtual void Release() override;
};