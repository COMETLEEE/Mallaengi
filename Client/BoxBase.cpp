#include "PreCompiledHeader.h"
#include "BoxBase.h"

BoxBase::BoxBase():
mSize({TILE_WIDTH, TILE_HEIGHT}),
mTrigger(false),
mIsFirstLoop(true)
{
	SetTag("BoxBase");

	AddAABBCollision();

	AddSpriteRenderer()->SetSortOrder(6);
}

BoxBase::~BoxBase()
{
}

void BoxBase::Update()
{
	GameObject::Update();

	if ((mIsFirstLoop) && (mTrigger))
	{
		TriggerEvent();

		mIsFirstLoop = false;
	}
}

void BoxBase::TriggerEvent()
{
}