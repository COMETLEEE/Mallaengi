#include "PreCompiledHeader.h"
#include "CatBoxTrap.h"

#include "Player.h"

CatBoxTrap::CatBoxTrap():
mTimer(0.f)
{
	mTransform->SetScale(Vector2D(2.0f, 2.0f));

	AddSpriteRenderer()->SetSortOrder(4);

	AddAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("TRAP_CAT"));
}

CatBoxTrap::~CatBoxTrap()
{
}

void CatBoxTrap::Update()
{
	GameObject::Update();

	mTimer += Timer::GetInstance().GetDeltaTime() / 1000.f;

	if (mTimer >= 0.5f)
	{
		// ÇÊÅ³ ^^ ..
		Game::GetInstance().GetPlayer()->SetHp(0);
	}
}