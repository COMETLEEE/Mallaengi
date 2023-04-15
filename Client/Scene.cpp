#include "PreCompiledHeader.h"
#include "Scene.h"

#include "FadeInObject.h"
#include "Player.h"

#include "CollisionGrid.h"

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
#include "BigBarTrap.h"
#include "CatBoxTrap.h"
#include "DoorOpen.h"
#include "FakeTriggerBuilding.h"
#include "FallingBlockTriggerTrap.h"
#include "FallingEnemy.h"
#include "FallingPlatform.h"
#include "FreeEnemy.h"
#include "FallingTriggerTrap.h"
#include "KetchapTrap.h"
#include "KillMayo.h"
#include "Portal.h"
#include "SavePointBoxTrap.h"
#include "ShurikenPlatform.h"
#include "TriggerPigeon.h"
#include "UpperEnemy.h"
#include "UpperShuriken.h"
#include "WalkPad.h"
#include "DumbellDown.h"
#include "OneWayMob.h"
#include "OneWayMobTrigger.h"
#include "Niddle.h"
#include "RedRight.h"
#include "ExitPortal.h"
#include "RedUp.h"
#include "LRMob.h"
#include "BrokenHeart.h"
#include "SlowNiddle.h"
#include "TrapTile.h"
#include "FiveFalling.h"
#include "RidingNacho.h"

#include "SubCamera.h"
#include "TriggerDoor.h"

#define COLLISION_GRID_COUNT 52


Scene::Scene(std::string sceneName) :
	mSceneName(sceneName),
	mGameObjects(std::vector<GameObject*>()),
	mCollisions(std::vector<Collision*>()),
	mIsFirstLoad(true)
{

}

Scene::~Scene()
{

}

/// <summary>
/// 스프라이트 생성시 필요한 정보를 전달 받아서 동일한 동작을 하게 만든다.
/// </summary>
Sprite* MakeSprite(const std::vector<TileData>::iterator& iter, Vector2D rectpos = {}, Vector2D pivot = Vector2D(0.5f, 0.5f), float delayTime = 0.f)
{
	D2D1_RECT_F rect = iter->imageRect;

	Sprite* sprite = new Sprite(iter->imageID, pivot,
		{ rect.right - rect.left + 1, rect.bottom - rect.top + 1 }, delayTime, Vector2D(rect.left, rect.top) + rectpos);

	return sprite;
}

/// <summary>
/// 인자로 오브젝트의 위치와, 생성자에 필요한 매개 변수를 가변 인자로 받는다.
/// </summary>
template <class T, typename... argsT>
T* MakeObject(Vector2D pos, argsT ... args)
{
	T* newObject = new T(args...);
	newObject->GetTransform()->SetPosition(pos);

	return newObject;
}

void Scene::BuildScene()
{
	mGamePlayer->SetPlayerState(PlayerState::Idle);

	// 플레이어의 시간을 0으로 .. 죽으면 초기화한다 ..! 의 충분조건을 만족.
	mGamePlayer->SetStagePlayTime(0.f);

	//for (int i = 0; i < COLLISION_GRID_COUNT; i++)
	//{
	//	CollisionGrid* grid = new CollisionGrid(Vector2D(-1000 + 2000 * (i % 12), 1000 + 1000 * static_cast<int>(i / 12)));

	//	mCollisionGrids.push_back(grid);

	//	AddGameObject(grid);
	//}
}

void Scene::PrePhase() const
{
	// 전 프레임에서 사용한 충돌 여부 / 충돌 정보 전부 초기화
	for (Collision* collision : mCollisions)
	{
		collision->SetIsCollision(false);
		collision->GetCollisionInfo().clear();
	}

	//for (CollisionGrid* grid : mCollisionGrids)
	//	grid->mCollisions.clear();
}

void Scene::DataPhase()
{
	// Timer Update
	Timer::GetInstance().Update();

	// Key Input Update
	Input::GetInstance().Update();

	// 이거 작업표시줄 눌렀을 때 이상한 움직임을 방지하기 위한 코드인데 .. 나중에 뺍시다.
	if (Timer::GetInstance().GetDeltaTime() / 1000.f > 0.04f)
		Timer::GetInstance().Update();

	// 기타 해당 Scene에서 필요한 Data 조작 Update
	BirthAndDeath();
}

void Scene::PhysicsPhase() const
{
#pragma region Collision
	//// 어떻게하면 최적화를 할 수 있을지, 생각할 필요가 있다.
	//for (Collision* firCollision : mCollisions)
	//	for (Collision* SecCollision : mCollisions)
	//	{
	//		if (firCollision == SecCollision)
	//			continue;

	//		firCollision->CheckCollision(SecCollision);
	//	}

	//// 1. 그리드랑 대충 AABB 체킹
	//for (CollisionGrid* grid : mCollisionGrids)
	//{
	//	Vector2D gridPos = grid->GetTransform()->GetPosition();

	//	for (GameObject* object : mGameObjects)
	//	{
	//		// 하 .. 이거 리스트 저장하고 있는 방법 알면 충분히 더 확실하게 최적화 가능한데 따로 공부할 시간이 부족 ..
	//		
	//		Vector2D pos = object->GetTransform()->GetPosition();

	//		if ((abs(gridPos.GetX() - pos.GetX()) < GRID_HALF_WIDTH + 70.f)
	//			&& (abs(gridPos.GetY() - pos.GetY()) < GRID_HALF_HEIGHT + 70.f))
	//		{
	//			Collision* collision = object->GetCollision();

	//			if (collision != nullptr)
	//				grid->mCollisions.push_back(collision);
	//		}
	//	}
	//}

	//// 2. 그리드 안에서 체크
	//for (CollisionGrid* grid : mCollisionGrids)
	//{
	//	std::vector<Collision*> collisions = grid->mCollisions;

	//	for (Collision* firCollision : collisions)
	//	{
	//		for (Collision* secCollision : collisions)
	//		{
	//			// 플랫폼 등의 충돌의 영향을 받아야 하는 녀석들 (Player, Enemy, Item)
	//			// 여길 넣으면 그냥 초 완전 최적화가 완성된다 ..
	//			std::string tag = firCollision->GetGameObject()->GetTag();

	//			if ((tag == "Player") || (tag == "Enemy"))
	//				firCollision->CheckCollision(secCollision);
	//		}
	//	}
	//}
#pragma endregion
	// 금단의 최적화 스킬 ..
	for (Collision* firCollision : mCollisions)
	{
		// 플랫폼 등의 충돌의 영향을 받아야 하는 녀석들 (Player, Enemy, Item)
		// 여길 넣으면 그냥 초 완전 최적화가 완성된다 ..
		std::string tag = firCollision->GetGameObject()->GetTag();

		if ((tag == "Player") || (tag == "Enemy"))
			for (Collision* secCollision : mCollisions)
				firCollision->CheckCollision(secCollision);
	}
}

void Scene::FixedPhase() const
{
	if (Game::GetInstance().GetIsOptionOn())
	{
		for (GameObject* object : mGameObjects)
			if (object->GetTag() == "UI")
				object->FixedUpdate();
	}
	else if ((mGamePlayer->GetCurrentState() == PlayerState::Trans) || (mGamePlayer->GetCurrentState() == PlayerState::Die))
	{
		for (GameObject* object : mGameObjects)
			if ((object->GetTag() == "Player") || (object->GetTag() == "UI") || (object->GetTag() == "Camera") || (object->GetTag() == "BackGround"))
				object->FixedUpdate();
	}
	else
	{
		for (GameObject* object : mGameObjects)
			object->FixedUpdate();
	}
}

void Scene::LogicPhase() const
{
	// 만약 Option이 켜져있다면
	// UI만 업데이트한다. (플레이어 죽음, 트랜스보다 옵션이 먼저 위야)
	if (Game::GetInstance().GetIsOptionOn())
	{
		for (GameObject* object : mGameObjects)
			if ((object->GetTag() == "UI") || (object->GetTag() == "Camera") || (object->GetTag() == "BackGround"))
				object->Update();

		for (GameObject* object : mGlobalGameObjects)
			if ((object->GetTag() == "UI") || (object->GetTag() == "Camera") || (object->GetTag() == "BackGround"))
				object->Update();

		for (GameObject* object : mGameObjects)
			if ((object->GetTag() == "UI") || (object->GetTag() == "Camera") || (object->GetTag() == "BackGround"))
				object->LateUpdate();

		for (GameObject* object : mGlobalGameObjects)
			if ((object->GetTag() == "UI") || (object->GetTag() == "Camera") || (object->GetTag() == "BackGround"))
				object->LateUpdate();
	}
	// 플레이어가 Trans Or Die 상태일 때 UI와 PLAYER의 Update만 진행합니다.
	else if ((mGamePlayer->GetCurrentState() == PlayerState::Trans) || (mGamePlayer->GetCurrentState() == PlayerState::Die))
	{
		for (GameObject* object : mGameObjects)
			if ((object->GetTag() == "Player") || (object->GetTag() == "UI") || (object->GetTag() == "Camera") || (object->GetTag() == "BackGround"))
				object->Update();

		for (GameObject* object : mGlobalGameObjects)
			if ((object->GetTag() == "Player") || (object->GetTag() == "UI") || (object->GetTag() == "Camera") || (object->GetTag() == "BackGround"))
				object->Update();

		for (GameObject* object : mGameObjects)
			if ((object->GetTag() == "Player") || (object->GetTag() == "UI") || (object->GetTag() == "Camera") || (object->GetTag() == "BackGround"))
				object->LateUpdate();

		for (GameObject* object : mGlobalGameObjects)
			if ((object->GetTag() == "Player") || (object->GetTag() == "UI") || (object->GetTag() == "Camera") || (object->GetTag() == "BackGround"))
				object->LateUpdate();
	}
	else
	{
		for (GameObject* object : mGameObjects)
			object->Update();

		for (GameObject* object : mGlobalGameObjects)
			object->Update();

		for (GameObject* object : mGameObjects)
			object->LateUpdate();

		for (GameObject* object : mGlobalGameObjects)
			object->LateUpdate();
	}
}

void Scene::RenderPhase() const
{
	Graphics::GetInstance().BeginRender();

	Vector2D cameraPos = mCamera->GetTransform()->GetPosition();

	for (Renderer* renderer : mRenderers)
	{
		/*Vector2D objectPos = renderer->GetGameObject()->GetTransform()->GetPosition();

		if ((abs(cameraPos.GetX() - objectPos.GetX()) < size.width / 2 * 1.3f + 200.f)
			&& (abs(cameraPos.GetY() - objectPos.GetY()) < size.height / 2 * 1.3f + 200.f))
		{
		}*/
		renderer->Render();
#pragma region DEBUG_MODE
		// Debug Mode
		if (Game::GetInstance().GetIsDebugMode())
		{
			GameObject* object = renderer->GetGameObject();

			Collision* collision = object->GetCollision();

			if (collision != nullptr)
			{
				AABBCollision* aabbcollision = dynamic_cast<AABBCollision*>(collision);

				D2D1_SIZE_F size = aabbcollision->GetSize();

				if (aabbcollision->GetIsCollision())
					Graphics::GetInstance().DrawRectangle(Vector2D(0, 0), size, D2D1::ColorF(1, 0, 0, 1));
				else
					Graphics::GetInstance().DrawRectangle(Vector2D(0, 0), size, D2D1::ColorF(0, 1, 0, 1));

				// 디버그에서 타일의 ID 출력
				TCHAR buf[16];
				_stprintf_s(buf, _T("%d"), object->GetID());
				Graphics::GetInstance().DrawText(-size.width / 2, -size.height / 2, buf);
			}
		}
	}

	// 노가다할 때 도움이 될 코드
	// 충돌박스 디버그모드 외에 빼놓기
	// Debug Mode -> 인게임씬의 디버그. 씬이 달라지면 위치 변경
	if (Game::GetInstance().GetIsDebugMode())
	{
		// 스테이지3에서는 글자가 따라다님 왜?
		D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

		Graphics::GetInstance().DrawText(size.width - 2100, size.height - 1000, "FPS : %.3f", Timer::GetInstance().GetDeltaTime() / 1000.f);
		//-70, -40
		Vector2D _pos = mGamePlayer->GetTransform()->GetPosition();

		Graphics::GetInstance().DrawText(size.width - 2100, size.height - 900, "Pos X : %f", _pos.mX);

		Graphics::GetInstance().DrawText(size.width - 2100, size.height - 800, "뭐더 찍을거 있나");
	}

	// /* 스테이지 3 의 디버그 가능?
	if (Game::GetInstance().GetIsDebugMode())
	{
		// 으,라어ㅓ니ㅓ아ㅣ린ㅇ
		// 카메라를 서브 카메라로바꾸기 -> 서브카메라는 고정이므로 좌표만 찍으면 된다 (0, 0, 19020, 1080) 스벌
		//SubCamera* subcamera = new SubCamera;
		
		//subcamera->GetCamera();
		//AddGameObject(new SubCamera());
		// D2D1_SIZE_F size = Graphics::GetInstance().SetCamera();
		//D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

		//Graphics::GetInstance().DrawText( 0, 0, "FPS : %.3f", Timer::GetInstance().GetDeltaTime() / 1000.f);
		
		//Vector2D _pos = mGamePlayer->GetTransform()->GetPosition();
		
		//Graphics::GetInstance().DrawText(0, 0, "Pos X : %f", _pos.mX);
		
		//Graphics::GetInstance().DrawText(0, 0, "맞냐 나와라");

	}
	//*/

#pragma endregion

	Graphics::GetInstance().EndRender();
}

// 만약 플레이어가 죽거나, 단계가 변화하는 상황이라면 다른 친구들의 Update는 멈추고
// 플레이어만 Update 합니다 ..!

// 플레이어가 이번 프레임에서 단계가 변화했는지 || PlayerState::Die 인지 체크해서 돌립니다.
void Scene::SceneLoop()
{
	this->PrePhase();

	this->DataPhase();

	this->FixedPhase();

	this->PhysicsPhase();

	this->LogicPhase();

	this->RenderPhase();
}

void Scene::ClearScene()
{
	// 플레이어를 제외한 Object들을 삭제 !
	for (auto& object : mGameObjects)
	{
		if ((object != mGamePlayer) && (object != nullptr))
		{
			object->Release();
			delete object;
		}
	}

	// 컬렉션 내부에 있는 친구들 Clear
	mGameObjects.clear();
	mRenderers.clear();
	mCollisions.clear();
	mCollisionGrids.clear();

	// 예약 컬렉션 내부에 있는 친구들 clear
	mCreateReserveList.clear();
	mDestroyReserveList.clear();
}

void Scene::LoadSceneData(const string& path, int mapCount)
{
	MapJson stageOne;

	GameObject* newObject = nullptr;

	float idleTimeControl = 0.f;

	for (int i = 0; i < mapCount; i++)
	{
		// 맵이 하나인 경우 바로 불러오고 여러개인 경우 순서대로 불러온다.
		if (mapCount == 1)
		{
			stageOne.DeserializeFromCArchive(path);
		}
		else
		{
			TCHAR buf[256];

			_stprintf_s(buf, path.c_str(), i + 1);

			stageOne.DeserializeFromCArchive(buf);
		}

		for (auto iter = stageOne.mTileList.begin(); iter != stageOne.mTileList.end(); iter++)
		{
			// 1. 몇 번째 타일에 이것이 들어왔는지 체크합니다.
			float _yOriTile = (iter->index >> 16);
			float _xOriTile = (iter->index & 0xffff);

			// 그룹 타일의 갯수로 객체의 중점을 계산합니다.
			float _yTile = (_yOriTile)+(1.0f + (iter->group.back() >> 16)) / 2;
			float _xTile = (_xOriTile)+(1.0f + (iter->group.back() & 0xffff)) / 2;

			// 맵 갯수에 따라 좌표를 설정해줍니다.
			Vector2D objectPos = { (_xTile + 100 * i) * TILE_WIDTH, _yTile * TILE_HEIGHT };

			// 플랫폼 타일 (잔디가 있는, 올라갈 수 있는 것이다)
			if ((iter->ID == 10101001) || (iter->ID == 10101002) || (iter->ID == 10101003))
			{
				newObject = MakeObject<Platform>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			// 플랫폼 타일 (잔디가 없는, 올라갈 수 없는 것이다)
			else if ((iter->ID == 10101004) || (iter->ID == 10101005) || (iter->ID == 10101006)
				|| (iter->ID == 10101007) || (iter->ID == 10101008) || (iter->ID == 10101009))
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			// 플랫폼 타일 (관통이 불가능한, 위에만 설 수 있는)
			else if ((iter->ID == 10101010) || (iter->ID == 10101011) || (iter->ID == 10101012) || (iter->ID == 10101013) || (iter->ID == 10101014)
				|| (iter->ID == 10101015))
			{
				newObject = MakeObject<BoxBase>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if ((iter->ID == 10101017) || (iter->ID == 10101018))
			{
				newObject = MakeObject<BoxBase>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			// 에어 타일 ~
			else if ((iter->ID == 10102001) || (iter->ID == 10102002) || (iter->ID == 10102003))
			{
				newObject = MakeObject<Platform>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}

			// 머드 타일
			else if ((iter->ID == 10103001) || (iter->ID == 10103002) || (iter->ID == 10103003))
			{
				newObject = MakeObject<Platform>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			// 머드 타일 내부 및 하단
			else if ((iter->ID == 10103004) || (iter->ID == 10103005) || (iter->ID == 10103006) || (iter->ID == 10103007) || (iter->ID == 10103008) || (iter->ID == 10103009))
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}

			else if (iter->ID == 101001)	// Tree (apple X)
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 102002)	// Tree (apple O)
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101003)	// Street Lamp (1)
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101004)	// Street Lamp (2)
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101005)	// Lamp (떨어지는 램프)
			{
				newObject = MakeObject<FallingTriggerTrap>(objectPos, 1300.f);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101006)	// Store
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101007)	// Sign
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101008)	// Cloud 1
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101009)	// Cloud 2
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101010)	// Cloud 3
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101011)	// 빌딩 (스테이지 1 포탈)
			{
				newObject = MakeObject<Portal>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101012)	// 햄버거
			{
				newObject = MakeObject<FreeEnemy>(objectPos + 150.f * Vector2D::Up, "Hamburger");

				AddGameObject(newObject);
			}
			else if (iter->ID == 101013)	// 햄버거 2
			{

			}
			else if (iter->ID == 101014)	// 킬 클라우드 (닿으면 죽는건가 ..?)
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101015)	// 피존, 그레이
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101016)	// 피존, 블랙
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101017)	// 우드 박스
			{
				newObject = MakeObject<Platform>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 101018)	// 무빙 플랫폼 (위, 아래 5칸)
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<UDMovingPlatform>(objectPos, startPos, 5, 2, idleTimeControl, "Block");

				idleTimeControl += TILE_HEIGHT * 5 / UD_MOVING_SPEED;

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				AddGameObject(newObject);
			}
			else if (iter->ID == 101019)	// 무빙 플랫폼 (왼, 오 7칸)
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<LRMovingPlatform>(objectPos, startPos, 7, 3, 0.f);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				AddGameObject(newObject);
			}
			else if (iter->ID == 102001)	// Item Box - 말랭 1
			{
				Food* reserve = new Food(-0.5f, 20106, Vector2D(80.f, 80.f), true);

				reserve->GetTransform()->SetPosition(objectPos);

				newObject = MakeObject<ItemBox>(objectPos, reserve, 1);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 102002)	// Item Box - 말랭 2
			{
				Food* reserve = new Food(-0.5f, 20106, Vector2D(240.f, 80.f), true);

				reserve->GetTransform()->SetPosition(objectPos);

				newObject = MakeObject<ItemBox>(objectPos, reserve, 1);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 102003)	// Item Box - Ketchup
			{
				Food* reserve = new Food(-0.5f, 20103, Vector2D(1360.f, 563.f), true);

				reserve->GetTransform()->SetPosition(objectPos);

				newObject = MakeObject<ItemBox>(objectPos, reserve, 1);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 102004)	// 텅빈 박스
			{
				newObject = MakeObject<ItemBox>(objectPos, nullptr, 1);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 102005)	// 캣 몬스터 ..? 뭐냐 이거는
			{
				newObject = MakeObject<ItemBox>(objectPos, nullptr, 1);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 102006 || iter->ID == 102011)	// Block
			{
				newObject = MakeObject<BreakableBlock>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 103001)	// Mayo
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 103002)	// 케찹
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 103003)	// 마요 케이스
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 103004)	// 케첩 케이스
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104001)	// 도넛
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104002)	// 나초
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104003)	// 칠리 나초
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104004)	// 꿀나초
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104005)	// 바질나초 .. 나초지옥
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104006)	// 팝콘 케이스
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104007)	// 팝콘 존나 꽉찬
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104008)	// 그냥 팝콘 (?)
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104009)	// 꽈자
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104010)	// 작은 사과
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104011)	// 큰 사과
			{
				newObject = MakeObject<FallingTriggerTrap>(objectPos, 1300.f);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104012)	// 말랭바 1
			{
				newObject = MakeObject<Food>(objectPos, Food::mMallaengBar, iter->imageID, Vector2D(iter->imageRect.left, iter->imageRect.top), false);

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104013)	// 말랭바 2
			{
				newObject = MakeObject<Food>(objectPos, Food::mMallaengBar, iter->imageID, Vector2D(iter->imageRect.left, iter->imageRect.top), false);

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 104014)	// 썩은 말랭바
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 105001)	// 우드 박스
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 105002)	// 밴취
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 105003)	// 부쉬
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 106001)	// 페이크 플래그
			{
				newObject = MakeObject<KetchapTrap>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 107001)	// 리얼 플래그
			{
				newObject = MakeObject<CheckPoint>(objectPos);

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			// Trap (구현하고 하나씩 넣을 필요가 있다
			else if (iter->ID == 109001)	// 인비지블 박스 (1) => 박으면 초록색 사용한 박스로 바뀜
			{
				newObject = MakeObject<TransBox>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter, Vector2D(160.f, 0.f)));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				newObject->GetSpriteRenderer()->SetOpacity(0.f);

				AddGameObject(newObject);
			}

			else if (iter->ID == 109003)	// 인비지블박스 3 (3스테이지 박스 받으면 그걸로)
			{
				newObject = MakeObject<TransBox>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter, Vector2D(160.f, 0.f)));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				newObject->GetSpriteRenderer()->SetOpacity(0.f);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109004)	// 나초 (먹으면 죽는)
			{
				newObject = MakeObject<TriggerTrap>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109005)	// 나초 (위로 상승하는)
			{
				newObject = MakeObject<RisingTrap>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109006)	// 나초 (위로 상승하는)
			{
				newObject = MakeObject<RisingTrap>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109007)	// 나초 (위로 상승하는)
			{
				newObject = MakeObject<RisingTrap>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109008)	// 폴링 블락 (3)
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<FallingBlock>(objectPos, startPos, 3);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109009)	// 폴링 블락 (1)
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<FallingBlock>(objectPos, startPos, 1);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109010)	// 나초 슈리켄
			{
				newObject = MakeObject<UpperShuriken>(objectPos);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109011)	// 트리거 나초
			{
				newObject = MakeObject<TriggerTrap>(objectPos, true);		// 이미지 관통 출력형

				newObject->GetTransform()->SetPosition(newObject->GetTransform()->GetPosition() + 27.f * Vector2D::Down);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109012)	// 추락 트리거 폴링 블락 (3)
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<FallingBlockTriggerTrap>(objectPos, startPos, 3);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109014)	// 죽음의 클라우드
			{
				newObject = MakeObject<TriggerTrap>(objectPos, new Sprite(20105, Vector2D(0.5f, 0.5f), { 1270 - 960, 480 - 243 }, 0.f, Vector2D(960.f, 243.f)));

				dynamic_cast<AABBCollision*>(newObject->GetCollision())->SetSize({ TILE_WIDTH * 4, TILE_HEIGHT * 2 });

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109015)	// 페이크 포탈 ?
			{
				newObject = MakeObject<FakeTriggerBuilding>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109016)	// 트리거 트리
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109017)	// 트리거 램프
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109018)	// 폴링 플랫폼
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<FallingPlatform>(objectPos, startPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109020)	// 폴링 에어 타일
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<FallingBlock>(objectPos, startPos, 3);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109022)	// Upper Hamburger 
			{
				newObject = MakeObject<UpperEnemy>(objectPos, "Hamburger");

				AddGameObject(newObject);
			}
			else if (iter->ID == 109024)	// 피존
			{
				newObject = MakeObject<TriggerPigeon>(objectPos, "Gray");

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109025)	// 피존
			{
				newObject = MakeObject<TriggerPigeon>(objectPos, "Black");

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109026)	// 찍으면 세이브 포인트가 나오는 박스
			{
				newObject = MakeObject<SavePointBoxTrap>(objectPos, new KillMayo());

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109027)	// 트리거 발판
			{
				newObject = MakeObject<ShurikenPlatform>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109028)	// 폴링 플랫폼
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<FallingBlockTriggerTrap>(objectPos, startPos, 1);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(4);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109029)
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<FallingBlockTriggerTrap>(objectPos, startPos, 3);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(4);

				AddGameObject(newObject);
			}
			// Falling Hamburger의 본체
			else if (iter->ID == 10104001)
			{
				newObject = MakeObject<FallingEnemy>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}

			// ---------------- Stage 2 --------------------
			// Tiles
			else if ((iter->ID == 20101001) || (iter->ID == 20101002) || (iter->ID == 20101003) || (iter->ID == 20101004) ||
				(iter->ID == 20101005) || (iter->ID == 20101006) || (iter->ID == 20101007) || (iter->ID == 20101008) || (iter->ID == 20101009) ||
				(iter->ID == 20101010) || (iter->ID == 20101011) || (iter->ID == 20101012) || (iter->ID == 20101013) || (iter->ID == 20101014) ||
				(iter->ID == 20101015) || (iter->ID == 20101016) || (iter->ID == 20101017) || (iter->ID == 20101018) || (iter->ID == 20101019) ||
				(iter->ID == 20101020) || (iter->ID == 20101021) || (iter->ID == 20101022) || (iter->ID == 20101023) || (iter->ID == 20101024) ||
				(iter->ID == 20101025) || (iter->ID == 20101026) || (iter->ID == 20101027))
			{
				newObject = MakeObject<BlockBase>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 109002)	// 인비지블박스 2 (2스테이지 박스 받으면 그걸로)
			{
				newObject = MakeObject<TransBox>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter, Vector2D(320.f, 0.f)));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				newObject->GetSpriteRenderer()->SetOpacity(0.f);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202001)	// Door Open
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202002)	// Door Close
			{
				/*newObject = MakeObject<Portal>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);*/
			}
			else if (iter->ID == 202003)	// 벤치프레스
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202004)	// 싸이클
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202005)	// 스미스머신	
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202006)	// WalkPad Left
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) + 5 };

				for (int i = 0; i < 4; i++)
				{
					BlockBase* block = new BlockBase();

					block->GetTransform()->SetPosition(startPos + Vector2D(i * TILE_WIDTH, 0.f));

					Game::GetInstance().GetCurrentScene()->AddGameObject(block);
				}

				newObject = MakeObject<WalkPad>(objectPos, Vector2D(-1.f, 0.f));

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				dynamic_cast<AABBCollision*>(newObject->GetCollision())->SetSize({ TILE_WIDTH * 4, TILE_HEIGHT });

				AddGameObject(newObject);
			}
			else if (iter->ID == 202007)	// WalkPad Right
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) + 5 };

				for (int i = 0; i < 4; i++)
				{
					BlockBase* block = new BlockBase();

					block->GetTransform()->SetPosition(startPos + Vector2D(i * TILE_WIDTH, 0.f));

					Game::GetInstance().GetCurrentScene()->AddGameObject(block);
				}

				newObject = MakeObject<WalkPad>(objectPos, Vector2D(1.f, 0.f));

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				dynamic_cast<AABBCollision*>(newObject->GetCollision())->SetSize({ TILE_WIDTH * 4, TILE_HEIGHT });

				AddGameObject(newObject);
			}
			else if (iter->ID == 202008)	// 덜덜이
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202009)	// 샌드백
			{
				newObject = MakeObject<FreeEnemy>(objectPos + 200.f * Vector2D::Up, "SandBag");

				//newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202011)	// 덤벨 몬스터
			{
				newObject = MakeObject<FreeEnemy>(objectPos + 200.f * Vector2D::Up, "Dum");

				AddGameObject(newObject);
			}
			else if (iter->ID == 202012)	// 니들 덤벨
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202013)	// 니들 덤벨 라지
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202014)	// 니들덤벨 ss
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202015)	// 니들덤벨 sl
			{
				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202016)	// 무빙 3
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<UDMovingPlatform>(objectPos, startPos, 5, 3, idleTimeControl, "Block");

				idleTimeControl += TILE_HEIGHT * 5 / UD_MOVING_SPEED;

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				AddGameObject(newObject);
			}
			else if (iter->ID == 202017)	// 무빙 4
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<LRMovingPlatform>(objectPos, startPos, 7, 4, 0.f);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				AddGameObject(newObject);
			}
			else if (iter->ID == 202018)	// 샌드백 몬스터 (왼쪽 감지형)
			{
				newObject = MakeObject<OneWayMob>(objectPos + 200.f * Vector2D::Up, "SandBag", 300.f);

				AddGameObject(newObject);
			}
			else if (iter->ID == 202019)	// 샌드백 몬스터 (우측 감지형, 스폰되는 형)
			{
				newObject = MakeObject<OneWayMobTrigger>(objectPos, "SandBag", 300.f, Vector2D(1.f, 0.f));

				AddGameObject(newObject);
			}
			else if (iter->ID == 202020)	// 덤벨 몬스터 (왼쪽 감지형)
			{
				newObject = MakeObject<OneWayMob>(objectPos + 200.f * Vector2D::Up, "Dum", 300.f);

				AddGameObject(newObject);
			}
			else if (iter->ID == 203001)	// 아이템 박스 - 말랭바 2
			{
				Food* reserve = new Food(-0.5f, 20106, Vector2D(240.f, 80.f), true);

				reserve->GetTransform()->SetPosition(objectPos);

				newObject = MakeObject<ItemBox>(objectPos, reserve, 2);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 203002)	// 블럭
			{
				newObject = MakeObject<BreakableBlock>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 203003)	// 텅빈 박스
			{
				newObject = MakeObject<ItemBox>(objectPos, nullptr, 2);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 203004)	// 아이템 박스 - 캣
			{
				CatBoxTrap* trap = new CatBoxTrap();

				// TODO: 애니메이션도 있다
				newObject = MakeObject<ItemBox>(objectPos, trap, 2);

				trap->GetTransform()->SetPosition(objectPos + Vector2D(-40.f, 0.f));

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 203005)	// 아이템 박스 - Rotten
			{
				Food* reserve = new Food(-0.5f, 20106, Vector2D(240.f, 80.f), true);

				reserve->GetTransform()->SetPosition(objectPos);

				newObject = MakeObject<BigBarTrap>(objectPos, reserve);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 203009)	// 뾰족 가시
			{
				Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile + 100 * i) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

				newObject = MakeObject<DecoObject>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);

				TriggerTrap* trigger = new TriggerTrap();

				trigger->GetTransform()->SetPosition(startPos);

				Game::GetInstance().GetCurrentScene()->AddGameObject(trigger);
			}
			else if (iter->ID == 203011)	// ItemBox - Door Open
			{
				newObject = MakeObject<DoorOpen>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				std::vector<TriggerTrap*> traps = dynamic_cast<DoorOpen*>(newObject)->GetTriggerTraps();

				traps[0]->GetTransform()->SetPosition(newObject->GetTransform()->GetPosition() - Vector2D(0.f, TILE_HEIGHT * 5));

				Game::GetInstance().GetCurrentScene()->AddGameObject(traps[0]);

				traps[1]->GetTransform()->SetPosition(newObject->GetTransform()->GetPosition() - Vector2D(0.f, TILE_HEIGHT * 4));

				traps[1]->GetSpriteRenderer()->SetSprite(new Sprite(20115, Vector2D(0.25f, 0.5f), { 160.f, 385.f }, 0.f, Vector2D(800.f, 15.f)));

				traps[1]->GetSpriteRenderer()->SetSortOrder(6);

				Game::GetInstance().GetCurrentScene()->AddGameObject(traps[1]);

				traps[2]->GetTransform()->SetPosition(newObject->GetTransform()->GetPosition() - Vector2D(0.f, TILE_HEIGHT * 3));

				Game::GetInstance().GetCurrentScene()->AddGameObject(traps[2]);

				Game::GetInstance().GetCurrentScene()->AddGameObject(newObject);
			}
			else if (iter->ID == 205001)	// 초코, 먹으면 살이 찐다.
			{
				newObject = MakeObject<Food>(objectPos, 1.0f, iter->imageID, Vector2D(iter->imageRect.left, iter->imageRect.top), false);

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 206001)	// 니들업
			{
				newObject = MakeObject<Niddle>(objectPos + Vector2D(0.f, TILE_HEIGHT), CollisionDir::UP);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(4);

				AddGameObject(newObject);
			}
			else if (iter->ID == 206002)	// 캐틀벨 폴링
			{
				newObject = MakeObject<FallingTriggerTrap>(objectPos, 2800.f);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 206003)	// 덤벨 어퍼 ..
			{
				newObject = MakeObject<RisingTrap>(objectPos);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

				AddGameObject(newObject);
			}
			else if (iter->ID == 206004)		// 니들 덤벨 다운
			{
				newObject = MakeObject<DumbellDown>(objectPos, "NiddleDown");

				AddGameObject(newObject);
			}
			else if (iter->ID == 206005)		// 덤벨 다운
			{
				newObject = MakeObject<DumbellDown>(objectPos, "Down");

				AddGameObject(newObject);
			}
			else if (iter->ID == 206006)		// 니들 레프트
			{
				newObject = MakeObject<Niddle>(objectPos + Vector2D(TILE_WIDTH, 0.f), CollisionDir::LEFT);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(4);

				AddGameObject(newObject);
			}
			else if (iter->ID == 206007)		// 니들 라이트
			{
				newObject = MakeObject<Niddle>(objectPos - Vector2D(TILE_WIDTH, 0.f), CollisionDir::RIGHT);

				newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

				newObject->GetSpriteRenderer()->SetSortOrder(6);

				AddGameObject(newObject);
			}
			else if (iter->ID == 206008)
			{
				newObject = MakeObject<UpperEnemy>(objectPos, "SandBag");

				AddGameObject(newObject);
			}

			newObject->SetID(iter->ID);
		}

		stageOne.mTileList.clear();
	}
}

void Scene::LoadSceneDataStageThree(const string& path)
{
	MapJson stage;

	GameObject* newObject = nullptr;

	float idleTimeControl = 0.f;

	stage.DeserializeFromCArchive(path);

	for (auto iter = stage.mTileList.begin(); iter != stage.mTileList.end(); iter++)
	{
		// 1. 몇 번째 타일에 이것이 들어왔는지 체크합니다.
		float _yOriTile = (iter->index >> 16);
		float _xOriTile = (iter->index & 0xffff);

		// 그룹 타일의 갯수로 객체의 중점을 계산합니다.
		float _yTile = (_yOriTile)+(1.0f + (iter->group.back() >> 16)) / 2;
		float _xTile = (_xOriTile)+(1.0f + (iter->group.back() & 0xffff)) / 2;

		// 맵 갯수에 따라 좌표를 설정해줍니다.
		Vector2D objectPos = { (_xTile)*TILE_WIDTH, _yTile * TILE_HEIGHT };

		// ------------------ Stage 3 ---------------------
		// Tiles : All Normal Block
		if ((iter->ID == 20102001) || (iter->ID == 20102002) || (iter->ID == 20102003) || (iter->ID == 20102004) ||
			(iter->ID == 20102005) || (iter->ID == 20102006) || (iter->ID == 20102007) || (iter->ID == 20102008) ||
			(iter->ID == 20102009) || (iter->ID == 20102010) || (iter->ID == 20102011) || (iter->ID == 20102012) ||
			(iter->ID == 20102013) || (iter->ID == 20102014) || (iter->ID == 20102015) || (iter->ID == 20102016) ||
			(iter->ID == 20102017) || (iter->ID == 20102018) || (iter->ID == 20102019) || (iter->ID == 20102020) ||
			(iter->ID == 20102021) || (iter->ID == 20102022) || (iter->ID == 20102023) || (iter->ID == 20102024))
		{
			newObject = MakeObject<BlockBase>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 102004)			// 텅빈 박스
		{
			newObject = MakeObject<ItemBox>(objectPos, nullptr, 1);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 109011)			// 트리거 나초
		{
			newObject = MakeObject<TriggerTrap>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 109031)		// 라이징 나초 (슬로우)
		{
			newObject = MakeObject<RedUp>(objectPos, Vector2D::Up, 1300.f);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(6);

			AddGameObject(newObject);
		}
		else if (iter->ID == 109032)		// 라이징 나초 (노멀)
		{
			newObject = MakeObject<RedUp>(objectPos, Vector2D::Up, 1800.f);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(6);

			AddGameObject(newObject);
		}
		else if (iter->ID == 109033)		// 라이징 나초 (패스트)
		{
			newObject = MakeObject<RedUp>(objectPos, Vector2D::Up, 2500.f);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(6);

			AddGameObject(newObject);
		}
		else if (iter->ID == 206003)	// 덤벨 어퍼 ..
		{
			newObject = MakeObject<RisingTrap>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 107001)	// 리얼 플래그
		{
			newObject = MakeObject<CheckPoint>(objectPos);

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		// Arrow
		else if ((iter->ID >= 210001) && (iter->ID <= 210024))
		{
			newObject = MakeObject<DecoObject>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			AddGameObject(newObject);
		}
		else if (iter->ID == 211001)		// 브로큰 하트 (스프라이트 이미지를 교체하면서 추락)
		{
			newObject = MakeObject<BrokenHeart>(objectPos);

			dynamic_cast<BrokenHeart*>(newObject)->mChangeSprite = new Sprite(20116, Vector2D(0.5f, 0.5f), { 160.f, 77.f }, 0.f, Vector2D(800.f, 81.f));

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 211003)		// EXIT : 이동포탈
		{
			newObject = MakeObject<ExitPortal>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 211004)		//  하얀 블록
		{
			newObject = MakeObject<BreakableBlock>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 211005)		// 회색 블록
		{
			newObject = MakeObject<BreakableBlock>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 211006)		// 3칸짜리 / 가로 5칸
		{
			Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

			newObject = MakeObject<LRMovingPlatform>(objectPos, startPos, 5, 3, 0.f);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			AddGameObject(newObject);
		}
		else if (iter->ID == 211007)		// 3칸짜리 / 세로 7칸
		{
			Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

			newObject = MakeObject<UDMovingPlatform>(objectPos, startPos, 7, 3, 0.f, "Platform");

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			AddGameObject(newObject);
		}
		else if (iter->ID == 211008)		// 3칸짜리 폴링블록
		{
			Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

			newObject = MakeObject<FallingBlock>(objectPos, startPos, 3);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 211009)		// 1칸짜리 폴링블록
		{
			Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

			newObject = MakeObject<FallingBlock>(objectPos, startPos, 1);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 211010)		// 이미지는 없으나 콜라이더는 있음.
		{
			newObject = MakeObject<BlockBase>(objectPos);

			AddGameObject(newObject);
		}
		else if (iter->ID == 211011)		// 이미지는 있음, 콜라이더는 없음.
		{
			newObject = MakeObject<DecoObject>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 211012)		// 이미지는 있음, 콜라이더는 없음
		{
			newObject = MakeObject<DecoObject>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 211013)		// 플랫폼 폴링
		{
			Vector2D startPos = { TILE_WIDTH / 2 + (_xOriTile) * (TILE_WIDTH), TILE_HEIGHT / 2 + (_yOriTile) * (TILE_HEIGHT) };

			newObject = MakeObject<FallingBlock>(objectPos, startPos, 3);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 211014)		// 라이징 나초 타이니
		{
			newObject = MakeObject<RedUp>(objectPos, Vector2D::Up, 1300.f, TILE_HEIGHT * 7);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210115)		// 페이스 (온리 왼쪽)
		{
			newObject = MakeObject<FreeEnemy>(objectPos + 200.f * Vector2D::Up, "Face");

			AddGameObject(newObject);
		}
		else if (iter->ID == 210116)		// 퍼 (온리 왼쪽)
		{
			newObject = MakeObject<FreeEnemy>(objectPos + 200.f * Vector2D::Up, "Fur");

			AddGameObject(newObject);
		}
		else if (iter->ID == 210201)		// 인비지블 박스 4
		{
			newObject = MakeObject<TransBox>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(new Sprite(20104, Vector2D(0.5f, 0.5f), { 80.f, 77.f }, 0.f, Vector2D(560.f, 80.f)));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			newObject->GetSpriteRenderer()->SetOpacity(0.f);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210202)		// Red Right
		{
			newObject = MakeObject<RedRight>(objectPos, Vector2D::Right, 1300.f);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210203)		// 니들 업
		{
			newObject = MakeObject<Niddle>(objectPos + Vector2D(0.f, TILE_HEIGHT), CollisionDir::UP);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(4);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210204)		// 니들 레프트
		{
			newObject = MakeObject<Niddle>(objectPos + Vector2D(TILE_WIDTH, 0.f), CollisionDir::LEFT);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(4);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210205)		// 니들 라이트
		{
			newObject = MakeObject<Niddle>(objectPos - Vector2D(TILE_WIDTH, 0.f), CollisionDir::RIGHT);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(4);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210207)		// 레드 업
		{
			newObject = MakeObject<RedUp>(objectPos, Vector2D::Up, 1300.f);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(6);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210209)		// 슬로우 니들 다운
		{
			newObject = MakeObject<SlowNiddle>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetAABBCollision()->SetSize({ TILE_WIDTH, TILE_HEIGHT });

			newObject->GetSpriteRenderer()->SetSortOrder(6);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210210)		// slow niddle2x Up
		{
			newObject = MakeObject<SlowNiddle>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetAABBCollision()->SetSize({ TILE_WIDTH, 2 * TILE_HEIGHT });

			newObject->GetSpriteRenderer()->SetSortOrder(6);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210212)		// 화이트 다운
		{
			newObject = MakeObject<RedUp>(objectPos, Vector2D::Down, 1300.f);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(6);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210214)
		{
			newObject = MakeObject<DecoObject>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(3);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210215)
		{
			newObject = MakeObject<SlowNiddle>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetAABBCollision()->SetSize({ TILE_WIDTH, TILE_HEIGHT });

			newObject->GetSpriteRenderer()->SetSortOrder(6);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210220)	// 라이'딩' 나초
		{
			newObject = MakeObject<RidingNacho>(objectPos);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(6);

			AddGameObject(newObject);
		}
		else if (iter->ID == 210223)	// 도어
		{
		newObject = MakeObject<TriggerDoor>(objectPos);

		newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

		newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

		AddGameObject(newObject);
		}

		// Five Falling Object
		else if ((210301 <= iter->ID) && (iter->ID <= 210320))
		{
			float dropTime = iter->ID - 210301;

			D2D1_SIZE_F size = { iter->imageRect.right - iter->imageRect.left, iter->imageRect.bottom - iter->imageRect.top };

			newObject = MakeObject<FiveFalling>(objectPos, size, 4.f + dropTime * 2.f);

			newObject->GetSpriteRenderer()->SetSprite(MakeSprite(iter));

			newObject->GetSpriteRenderer()->SetSortOrder(iter->layer);

			AddGameObject(newObject);
		}



		// newObject->SetID(iter->ID);
	}

}

void Scene::AddGameObject(GameObject* object)
{
	Collision* collision = object->GetCollision();

	Renderer* renderer = object->GetRenderer();

	mGameObjects.push_back(object);

	if (collision != nullptr)
		mCollisions.push_back(collision);

	if (renderer != nullptr)
		mRenderers.insert(renderer);
}

void Scene::AddGlobalGameObject(GameObject* object)
{
	Collision* collision = object->GetCollision();

	Renderer* renderer = object->GetRenderer();

	mGlobalGameObjects.push_back(object);

	if (collision != nullptr)
		mCollisions.push_back(collision);

	if (renderer != nullptr)
		mRenderers.insert(renderer);
}

void Scene::SubGameObject(GameObject* object)
{
	Renderer* renderer = object->GetRenderer();

	Collision* collision = object->GetCollision();

	if (renderer != nullptr)
		for (auto iter = mRenderers.begin(); iter != mRenderers.end(); iter++)
		{
			if (*iter == renderer)
			{
				mRenderers.erase(iter);

				break;
			}
		}

	if (collision != nullptr)
		for (auto iter = mCollisions.begin(); iter != mCollisions.end(); iter++)
		{
			if (*iter == collision)
			{
				mCollisions.erase(iter);

				break;
			}
		}

	for (auto iter = mGameObjects.begin(); iter != mGameObjects.end(); iter++)
	{
		if (*iter == object)
		{
			object->Release();

			delete object;

			mGameObjects.erase(iter);

			break;
		}
	}
}

/// <summary>
/// 전역으로 사용할 오브젝트를 등록하여 관리하기
/// </summary>
void Scene::SubGlobalGameObject(GameObject* object)
{
	Renderer* renderer = object->GetRenderer();

	Collision* collision = object->GetCollision();

	if (renderer != nullptr)
		for (auto iter = mRenderers.begin(); iter != mRenderers.end(); iter++)
		{
			if (*iter == renderer)
			{
				mRenderers.erase(iter);

				break;
			}
		}

	if (collision != nullptr)
		for (auto iter = mCollisions.begin(); iter != mCollisions.end(); iter++)
		{
			if (*iter == collision)
			{
				mCollisions.erase(iter);

				break;
			}
		}

	for (auto iter = mGlobalGameObjects.begin(); iter != mGlobalGameObjects.end(); iter++)
	{
		if (*iter == object)
		{
			mGlobalGameObjects.erase(iter);

			break;
		}
	}
}

std::string Scene::GetSceneName()
{
	return mSceneName;
}

void Scene::ReserveCreate(GameObject* object, float time)
{
	mCreateReserveList.push_back({ object, time });
}

void Scene::ReserveDestroy(GameObject* object, float time)
{
	mDestroyReserveList.push_back({ object, time });
}

void Scene::BirthAndDeath()
{
	float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

	// Birth
	for (auto iter = mCreateReserveList.begin(); iter != mCreateReserveList.end(); )
	{
		(*iter).second -= delta;

		if ((*iter).second <= 0.f)
		{
			AddGameObject((*iter).first);

			iter = mCreateReserveList.erase(iter);
		}
		else
			++iter;
	}

	// Death
	for (auto iter = mDestroyReserveList.begin(); iter != mDestroyReserveList.end(); )
	{
		(*iter).second -= delta;

		// 렌더러, 콜리젼, 오브젝트 리스트에서 다 삭제해야함
		if ((*iter).second <= 0.f)
		{
			SubGameObject((*iter).first);

			iter = mDestroyReserveList.erase(iter);
		}
		else
			++iter;
	}
}