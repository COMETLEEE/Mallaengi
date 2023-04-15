#include "PreCompiledHeader.h"
#include "PlatformBase.h"

PlatformBase::PlatformBase():
	mSize({ TILE_WIDTH + 1, TILE_HEIGHT}),
	mCollisionDir(CollisionDir::NONE)
{
	// 플랫폼은 AABBCollision으로 작동한다.
	mAABBCollision = AddAABBCollision();

	AddSpriteRenderer();

	// 태그를 플랫폼 베이스으로 설정한다.
	SetTag("PlatformBase");
}

PlatformBase::~PlatformBase()
{

}

void PlatformBase::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void PlatformBase::Update()
{
	GameObject::Update();
}