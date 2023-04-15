#include "PreCompiledHeader.h"
#include "RisingTrap.h"

#include "Player.h"

#define RISING_DELTA_X 10.f
#define RISING_SPEED_PER_SEC 2700.f

RisingTrap::RisingTrap():
mTrigger(false)
{
	mGamePlayer = Game::GetInstance().GetPlayer();

	AddAABBCollision();

	AddSpriteRenderer();
}

RisingTrap::~RisingTrap()
{
}

void RisingTrap::Update()
{
	GameObject::Update();

	Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

	Vector2D myPos = mTransform->GetPosition();

	if ((abs(playerPos.mX - myPos.mX) <= TILE_WIDTH / 2 + RISING_DELTA_X) && (playerPos.mY < myPos.mY))
		mTrigger = true;

	if (mTrigger)
	{
		static float timer = 0.f;

		float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

		timer += delta;

		// ³Ê¹« ÂªÀº ¼ø°£¿¡ µô¸®Æ®ÇÏ¸é ´ÙÀ½ ¶óÀÌÂ¡ ³ªÃÊ¶û °ãÄ¥ ¼ö ÀÖ´Ù ..
		if (timer >= 20.f)
		{
			Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);

			timer = 0;
		}

		mTransform->SetPosition(myPos + delta * RISING_SPEED_PER_SEC * Vector2D::Up);

		std::vector<GameObject*> collisionInfo = GetCollision()->GetCollisionInfo();

		for (GameObject* object : collisionInfo)
		{
			if (object->GetTag() == "Player")
			{
				// Áê±ä´Ù.
				mGamePlayer->SetHp(0);
			}
		}
	}
}