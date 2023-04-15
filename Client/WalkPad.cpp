#include "PreCompiledHeader.h"
#include "WalkPad.h"

#include "Player.h"

bool WalkPad::mPlayerChecked = false;
bool WalkPad::mMonsterChecked = false;

WalkPad::WalkPad(Vector2D dir):
mDirrection(dir)
{
	SetTag("BlockBase");

	AddSpriteRenderer();

	AddAABBCollision();

	mGamePlayer = Game::GetInstance().GetPlayer();
}

WalkPad::~WalkPad()
{
}

void WalkPad::FixedUpdate()
{
	mPlayerChecked = false;

	mMonsterChecked = false;
}

#include <iostream>

using namespace std;

void WalkPad::Update()
{
	GameObject::Update();

	std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

	float delta = Timer::GetInstance().GetDeltaTime() / 1000.0f;

	for (GameObject* object : info)
	{
		if (object->GetTag() == "Enemy")
		{
			object->GetTransform()->SetPosition(object->GetTransform()->GetPosition() + delta * WALKPAD_SPEED_PER_SEC * mDirrection);
		}
	}

	if (!mPlayerChecked)
	{
		for (GameObject* object : info)
		{
			if (object->GetTag() == "Player")
			{
				mGamePlayer->GetTransform()->SetPosition(mGamePlayer->GetTransform()->GetPosition() + delta * WALKPAD_SPEED_PER_SEC * mDirrection);

				mPlayerChecked = true;

				return;
			}
		}
	}
}