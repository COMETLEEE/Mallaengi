#include "PreCompiledHeader.h"
#include "BlockBase.h"
#include "Player.h"

BlockBase::BlockBase() :
	mSize({ TILE_WIDTH, TILE_HEIGHT })
{
	// 블록은 AABBCollision으로 작동한다.
	mAABBCollision = AddAABBCollision();

	AddSpriteRenderer();

	// 태그를 블록 베이스로 설정한다.
	SetTag("BlockBase");
}

BlockBase::~BlockBase()
{

}

void BlockBase::FixedUpdate()
{
	
}

void BlockBase::Update()
{
	GameObject::Update();
}