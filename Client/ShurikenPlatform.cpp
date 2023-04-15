#include "PreCompiledHeader.h"
#include "ShurikenPlatform.h"

#include "NachoShuriken.h"

ShurikenPlatform::ShurikenPlatform():
BlockPlatform(),
mTrigger(false)
{

}

ShurikenPlatform::~ShurikenPlatform()
{
}

void ShurikenPlatform::Update()
{
	BlockPlatform::Update();

	if (!mTrigger)
	{
		std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

		for (GameObject* object : info)
		{
			if (object->GetTag() == "Player")
			{
				NachoShuriken* shuriken = new NachoShuriken(Vector2D(-1.f, 0.f));

				shuriken->GetTransform()->SetPosition(mTransform->GetPosition() + Vector2D(2000.f, -TILE_WIDTH));

				Game::GetInstance().GetCurrentScene()->AddGameObject(shuriken);

				mTrigger = true;
			}
		}
	}
}