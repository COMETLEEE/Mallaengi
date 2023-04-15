#pragma once

/// <summary>
/// 2022.02.07. MG.
/// 
/// 애니메이션 클립
/// </summary>
class AnimationClip
{
public:
	AnimationClip(std::vector<Sprite*>& animation);
	~AnimationClip();

private:
	std::vector<Sprite*> mAnimation;		// 스프라이트들의 정보가 담길 변수

public:
	Sprite* GetSpriteOfIndex(int index) 
	{
		if (mAnimation.size() <= index)
			return nullptr;

		return mAnimation[index]; 
	}

	int GetTotalFrameOfAnimation()
	{
		return mAnimation.size();
	}
};