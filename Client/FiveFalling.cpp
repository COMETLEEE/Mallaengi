#include "PreCompiledHeader.h"
#include "FiveFalling.h"

#include "Player.h"

FiveFalling::FiveFalling(D2D1_SIZE_F collisionSize, float dropTime):
	mDropTime(dropTime)
{
	AddSpriteRenderer();

	AddAABBCollision()->SetSize(collisionSize);
}

FiveFalling::~FiveFalling()
{

}

void FiveFalling::Update()
{
	GameObject::Update();

	float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

	mDropTime -= delta;

	if (mDropTime <= 0.f)
	{
		mTransform->SetPosition(mTransform->GetPosition() + delta * FALLING_SPEED * Vector2D::Down);

		std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

		for (GameObject* object : info)
		{
			if (object->GetTag() == "Player")
			{
				Game::GetInstance().GetPlayer()->SetHp(0);
			}
		}
	}
}