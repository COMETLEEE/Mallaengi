#pragma once

class GameObject;
class Transform;
/// <summary>
/// 2022.02.07. MG
/// </summary>
class Animator
{
public:
	Animator(GameObject* object);
	~Animator();

private:
	GameObject* mGameObject;

	Transform* mTransform;

	AnimationClip* mAnimationClip;

	int mCurrentIndex;				// 출력할 스프라이트의 인덱스
	float mPlayingTime;				// 현재 출력 중인 스프라이트가 어느 정도의 시간동안 출력되었는가.
	int mTotalFrameOfClip;			// 현재 재생 중인 애니메이션 클립의 Sprite 장 수

	bool mIsLoop;
	void (*mFunc)(GameObject* object);

public:
	GameObject* GetGameObject() { return mGameObject; }

	Transform* GetTransform() { return mTransform; }

	void SetNotLoop(void (*func)(GameObject* object));

	// 애니메이션을 위한 스프라이트 벡터 데이터 대입. 총 스프라이트 수 대입
	void SetAnimationClip(AnimationClip* animationClip) 
	{
		mAnimationClip = animationClip;

		mTotalFrameOfClip = mAnimationClip->GetTotalFrameOfAnimation();

		// CurrentIndex 초기화는 필수 ..!
		mCurrentIndex = 0;
	}

	void Play();
	void Release();
};