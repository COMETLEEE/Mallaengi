#include "PreCompiledHeader.h"
#include "NachoShuriken.h"

#define SHURIKEN_SPEED 2600.f

NachoShuriken::NachoShuriken(Vector2D dir) :
	mDirrection(dir)
{
	AddAABBCollision();

	AddSpriteRenderer();

	mAnimation = Game::GetInstance().GetResource()->GetAnimationClip("NACHO_SHURIKEN");

	AddAnimator()->SetAnimationClip(mAnimation);
}

NachoShuriken::~NachoShuriken()
{
}

void NachoShuriken::Update()
{
	GameObject::Update();

	// 나초 수리검은 설정된 방향으로 날아간다.
	mTransform->SetPosition(mTransform->GetPosition() + Timer::GetInstance().GetDeltaTime() / 1000.f * SHURIKEN_SPEED * mDirrection);

	std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

	for (GameObject* object : info)
	{
		if (object->GetTag() == "Player")
			Game::GetInstance().GetPlayer()->SetHp(0);
	}
}