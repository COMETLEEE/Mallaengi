#include "PreCompiledHeader.h"
#include "FallingEnemy.h"

#include "FreeEnemy.h"

FallingEnemy::FallingEnemy():
BlockPlatform(),
mTrigger(false)
{

}

FallingEnemy::~FallingEnemy()
{
}

void FallingEnemy::Update()
{
	BlockPlatform::Update();

	std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

	if (!mTrigger)
	{
		for (GameObject* object : info)
		{
			if ((object->GetTag() == "Player") && (mCollisionDir == CollisionDir::UP))
			{
				FreeEnemy* free = new FreeEnemy("Hamburger", -1);

				free->GetTransform()->SetPosition(mTransform->GetPosition() + 1200.f * Vector2D::Up);

				free->SetVelocity(Vector2D(0.f, 200.f));

				Game::GetInstance().GetCurrentScene()->AddGameObject(free);

				mTrigger = true;
			}
		}
	}
}