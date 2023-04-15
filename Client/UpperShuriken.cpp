#include "PreCompiledHeader.h"
#include "UpperShuriken.h"

#include "NachoShuriken.h"
#include "Player.h"

#define RISING_DELTA_X 10.f

UpperShuriken::UpperShuriken()
{
	mGamePlayer = Game::GetInstance().GetPlayer();
}

UpperShuriken::~UpperShuriken()
{
}

void UpperShuriken::Update()
{
	GameObject::Update();

	if (!mTrigger)
	{
		Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

		Vector2D myPos = mTransform->GetPosition();

		if ((abs(playerPos.mX - myPos.mX) <= TILE_WIDTH / 2 + RISING_DELTA_X) && (playerPos.mY <= myPos.mY))
		{
			mTrigger = true;

			NachoShuriken* shuriken = new NachoShuriken(Vector2D::Up);

			shuriken->GetTransform()->SetPosition(mTransform->GetPosition() + Vector2D(0, 400.f));

			Game::GetInstance().GetCurrentScene()->AddGameObject(shuriken);
		}
	}
}