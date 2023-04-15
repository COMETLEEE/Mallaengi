#include "pch.h"
#include "AnimationClip.h"

AnimationClip::AnimationClip(std::vector<Sprite*>& animation)
{
	mAnimation = animation;
}

AnimationClip::~AnimationClip()
{
	for (int i = 0; i < mAnimation.size(); i++)
	{
		if (mAnimation[i] != nullptr)
		{
			delete mAnimation[i];
		}
	}
}
