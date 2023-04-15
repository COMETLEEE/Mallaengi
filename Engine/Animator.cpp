#include "pch.h"
#include "Timer.h"
#include "Animator.h"

Animator::Animator(GameObject* object)
	: mGameObject(object),
	mTransform(object->GetTransform()),
	mPlayingTime(0),
	mTotalFrameOfClip(0),
	mCurrentIndex(0),
	mIsLoop(true),
	mAnimationClip(nullptr),
	mFunc(nullptr)
{
	
}

Animator::~Animator()
{

}

void Animator::SetNotLoop(void(*func)(GameObject* object))
{
	mFunc = func;
	mIsLoop = false;
}

void Animator::Play()
{
	// 현재 흐르는 델타 타임 받아옴 -> 현재 출력 중인 스프라이트의 출력을 시작하고 부터 현재까지 누적 출력 시간
	mPlayingTime += Timer::GetInstance().GetDeltaTime() / 1000;

	// 현재 출력 중인 스프라이트의 딜레이타임 (얼마나 출력할 것인지 설정함) <= 현재 출력중인 개별 스프라이트의 시간
	if (mAnimationClip->GetSpriteOfIndex(mCurrentIndex)->mDelayTime <= mPlayingTime)
	{
		// 현재 인덱스를 1 증가시켜서 총 인덱스 수에 나머지연산을 한다. -> 다음 스프라이트 인덱스 나옴.
		mCurrentIndex++;

		if (mIsLoop == true)
		{
			mCurrentIndex %= mTotalFrameOfClip;
		}
		else
		{
			if (mCurrentIndex >= mTotalFrameOfClip)
			{
				mFunc(mGameObject);
			}
		}

		// 현재 출력시간 0으로 만들기
		mPlayingTime = 0.f;
	}

	// 렌더를 위한 변수
	Renderer* renderer = mGameObject->GetRenderer();

	// setSprite하기 위한 변수
	SpriteRenderer* spriteRenderer = dynamic_cast<SpriteRenderer*>(renderer);

	if (spriteRenderer != nullptr)
	{
		// 다음 스프라이트 인덱스를 출력하도록 CurrentIndex 를 설정 해준다.
		spriteRenderer->SetSprite(mAnimationClip->GetSpriteOfIndex(mCurrentIndex));
	}
}

void Animator::Release()
{
	if (mAnimationClip != nullptr)
	{
		Renderer* renderer = mGameObject->GetRenderer();

		SpriteRenderer* spriteRenderer = dynamic_cast<SpriteRenderer*>(renderer);

		if (spriteRenderer != nullptr)
			spriteRenderer->SetSprite(nullptr);

		delete mAnimationClip;
		mAnimationClip = nullptr;
	}
}