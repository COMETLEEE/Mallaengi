#pragma once

#define FIXED_UPDATE_TIME 0.02

class Player;
class CollisionGrid;

// SortOrder에 따라서 multi-set이 정렬이 되도록 만들어주는 함수 객체
struct RendererCompare
{
	bool operator () (const Renderer* renderer1, const Renderer* renderer2) const
	{
		return renderer2->GetSortOrder() < renderer1->GetSortOrder();
	}
};

/*
 * Game Scene을 구성할 Base Scene
 *
 * 2022. 02. 05. Comet.
 */
class Scene
{
public:
	Scene(std::string sceneName);
	virtual ~Scene();

protected:
	std::string mSceneName;

	Player* mGamePlayer;

public:
	bool mIsFirstLoad;

protected:
	std::vector<GameObject*> mGameObjects;

	std::vector<GameObject*> mGlobalGameObjects;

	std::vector<Collision*> mCollisions;

	// Collision Grids !
	std::vector<CollisionGrid*> mCollisionGrids;

	std::multiset<Renderer*, RendererCompare> mRenderers;

	// 해당 씬의 카메라입니다. 카메라 컬링을 위해 사용됩니다.
	GameObject* mCamera;

public:
	void SetCamera(GameObject* camera) { mCamera = camera; }
	GameObject* GetCamera() { return mCamera; }

public:
	// 이 함수를 override하여, 씬을 구성합니다.
	// 그리고 우리 게임의 구성의 특성 상, 로드할 때 Scene을 초기화하고 다시 빌드한다.
	virtual void BuildScene();

	// -1. 본격적으로 프레임을 갱신하기 전에 사전 작업을 수행합니다.
	void PrePhase() const;

	// 0. Input, Timer 등의 데이터를 업데이트합니다.
	void DataPhase();

	// 1. 충돌 처리를 진행합니다.
	void PhysicsPhase() const;

	// 1-1. 물리 처리를 진행합니다.
	void FixedPhase() const;

	// 2. 데이터와 충돌에 따른 Game Logic을 업데이트합니다.
	void LogicPhase() const;

	// 3. 모든 처리 완료 후의 그림을 화면 상에 표현합니다.
	void RenderPhase() const;

	// while ('Data -> Physics -> Logic -> Render')
	void SceneLoop();

	// 씬 부수기
	void ClearScene();

	void LoadSceneData(const string& path, int mapCount);

	void LoadSceneDataStageThree(const string& path);

public:
	// Add GameObject at collection in scene.
	void AddGameObject(GameObject* object);
	// Add Global GameObject at collection in scene.
	void AddGlobalGameObject(GameObject* object);
	// Subtract GameObject at collection in Scene
	void SubGameObject(GameObject* object);
	// Subtract GameObject at collection in Scene
	void SubGlobalGameObject(GameObject* object);

	std::string GetSceneName();

	Player* GetPlayer() { return mGamePlayer; }
	void SetPlayer(Player* player) { mGamePlayer = player; }

private:
	std::vector<std::pair<GameObject*, float>> mCreateReserveList;
	std::vector<std::pair<GameObject*, float>> mDestroyReserveList;

public:
	// 생성을 예약합니다. 시간이 지나고 난 다음 프레임에 생성됩니다.
	void ReserveCreate(GameObject* object, float time = 0.f);
	// 삭제를 예약합니다. 시간이 지나면 난 다음 프레임에 삭제합니다.
	void ReserveDestroy(GameObject* object, float time = 0.f);
	// 삶과 죽음의 프로세스
	void BirthAndDeath();
};