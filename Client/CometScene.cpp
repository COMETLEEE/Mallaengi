#include "PreCompiledHeader.h"
#include "CometScene.h"

#include "Player.h"
#include "StageOneBackGround.h"
#include "BreakableBlock.h"
#include "CheckPoint.h"
#include "MainCamera.h"

#include "Platform.h"
#include "DecoObject.h"

#include "JsonManager.h"
#include "TriggerTrap.h"

// CometScene의 Size
#define COMET_SCENE_WIDTH 3840
#define COMET_SCENE_HEIGHT 2160

CometScene::CometScene() :
	Scene("CometScene")
{

}

CometScene::~CometScene()
{

}

void CometScene::BuildScene()
{
	Scene::BuildScene();

	// 이 씬은 플레이어가 필요합니다.
	AddGameObject(mGamePlayer);

	// 이 씬은 Play가 이루어지는 씬이므로 메인 카메라를 사용합니다.
	AddGameObject(new MainCamera());

	GameObject* background = new StageOneBackGround();

	SpriteRenderer* sprite = dynamic_cast<SpriteRenderer*>(background->GetRenderer());

	sprite->SetSprite(Game::GetInstance().GetResource()->GetSprite("STAGE_1_BACKGROUND"));

	sprite->SetSortOrder(10);

	AddGameObject(background);

	// 맵툴 데이터 읽어오고 배치하기.
	MapJson cometSceneJson;

	cometSceneJson.DeserializeFromFile("Json\\CometScene.json");

	for (auto iter = cometSceneJson.mTileList.begin(); iter != cometSceneJson.mTileList.end(); iter++)
	{
		// 1. 몇 번째 타일에 이것이 들어왔는지 체크합니다.
		int _yTile = iter->index >> 16;
		int _xTile = iter->index & 0xffff;

		// 2. ID 별로 분류하여 조건에 맞는 오브젝트를 정확한 위치에 비치합니다.
		if (iter->ID == 102004) // Block
		{
			BreakableBlock* block = new BreakableBlock();

			block->GetTransform()->SetPosition(Vector2D(TILE_WIDTH / 2 + _xTile * TILE_WIDTH, TILE_HEIGHT / 2 + _yTile * TILE_HEIGHT));

			D2D1_RECT_F rect = iter->imageRect;

			Sprite* sprite = new Sprite(iter->imageID, Vector2D(0.5f, 0.5f),
				{ rect.right - rect.left, rect.bottom - rect.top }, 0.f, Vector2D(rect.left, rect.top));

			block->GetSpriteRenderer()->SetSprite(sprite);

			AddGameObject(block);
		}
		// 타일 (잔디가 있는, 올라갈 수 있는 것이다)
		else if ((iter->ID == 10101001) || (iter->ID == 10101002) || (iter->ID == 10101003))
		{
			Platform* platform = new Platform();

			platform->GetTransform()->SetPosition(Vector2D(TILE_WIDTH / 2 + _xTile * TILE_WIDTH, TILE_HEIGHT / 2 + _yTile * TILE_HEIGHT));

			D2D1_RECT_F rect = iter->imageRect;

			Sprite* sprite = new Sprite(iter->imageID, Vector2D(0.5f, 0.5f),
				{ rect.right - rect.left, rect.bottom - rect.top }, 0.f, Vector2D(rect.left, rect.top));

			platform->GetSpriteRenderer()->SetSprite(sprite);

			AddGameObject(platform);
		}
		// 타일 (잔디가 없는, 올라갈 수 없는 것이다)
		else if ((iter->ID == 10101004) || (iter->ID == 10101005) || (iter->ID == 10101006)
			|| (iter->ID == 10101007) || (iter->ID == 10101008) || (iter->ID == 10101009))
		{
			DecoObject* deco = new DecoObject();

			deco->GetTransform()->SetPosition(Vector2D(TILE_WIDTH / 2 + _xTile * TILE_WIDTH, TILE_HEIGHT / 2 + _yTile * TILE_HEIGHT));

			D2D1_RECT_F rect = iter->imageRect;

			Sprite* sprite = new Sprite(iter->imageID, Vector2D(0.5f, 0.5f),
				{ rect.right - rect.left, rect.bottom - rect.top }, 0.f, Vector2D(rect.left, rect.top));

			deco->GetSpriteRenderer()->SetSprite(sprite);

			AddGameObject(deco);
		}
		// 체크 포인트 (일단 데코로 해둡니다)
		else if (iter->ID == 103001)
		{
			CheckPoint* deco = new CheckPoint();

			deco->GetTransform()->SetPosition(Vector2D(TILE_WIDTH / 2 + _xTile * TILE_WIDTH, TILE_HEIGHT / 2 + _yTile * TILE_HEIGHT));

			D2D1_RECT_F rect = iter->imageRect;

			Sprite* sprite = new Sprite(iter->imageID, Vector2D(0.5f, 0.5f),
				{ rect.right - rect.left, rect.bottom - rect.top }, 0.f, Vector2D(rect.left, rect.top));

			deco->GetSpriteRenderer()->SetSprite(sprite);

			AddGameObject(deco);
		}
		// 사과나무 (일단 데코로 해둡니다)
		else if (iter->ID == 107002)
		{
			// 사과 나무는 가로로 3칸, 밑으로 5칸
			DecoObject* deco = new DecoObject();

			// 사과 나무 아래가 플랫하지 않아서 10 정도 더 내려줌
			deco->GetTransform()->SetPosition(Vector2D(TILE_WIDTH / 2 + (_xTile + 1) * TILE_WIDTH, TILE_HEIGHT / 2 + (_yTile + 2) * TILE_HEIGHT + 10.f));

			D2D1_RECT_F rect = iter->imageRect;

			Sprite* sprite = new Sprite(iter->imageID, Vector2D(0.5f, 0.5f),
				{ rect.right - rect.left, rect.bottom - rect.top }, 0.f, Vector2D(rect.left, rect.top));

			deco->GetSpriteRenderer()->SetSprite(sprite);

			AddGameObject(deco);
		}
		// 가판대
		else if (iter->ID == 105001)
		{
			DecoObject* deco = new DecoObject();

			deco->GetTransform()->SetPosition(Vector2D(TILE_WIDTH / 2 + (_xTile + 1) * TILE_WIDTH, TILE_HEIGHT + (_yTile + 1) * TILE_HEIGHT));

			D2D1_RECT_F rect = iter->imageRect;

			Sprite* sprite = new Sprite(iter->imageID, Vector2D(0.5f, 0.5f),
				{ rect.right - rect.left, rect.bottom - rect.top }, 0.f, Vector2D(rect.left, rect.top));

			deco->GetSpriteRenderer()->SetSprite(sprite);

			AddGameObject(deco);
		}
		// Item-Box (일단 브레이커블 블락으로 .. 클래스를 오브젝트별로 다 파야겠다 ..)
		else if (iter->ID == 102001)
		{
			BreakableBlock* block = new BreakableBlock();

			block->GetTransform()->SetPosition(Vector2D(TILE_WIDTH / 2 + _xTile * TILE_WIDTH, TILE_HEIGHT / 2 + _yTile * TILE_HEIGHT));

			D2D1_RECT_F rect = iter->imageRect;

			Sprite* sprite = new Sprite(iter->imageID, Vector2D(0.5f, 0.5f),
				{ rect.right - rect.left, rect.bottom - rect.top }, 0.f, Vector2D(rect.left, rect.top));

			block->GetSpriteRenderer()->SetSprite(sprite);

			AddGameObject(block);
		}
		// Bush
		else if (iter->ID == 107001)
		{
			DecoObject* deco = new DecoObject();

			deco->GetTransform()->SetPosition(Vector2D(TILE_WIDTH + (_xTile) * TILE_WIDTH, TILE_HEIGHT + (_yTile) * TILE_HEIGHT));

			D2D1_RECT_F rect = iter->imageRect;

			Sprite* sprite = new Sprite(iter->imageID, Vector2D(0.5f, 0.5f),
				{ rect.right - rect.left, rect.bottom - rect.top }, 0.f, Vector2D(rect.left, rect.top));

			deco->GetSpriteRenderer()->SetSprite(sprite);

			AddGameObject(deco);
		}
		// Donut
		else if (iter->ID == 104001)
		{
			DecoObject* deco = new DecoObject();

			deco->GetTransform()->SetPosition(Vector2D(TILE_WIDTH / 2 + (_xTile)*TILE_WIDTH, TILE_HEIGHT / 2 + (_yTile)*TILE_HEIGHT));

			D2D1_RECT_F rect = iter->imageRect;

			Sprite* sprite = new Sprite(iter->imageID, Vector2D(0.5f, 0.5f),
				{ rect.right - rect.left, rect.bottom - rect.top }, 0.f, Vector2D(rect.left, rect.top));

			deco->GetSpriteRenderer()->SetSprite(sprite);

			AddGameObject(deco);
		}
	}

	// 스테이지 시작 위치로 플레이어 세팅
	mGamePlayer->GetTransform()->SetPosition(Vector2D(0.f, 1400.f));

	TriggerTrap* trigger = new TriggerTrap();

	trigger->GetTransform()->SetPosition(Vector2D(200.f, 1700.f));

	AddGameObject(trigger);
}