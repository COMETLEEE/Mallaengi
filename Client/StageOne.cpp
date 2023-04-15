#include "PreCompiledHeader.h"
#include "StageOne.h"

#include "Player.h"

// Blocks
#include "BlockBase.h"
#include "BreakableBlock.h"
#include "TransBox.h"

// Platforms
#include "Platform.h"

// Traps
#include "FallingBlock.h"

// Structure
#include "StageOneBackGround.h"
#include "BlockPlatform.h"
#include "BodyScale.h"
#include "CheckPoint.h"
#include "DecoObject.h"
#include "FadeInObject.h"
#include "Food.h"
#include "JsonManager.h"
#include "LRMovingPlatform.h"
#include "MainCamera.h"
#include "TriggerTrap.h"
#include "UDMovingPlatform.h"

#include "ItemBox.h"
#include "RisingTrap.h"

#include "CollisionGrid.h"

// Enemy
#include "FallingPlatform.h"
#include "FreeEnemy.h"
#include "FallingTriggerTrap.h"
#include "Watch.h"

StageOne::StageOne() :
	Scene("StageOne")
{

}

StageOne::~StageOne()
{

}

void StageOne::BuildScene()
{
	Scene::BuildScene();

	// 이 함수를 사전에 호출하면, Build할 때 Fade-In을 실시한다.
	GameObject* fadeIn = new FadeInObject();

	AddGameObject(fadeIn);

	// UI 배치
	GameObject* bodyScale = new BodyScale();

	// 체중계
	AddGameObject(bodyScale);

	// 시계
	AddGameObject(new Watch());

	// 플레이어 배치
	AddGameObject(mGamePlayer);

	// 메인 카메라
	MainCamera* mainCamera = new MainCamera(TILE_WIDTH * 100 * 3, TILE_HEIGHT * 30);

	AddGameObject(mainCamera);

	// 배경 화면
	GameObject* background = new StageOneBackGround();

	SpriteRenderer* sprite = dynamic_cast<SpriteRenderer*>(background->GetRenderer());

	sprite->SetSprite(Game::GetInstance().GetResource()->GetSprite("STAGE_1_BACKGROUND"));

	sprite->SetSortOrder(10);

	AddGameObject(background);

	LoadSceneData(_T("Resources\\Json\\Stage 1-%d.json"), 3);

	SoundManager::GetInstance()->Play(500002);

	// 플레이 스테이지들은 첫 번째로 로드될 때의 디폴트 정보를 저장한다.
	if (mIsFirstLoad)
	{
		// 스테이지 별로 스타트하는 위치 (이 정보들을 게임에 저장해서 Stage Restart 기능 구현 ?)
		mGamePlayer->GetTransform()->SetPosition(Vector2D(100.f, 1760.f));

		//mGamePlayer->GetTransform()->SetPosition(Vector2D(23000.f, 160.f));

		Game::GetInstance().SetSaveBodyWeight(mGamePlayer->GetBodyWeight());

		Game::GetInstance().SetSavePosition(mGamePlayer->GetTransform()->GetPosition());

		mIsFirstLoad = false;
	}
	else
		// 낚여서 죽은 후 또는 Restart를 눌렀다 j..다시 태어난다는 소리죠 ?
	{
		// IDLE + STEP + 애니메이션 완전히 바꿔놓고 가면 되긴 함 ..
		float saveBodyWeight = Game::GetInstance().GetSaveBodyWeight();

		if (saveBodyWeight < 100.f)
			mGamePlayer->SetPlayerStep(PlayerStep::One);
		else if ((saveBodyWeight >= 100.f) && (saveBodyWeight < 120.f))
			mGamePlayer->SetPlayerStep(PlayerStep::Two);
		else if ((saveBodyWeight >= 120) && (saveBodyWeight < 140.f))
			mGamePlayer->SetPlayerStep(PlayerStep::Three);

		mGamePlayer->SetPlayerState(PlayerState::Idle);
		mGamePlayer->mRunEffect = nullptr;
		mGamePlayer->mLandingEffect = nullptr;

		std::vector<std::vector<AnimationClip*>> clips = mGamePlayer->GetAnimationClipsOfPlayer();

		mGamePlayer->GetAnimator()->SetAnimationClip(clips[static_cast<int>(mGamePlayer->GetCurrentStep())][static_cast<int>(mGamePlayer->GetCurrentState())]);

		// 첫 번째 로드가 아니라면 저장된 정보로 플레이어를 세팅한다. (Save Point 포함)
		mGamePlayer->GetTransform()->SetPosition(Game::GetInstance().GetSavePosition());
		mGamePlayer->SetBodyWeight(saveBodyWeight);
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