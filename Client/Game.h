#pragma once
#include "Scene.h"
#include "Resource.h"

class Exit;
class Title;
class Back;
class Restart;
class UIDecoObject;
class Player;
class CollisionGrid;

/**
 * Client에서 게임 진행을 총괄
 *
 * 2022. 02. 05. Comet
 */
class Game
{
public:
	Game();
	~Game();

	// Singleton
	static Game& GetInstance()
	{
		static Game instance;
		return instance;
	}

	void Initialize(HWND hWnd);

	// 현재 선택된 게임 씬의 Loop를 돌리면서 게임을 진행합니다.
	bool GameLoop();

	// 이 함수를 이용해 끈다.
	void EndGame();

private:
	// Game을 끝내야할 때 이 친구를 True로 켜줍니다.
	bool mIsEndGame;

	// 현재 이 게임 플레이어의 정보를 모두 담고 있겠습니다.
	// 매 씬 같은 정보를 가지고 있는 플레이어를 호출해야하기 때문입니다.
	Player* mGamePlayer;

	// 세이브 포인트에 도착했을 때 저장합니다.
	float mSaveBodyWeight;

	// 세이브 포인트에 도착했을 때 그 위치를 저장합니다.
	Vector2D mSavePosition;

	// 스테이지 3에 들어올 때 저장합니다. 이 친구를 통해서 엔딩을 븐기하겠습니다.
	float mLastBodyWeight;

	// 충돌 디버깅 모드
	bool mIsDebugMode;

	// 옵션 모드 => 스테이지에서만 킬 수 있다 ?
	bool mIsOptionOn;

public:
	Player* GetPlayer() const { return mGamePlayer; }

	// 마지막 몸무게 Save
	void SaveLastBodyWeight(float value) { mLastBodyWeight = value; }

	float GetLastBodyWeight() { return mLastBodyWeight; }

private:
	// Scene들을 모아둔다.
	std::map<std::string, Scene*> mScenes;

	// 현재 플레이 중인 스테이지 씬
	Scene* mCurrentStage;

	// 현재 게임 루프가 돌아갈 씬
	Scene* mCurrentScene;

	// Scene Load가 예약되면 여기에 저장해둡니다.
	Scene* mNextScene;

	// 씬 로드가 예약되어 있다면, 다음 프레임에 예약된 씬을 로드합니다.
	bool mIsReservedLoadScene;

public:
	// 씬을 등록합니다.
	void RegisterScene(Scene* scene);

	// Scene Load를 예약합니다.
	void ReserveLoadScene(std::string sceneName);

	// 예약이 되어 있다면 Scene을 Load합니다.
	void LoadScene();

	// 현재 Loop 중인 씬을 반환합니다. 이를 받아
	// 인 게임 중 로직에 따른 객체 생성 등을 진행할 예정입니다.
	Scene* GetCurrentScene() { return mCurrentScene; }

private:
	float mStagePlayTime;

private:
	// Resource Managing
	Resource* mResource;

public:
	// 밖에서는 이 함수를 통해 리소스에 접근합니다.
	Resource* GetResource() const { return mResource; }

public:
	// 스테이지 별로 빌드할 때 이거 해주면 되는거잖아 ..?
	void SetCurrentStage(Scene* scene);

	float GetSaveBodyWeight() { return mSaveBodyWeight; }
	void SetSaveBodyWeight(float value) { mSaveBodyWeight = value; }

	Vector2D GetSavePosition() { return mSavePosition; }
	void SetSavePosition(Vector2D position) { mSavePosition = position; }

	bool GetIsDebugMode() { return mIsDebugMode; }

	bool GetIsOptionOn() { return mIsOptionOn; }
	void OptionToggle();

	void SetIsOptionClicked() { mIsOptionClicked = true; }
	
	// 플레이어를 초기화 해줍니다.
	void InitPlayer();
	// 모든 씬들을 초기화 해줍니다.
	void InitScenes();
	// 옵션 초기화
	void InitOption();

private:
	void OnOption();
	void OffOption();

	std::vector<GameObject*> mMenuList;

	bool mIsOptionClicked;
};