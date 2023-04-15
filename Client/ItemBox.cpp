#include "PreCompiledHeader.h"
#include "ItemBox.h"

ItemBox::ItemBox(GameObject* reserveObject, int stage) :
	mStage(stage),
	mReserveObject(nullptr)
{
	SetTag("ItemBox");

	mReserveObject = reserveObject;
}

ItemBox::~ItemBox()
{
}

void ItemBox::TriggerEvent()
{
	if (mReserveObject != nullptr)
	{
		Game::GetInstance().GetCurrentScene()->AddGameObject(mReserveObject);
		mReserveObject->GetTransform()->SetPosition(mTransform->GetPosition());

		mReserveObject = nullptr;
	}

	// 사용된 아이템 박스로 변경
	if (mStage == 1)
	{
		delete GetSpriteRenderer()->GetSprite();
		GetSpriteRenderer()->SetSprite(new Sprite(20104, Vector2D(0.5f, 0.5f), { TILE_WIDTH, TILE_HEIGHT }, 0.f, Vector2D(240.f, 83.f)));
	}
	else if (mStage == 2)
	{
		delete GetSpriteRenderer()->GetSprite();
		GetSpriteRenderer()->SetSprite(new Sprite(20104, Vector2D(0.5f, 0.5f), { TILE_WIDTH, TILE_HEIGHT }, 0.f, Vector2D(400.f, 83.f)));
	}

	SoundManager::GetInstance()->Play(500031);
	SetTag("BoxBase");
}

void ItemBox::Release()
{
	if (mReserveObject != nullptr)
	{
		mReserveObject->Release();
		delete mReserveObject;
	}
}