#include "PreCompiledHeader.h"
#include "StageThree2.h"

#include "FadeInObject.h"
#include "IntroBackGround.h"
#include "Player.h"
#include "SubCamera.h"
#include "DecoObject.h"

StageThree2::StageThree2():
Scene("StageThreeTwo")
{
}

StageThree2::~StageThree2()
{
}

void StageThree2::BuildScene()
{
	Scene::BuildScene();

	// 사운드
	while (SoundManager::GetInstance()->Playing(500004) != true)
		SoundManager::GetInstance()->Play(500004);

	// Fade-In
	AddGameObject(new FadeInObject());

	AddGameObject(mGamePlayer);

	// 이 씬은 서브 카메라가 필요합니다. (위치 고정, 스크롤 X)
	AddGameObject(new SubCamera());

	// 배경 화면
	GameObject* background = new IntroBackGround();

	background->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("STAGE_3_BACKGROUND"));

	background->GetSpriteRenderer()->SetSortOrder(10);

	background->GetTransform()->SetPosition(Vector2D(1400.f, 500.f));

	AddGameObject(background);

	LoadSceneDataStageThree(_T("Resources\\Json\\Stage 3-2.json"));

	// 플레이 스테이지들은 첫 번째로 로드될 때의 디폴트 정보를 저장한다.
	if (mIsFirstLoad)
	{
		mGamePlayer->GetTransform()->SetPosition(Vector2D(700.f, 100.f));				// 스테이지 3은 기획자분들이 정하는 위치로 간다.

		Game::GetInstance().SetSavePosition(mGamePlayer->GetTransform()->GetPosition());

		// 스테이지 3에서는 몸무게 고정 / 2단계 fix
		float fixedBodyWeight = 105.f;

		if (fixedBodyWeight < 100.f)
			mGamePlayer->SetPlayerStep(PlayerStep::One);
		else if ((fixedBodyWeight >= 100.f) && (fixedBodyWeight < 120.f))
			mGamePlayer->SetPlayerStep(PlayerStep::Two);
		else if ((fixedBodyWeight >= 120) && (fixedBodyWeight < 140.f))
			mGamePlayer->SetPlayerStep(PlayerStep::Three);

		mGamePlayer->SetPlayerState(PlayerState::Idle);

		std::vector<std::vector<AnimationClip*>> clips = mGamePlayer->GetAnimationClipsOfPlayer();

		mGamePlayer->GetAnimator()->SetAnimationClip(clips[static_cast<int>(mGamePlayer->GetCurrentStep())][static_cast<int>(mGamePlayer->GetCurrentState())]);

		// 첫 번째 로드가 아니라면 저장된 정보로 플레이어를 세팅한다. (Save Point 포함)
		mGamePlayer->GetTransform()->SetPosition(Game::GetInstance().GetSavePosition());
		mGamePlayer->SetBodyWeight(fixedBodyWeight);
		mGamePlayer->SetHp(1);

		mIsFirstLoad = false;
	}
	else
	{
		// 스테이지 3에서는 몸무게 고정 / 2단계 fix
		float fixedBodyWeight = 105.f;

		if (fixedBodyWeight < 100.f)
			mGamePlayer->SetPlayerStep(PlayerStep::One);
		else if ((fixedBodyWeight >= 100.f) && (fixedBodyWeight < 120.f))
			mGamePlayer->SetPlayerStep(PlayerStep::Two);
		else if ((fixedBodyWeight >= 120) && (fixedBodyWeight < 140.f))
			mGamePlayer->SetPlayerStep(PlayerStep::Three);

		mGamePlayer->SetPlayerState(PlayerState::Idle);

		std::vector<std::vector<AnimationClip*>> clips = mGamePlayer->GetAnimationClipsOfPlayer();

		mGamePlayer->GetAnimator()->SetAnimationClip(clips[static_cast<int>(mGamePlayer->GetCurrentStep())][static_cast<int>(mGamePlayer->GetCurrentState())]);

		// 첫 번째 로드가 아니라면 저장된 정보로 플레이어를 세팅한다. (Save Point 포함)
		mGamePlayer->GetTransform()->SetPosition(Game::GetInstance().GetSavePosition());
		mGamePlayer->SetBodyWeight(fixedBodyWeight);
		mGamePlayer->SetHp(1);
	}

	// 캐릭터 얼굴
	GameObject* faceUI = new DecoObject();

	faceUI->GetTransform()->SetPosition(Vector2D(50, 50));

	faceUI->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("LIFE_FACE"));

	faceUI->GetSpriteRenderer()->SetSortOrder(1);		// 넌 뒤로 가라 ..

	faceUI->SetTag("UI");

	AddGameObject(faceUI);

	if (mGamePlayer->GetPlayerLife() < 0)
	{
		mGamePlayer->SetHp(100);
	}

	// 라이프를 받아온다. 이 숫자에 맞는 오브젝트들을 설치해서 보여줘야함 ..!
	std::string life = std::to_string(mGamePlayer->GetPlayerLife());

	// 양수
	if (life[0] != '-')
	{
		for (int i = 0; i < life.length(); i++)
		{
			GameObject* number = new DecoObject();

			if (life[i] == '0')
				number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_ZERO"));
			else if (life[i] == '1')
				number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_ONE"));
			else if (life[i] == '2')
				number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_TWO"));
			else if (life[i] == '3')
				number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_THREE"));
			else if (life[i] == '4')
				number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_FOUR"));
			else if (life[i] == '5')
				number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_FIVE"));
			else if (life[i] == '6')
				number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_SIX"));
			else if (life[i] == '7')
				number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_SEVEN"));
			else if (life[i] == '8')
				number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_EIGHT"));
			else if (life[i] == '9')
				number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_NINE"));

			number->GetTransform()->SetPosition(Vector2D(i * 20.f + 115.0f, 55.f));

			number->GetSpriteRenderer()->SetSortOrder(1);

			number->SetTag("UI");

			AddGameObject(number);
		}
	}
}
