#include "PreCompiledHeader.h"
#include "Game.h"

// Scenes
//#include "CometScene.h"
#include "DieScene.h"
#include "Intro.h"
#include "StageOne.h"
#include "LoadingScene.h"

// 오프닝
#include "Stage1OpeningScene.h"
#include "Stage2OpeningScene.h"
#include "Stage3OpeningScene.h"

// 엔딩
#include "EndingSceneOne.h"
#include "EndingSceneTwo.h"

#include "Player.h"
#include "StageTwo.h"
#include "StageThree1.h"

#include "ProgressBar.h"
#include "Exit.h"
#include "Title.h"
#include "Back.h"
#include "Restart.h"
#include "StageThree2.h"
#include "StageThree3.h"
#include "StageThree4.h"
#include "StageThree5.h"
#include "UIDecoObject.h"

#include "FadeOutObject.h"

Game::Game() :
	mScenes(std::map<std::string, Scene*>()),
	mSaveBodyWeight(0.f),
	mSavePosition(Vector2D(0.f, 0.f)),
	mCurrentScene(nullptr),
	mIsReservedLoadScene(false),
	mIsDebugMode(false),
	mIsEndGame(false),
	mResource(nullptr),
	mLastBodyWeight(0.f)
{

}

Game::~Game()
{
	mCurrentScene->ClearScene();

	for (auto iter : mScenes)
	{
		if (iter.second != nullptr)
			delete iter.second;
	}

	for (auto iter : mMenuList)
	{
		if (iter != nullptr)
			delete iter;
	}

	if (mGamePlayer != nullptr)
		delete mGamePlayer;

	if (mResource != nullptr)
		delete mResource;
}

void Game::Initialize(HWND hWnd)
{
	// Engine Initialize
	Engine::GetInstance().Initialize(hWnd);

	// Resource Initialize
	mResource = new Resource();
	mResource->Initialize();

	// 플레이어를 생성해줍니다. 이것은 게임 내에서 전역적으로 사용할 계획입니다.
	mGamePlayer = new Player();

	// 준비한 Scene Class들을 생성하고 저장해준다.

	// Intro
	RegisterScene(new Intro());

	// Opening
	RegisterScene(new Stage1OpeningScene());
	RegisterScene(new Stage2OpeningScene());
	RegisterScene(new Stage3OpeningScene());

	// Stages
	RegisterScene(new StageOne());
	RegisterScene(new StageTwo());
	RegisterScene(new StageThree1());
	RegisterScene(new StageThree2());
	RegisterScene(new StageThree3());
	RegisterScene(new StageThree4());
	RegisterScene(new StageThree5());

	// DieScene // 죽었을 때 불러와야하는 씬을 보내주는 것
	RegisterScene(new DieScene("StageOne"));
	RegisterScene(new DieScene("StageTwo"));
	RegisterScene(new DieScene("StageThreeOne"));
	RegisterScene(new DieScene("StageThreeTwo"));
	RegisterScene(new DieScene("StageThreeThree"));
	RegisterScene(new DieScene("StageThreeFour"));
	RegisterScene(new DieScene("StageThreeFive"));

	// Loading Scene (Narative ..?)
	RegisterScene(new LoadingScene("Intro"));
	RegisterScene(new LoadingScene("StageOneOpening"));
	RegisterScene(new LoadingScene("StageTwoOpening"));
	RegisterScene(new LoadingScene("StageThreeOneOpening"));
	RegisterScene(new LoadingScene("OneEnding"));
	RegisterScene(new LoadingScene("TwoEnding"));
	RegisterScene(new LoadingScene("StageOne"));	// Name = IntroLoadingScene
	RegisterScene(new LoadingScene("StageTwo"));	// Name = IntroLoadingScene
	RegisterScene(new LoadingScene("StageThreeOne"));	// Name = IntroLoadingScene

	// Ending Scene
	RegisterScene(new EndingSceneOne());
	RegisterScene(new EndingSceneTwo());

	// 그 이후는 로딩하지 말자.

	//// soundManager Initialize
	SoundManager::GetInstance()->Initialize();
	SoundManager::GetInstance()->LoadJsonAddSound();

	ReserveLoadScene("Intro");

	// Intro Scene 로드 후 준비
	LoadScene();

	// 옵션 초기화
	InitOption();
}

bool Game::GameLoop()
{
	SoundManager::GetInstance()->Update();

	

	std::string name = mCurrentScene->GetSceneName();

	// 스테이지 플레이 중 ESC 버튼을 누르면 Option창 On / Off
	if ((Input::GetInstance().GetKeyState(VK_ESCAPE) == KEYSTATE::DOWN))
	{
		// 문자열의 특정 부분을 잘라내여 씬의 역할을 구분한다.
		// 씬에 타입 변수를 넣었으면 더 좋았을거 같은데 나중에..
		string str = name;

		if (str.length() >= 7)
			str = str.substr(str.length() - 7);

		if (str == "Opening")
		{
			str = name;

			str = str.substr(0, str.length() - 7) + "LoadingScene";

			FadeOutObject* fadeOut = new FadeOutObject(str);

			Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
		}
		else
		{
			str = name;

			if (str.length() >= 6)
				str = str.substr(str.length() - 6);

			if (str == "Ending")
			{
				FadeOutObject* fadeOut = new FadeOutObject("IntroLoadingScene");

				Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
			}
			else
			{
				str = name;

				str = str.substr(0, 5);

				if ((str == "Intro") || (str == "Stage"))
					OptionToggle();
			}
		}
	}

	// DieScene일 때 키 입력을 받을 수 있게함
	if (Input::GetInstance().GetKeyState(VK_RETURN) == KEYSTATE::DOWN)
	{
		string str = name;

		if (str.length() >= 8)
			str = str.substr(str.length() - 8);

		if (str == "DieScene")
		{
			str = name;

			str = str.substr(0, str.length() - 8);

			FadeOutObject* fadeOut = new FadeOutObject(str);

			Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
		}
	}

	if (mIsOptionClicked)
		// 옵션이 클릭되었으면 OffOption해야지.
	{
		OffOption();

		//sound 
		/*SoundManager::GetInstance()->Resume();*/

		mIsOptionOn = false;

		mIsOptionClicked = false;
	}

#ifdef _DEBUG || DEBUG
	if (Input::GetInstance().GetKeyState(VK_F5) == KEYSTATE::DOWN)
	{
		mIsDebugMode = !mIsDebugMode;
	}
	else if (Input::GetInstance().GetKeyState(VK_F6) == KEYSTATE::DOWN)
	{
		ReserveLoadScene("StageOne");

		int bgmNumber = SoundManager::GetInstance()->GetCurrentPlayBGM();

		if (bgmNumber != -1)
			SoundManager::GetInstance()->Stop(bgmNumber);
	}
	else if (Input::GetInstance().GetKeyState(VK_F7) == KEYSTATE::DOWN)
	{
		ReserveLoadScene("StageTwo");

		int bgmNumber = SoundManager::GetInstance()->GetCurrentPlayBGM();

		if (bgmNumber != -1)
			SoundManager::GetInstance()->Stop(bgmNumber);
	}
	else if (Input::GetInstance().GetKeyState(VK_F8) == KEYSTATE::DOWN)
	{
		std::string scenename = Game::GetInstance().GetCurrentScene()->GetSceneName();

		if (scenename == "StageThreeOne")
			ReserveLoadScene("StageThreeTwo");
		else if (scenename == "StageThreeTwo")
			ReserveLoadScene("StageThreeThree");
		else if (scenename == "StageThreeThree")
			ReserveLoadScene("StageThreeFour");
		else if (scenename == "StageThreeFour")
			ReserveLoadScene("StageThreeFive");
		else
			ReserveLoadScene("StageThreeOne");

		int bgmNumber = SoundManager::GetInstance()->GetCurrentPlayBGM();

		if (bgmNumber != -1)
			SoundManager::GetInstance()->Stop(bgmNumber);
	}
	else if (Input::GetInstance().GetKeyState(VK_F9) == KEYSTATE::DOWN)
	{
		std::string scenename = Game::GetInstance().GetCurrentScene()->GetSceneName();

		FadeOutObject* fadeOut;

		if (scenename == "StageOne")
		{
			fadeOut = new FadeOutObject("StageTwoOpeningLoadingScene");

			Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
		}
		else if (scenename == "StageTwo")
		{
			fadeOut = new FadeOutObject("StageThreeOneOpeningLoadingScene");

			Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
		}
		else if (scenename == "StageThreeOne")
		{
			if (mGamePlayer->GetBodyWeight() >= 100.0f)
			{
				fadeOut = new FadeOutObject("OneEndingLoadingScene");
			}
			else
			{
				fadeOut = new FadeOutObject("TwoEndingLoadingScene");
			}

			Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
		}
		else
		{
			fadeOut = new FadeOutObject("StageOneOpeningLoadingScene");

			Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
		}

		int bgmNumber = SoundManager::GetInstance()->GetCurrentPlayBGM();

		if (bgmNumber != -1)
			SoundManager::GetInstance()->Stop(bgmNumber);
	}
#endif

	mCurrentScene->SceneLoop();

	// 씬 변경이 예약되어 있다면 모든 SceneLoop를 수행한 후 다음 씬으로 전환합니다.
	if (mIsReservedLoadScene)
		LoadScene();

	// 대충 뭔가 플레이어의 목숨이 다 끝났거나,
	// 엔딩씬을 다 보고 랭킹 등록이 완료되었거나,
	// 게임 종료를 눌렀을 때 끄면 되겠습니다.

	return mIsEndGame;
}

void Game::EndGame()
{
	mIsEndGame = true;
	/*SoundManager::DestroyInstance();*/
}

// 하지만 우리 게임은 게임 Initialize에서 모든 씬을 준비하기 때문에 필요가 없는 기능이다.
void Game::RegisterScene(Scene* scene)
{
	// 게임에서 관리하는 Scene Collection에 등록합니다.
	mScenes.insert({ scene->GetSceneName(), scene });
}

// 씬 이름을 받아서 로드를 예약합니다.
void Game::ReserveLoadScene(std::string sceneName)
{
	// 컴파일 중에 에러 메세지를 내뱉을 수 있도록 assert 걸어놔요 ..
	assert(mScenes.find(sceneName) != mScenes.end());

	mIsReservedLoadScene = true;

	mNextScene = mScenes[sceneName];
}

void Game::LoadScene()
{
	if (mCurrentScene != nullptr)
		mCurrentScene->ClearScene();

	// 만약, 로드 중인데 옵션이 또 켜져있다면 꺼줘 ..!
	if (mIsOptionOn)
		mIsOptionOn = !mIsOptionOn;

	mCurrentScene = mNextScene;

	// 플레이어 세팅해줍니다.
	mCurrentScene->SetPlayer(mGamePlayer);

	mGamePlayer->GetSpriteRenderer()->SetOpacity(1.f);

	mCurrentScene->BuildScene();

	mIsReservedLoadScene = false;
}

void Game::OptionToggle()
{
	mIsOptionOn = !mIsOptionOn;
	// True이면, 생성해서 넣어주자.

	if (mIsOptionOn)
		OnOption();
	else
		OffOption();
}

void Game::InitPlayer()
{
	// 그 전에 있던 플레이어 정보를 삭제해줘야하는데 .. 쓰읍 이거 어케하누.
	// mCurrentScene->ReserveDestroy(mGamePlayer);

	if (mGamePlayer != nullptr)
	{
		mGamePlayer->InitPlayer();
	}
}

void Game::InitScenes()
{
	for (auto scene : mScenes)
		scene.second->mIsFirstLoad = true;
}

void Game::InitOption()
{
	D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

	// 메뉴판 바탕
	UIDecoObject* menu = new UIDecoObject();

	menu->GetSpriteRenderer()->SetSprite(mResource->GetSprite("OPTION_MENU"));
	menu->GetTransform()->SetPosition(Vector2D(size.width / 2, size.height / 2));
	menu->GetSpriteRenderer()->SetSortOrder(2);

	// BGM Progress Bar
	//ProgressBar* bgmBack = new ProgressBar(mResource->GetSprite("OPTION_BACK_PROGRESS_BAR"), false);
	//bgmBack->GetTransform()->SetPosition(bgmBack->GetTransform()->GetPosition() + Vector2D(size.width / 2, size.height / 2 - 130));
	//bgmBack->GetSpriteRenderer()->SetSortOrder(3);

	// BGM 볼륨 조절하는 함수를 연결해준다.
	ProgressBar* bgmFront = new ProgressBar(mResource->GetSprite("OPTION_FRONT_PROGRESS_BAR"), true, [](float percent)
		{
			SoundManager::GetInstance()->SetBGMVolume(percent);
		},
		SoundManager::GetInstance()->GetBGMVolume());
	bgmFront->SetPercent(SoundManager::GetInstance()->GetBGMVolume());

	bgmFront->GetTransform()->SetPosition(bgmFront->GetTransform()->GetPosition() + Vector2D(size.width / 2, size.height / 2 - 130));
	bgmFront->GetSpriteRenderer()->SetSortOrder(2);

	ProgressBar* bgmBar = new ProgressBar(mResource->GetSprite("OPTION_PROGRESS_BAR"), false);
	bgmBar->GetTransform()->SetPosition(bgmBar->GetTransform()->GetPosition() + Vector2D(size.width / 2, size.height / 2 - 130));
	bgmBar->GetSpriteRenderer()->SetSortOrder(1);

	UIDecoObject* bgmText = new UIDecoObject();

	bgmText->GetSpriteRenderer()->SetSprite(mResource->GetSprite("OPTION_BGM_TEXT"));
	bgmText->GetTransform()->SetPosition(bgmBar->GetTransform()->GetPosition() - Vector2D(60.0f, -30.0f));
	bgmText->GetSpriteRenderer()->SetSortOrder(1);

	// SFX Progress Bar
	//ProgressBar* sfxBack = new ProgressBar(mResource->GetSprite("OPTION_BACK_PROGRESS_BAR"), false);
	//sfxBack->GetTransform()->SetPosition(sfxBack->GetTransform()->GetPosition() + Vector2D(size.width / 2, size.height / 2 - 65));
	//sfxBack->GetSpriteRenderer()->SetSortOrder(3);

	// SFX 볼륨 조절하는 함수를 연결해준다.
	ProgressBar* sfxFront = new ProgressBar(mResource->GetSprite("OPTION_FRONT_PROGRESS_BAR"), true, [](float percent)
		{
			SoundManager::GetInstance()->SetSFXVolume(percent);
		},
		SoundManager::GetInstance()->GetSFXVolume());
	sfxFront->SetPercent(SoundManager::GetInstance()->GetSFXVolume());

	sfxFront->GetTransform()->SetPosition(sfxFront->GetTransform()->GetPosition() + Vector2D(size.width / 2, size.height / 2 - 65));
	sfxFront->GetSpriteRenderer()->SetSortOrder(2);

	ProgressBar* sfxBar = new ProgressBar(mResource->GetSprite("OPTION_PROGRESS_BAR"), false);
	sfxBar->GetTransform()->SetPosition(sfxBar->GetTransform()->GetPosition() + Vector2D(size.width / 2, size.height / 2 - 65));
	sfxBar->GetSpriteRenderer()->SetSortOrder(1);

	UIDecoObject* sfxText = new UIDecoObject();

	sfxText->GetSpriteRenderer()->SetSprite(mResource->GetSprite("OPTION_SFX_TEXT"));
	sfxText->GetTransform()->SetPosition(sfxBar->GetTransform()->GetPosition() - Vector2D(60.0f, -30.0f));
	sfxText->GetSpriteRenderer()->SetSortOrder(1);

	// 재시작
	Restart* res = new Restart();
	res->GetTransform()->SetPosition(Vector2D(size.width / 2, size.height / 2 + 50.f));
	res->GetSpriteRenderer()->SetSortOrder(1);

	// 뒤로가기
	Back* back = new Back();
	back->GetTransform()->SetPosition(Vector2D(size.width / 2, size.height / 2 + 125.0f));
	back->GetSpriteRenderer()->SetSortOrder(1);

	// 타이틀로
	Title* title = new Title();
	title->GetTransform()->SetPosition(Vector2D(size.width / 2, size.height / 2 + 200.f));
	title->GetSpriteRenderer()->SetSortOrder(1);

	// 게임 종료
	Exit* exit = new Exit();
	exit->GetTransform()->SetPosition(Vector2D(size.width / 2, size.height / 2 + 275.f));
	exit->GetSpriteRenderer()->SetSortOrder(1);

	// 메뉴 객체 리스트 보관
	mMenuList.push_back(menu);
	mMenuList.push_back(res);
	mMenuList.push_back(back);
	mMenuList.push_back(title);
	//mMenuList.push_back(bgmBack);
	mMenuList.push_back(bgmBar);
	mMenuList.push_back(bgmFront);
	mMenuList.push_back(bgmText);
	//mMenuList.push_back(sfxBack);
	mMenuList.push_back(sfxBar);
	mMenuList.push_back(sfxFront);
	mMenuList.push_back(sfxText);
	mMenuList.push_back(exit);
}

void Game::OnOption()
{
	for (int i = 0; i < mMenuList.size(); i++)
	{
		mCurrentScene->AddGlobalGameObject(mMenuList[i]);
	}

	// 일부 메뉴를 특정 씬에서만 활성 / 비활성화 한다.
	if (mCurrentScene->GetSceneName() != "Intro" && mCurrentScene->GetSceneName() != "StageOneOpening" &&
		mCurrentScene->GetSceneName() != "StageTwoOpening" && mCurrentScene->GetSceneName() != "StageThreeOneOpening")
	{
		dynamic_cast<ButtonBase*>(mMenuList[1])->SetActivate(true);
		dynamic_cast<ButtonBase*>(mMenuList[2])->SetActivate(true);
		dynamic_cast<ButtonBase*>(mMenuList[3])->SetActivate(true);
	}
	else
	{
		dynamic_cast<ButtonBase*>(mMenuList[1])->SetActivate(false);
		dynamic_cast<ButtonBase*>(mMenuList[2])->SetActivate(false);
		dynamic_cast<ButtonBase*>(mMenuList[3])->SetActivate(false);
	}

	int bgmNumber = SoundManager::GetInstance()->GetCurrentPlayBGM();

	if (bgmNumber != -1)
		SoundManager::GetInstance()->Pause(bgmNumber);
}

void Game::OffOption()
{
	for (int i = 0; i < mMenuList.size(); i++)
	{
		mCurrentScene->SubGlobalGameObject(mMenuList[i]);
	}

	int bgmNumber = SoundManager::GetInstance()->GetCurrentPlayBGM();

	if (bgmNumber != -1)
		SoundManager::GetInstance()->Resume(bgmNumber);
}