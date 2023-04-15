#include "PreCompiledHeader.h"
#include "TrapTile.h"

#include "Platform.h"
#include "Player.h"

TrapTile::TrapTile():
	BlockBase(),
	mTrigger(false)
{

}

TrapTile::~TrapTile()
{

}

void TrapTile::Update()
{
	BlockBase::Update();

	if (mTrigger)
		return;

	std::vector<GameObject*> info = mCollision->GetCollisionInfo();

	for (GameObject* object : info)
	{
		if ((object->GetTag() == "Player") && (mCollisionDir == CollisionDir::DOWN))
		{
			mTransform->SetPosition(mTransform->GetPosition() + TILE_HEIGHT * Vector2D::Down);

			mTrigger = true;

			Game::GetInstance().GetPlayer()->SetHp(0);
		}
		else if ((object->GetTag() == "Player") && (mCollisionDir == CollisionDir::UP))
		{
			mTransform->SetPosition(mTransform->GetPosition() + TILE_HEIGHT * Vector2D::Up);

			mTrigger = true;

			Game::GetInstance().GetPlayer()->SetHp(0);
		}
	}
}