#include "PreCompiledHeader.h"
#include "FadeOutObject.h"

#define FADE_OUT_SECOND 1.5f

FadeOutObject::FadeOutObject() :
	mFadeTime(0.f),
	mSceneName(""),
	mIsWantLoadScene(false),
	mIsTitle(false)

{
	SetTag("UI");

	D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

	mTransform->SetPosition(Vector2D(size.width / 2, size.height / 2));

	AddSpriteRenderer()->SetSortOrder(1);

	GetSpriteRenderer()->SetOpacity(0.f);

	GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("FADE_INOUT"));

	mIsTitle = true;
}

FadeOutObject::FadeOutObject(std::string sceneName)
	: mFadeTime(0.0f)
{
	SetTag("UI");

	D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

	mTransform->SetPosition(Vector2D(size.width / 2, size.height / 2));

	AddSpriteRenderer()->SetSortOrder(1);

	GetSpriteRenderer()->SetOpacity(0.f);

	GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("FADE_INOUT"));

	mSceneName = sceneName;

	mIsWantLoadScene = true;

	mIsTitle = false;
}

FadeOutObject::~FadeOutObject()
{
}

void FadeOutObject::Update()
{
	GameObject::Update();

	mFadeTime += Timer::GetInstance().GetDeltaTime() / 1000.f;

	mVolume = SoundManager::GetInstance()->GetCurrentPlayBGMVolume() - Timer::GetInstance().GetDeltaTime() / 1000.0f;

	if (mVolume < 0)
		mVolume = 0.0f;

	SoundManager::GetInstance()->Volume(SoundManager::GetInstance()->GetCurrentPlayBGM(), mVolume);

	// 2.5초 페이드
	if (GetSpriteRenderer()->GetOpacity() <= 1.f)
		GetSpriteRenderer()->SetOpacity(0.f + mFadeTime / FADE_OUT_SECOND);
	else
	{
		if (mIsTitle)
		{
			Game::GetInstance().InitPlayer();

			Game::GetInstance().ReserveLoadScene("Intro");
		}
		else if (mIsWantLoadScene)
			Game::GetInstance().ReserveLoadScene(mSceneName);

		int bgmNumber = SoundManager::GetInstance()->GetCurrentPlayBGM();

		if (bgmNumber != -1)
			SoundManager::GetInstance()->Stop(bgmNumber);
	}
}