#include "PreCompiledHeader.h"
#include "Niddle.h"

#include "PlatformBase.h"
#include "Player.h"

Niddle::Niddle(CollisionDir dir):
mDetectWay(dir),
mIsDone(false)
{
	GetSpriteRenderer()->SetOpacity(0.f);
}

Niddle::~Niddle()
{
}

void Niddle::Update()
{
	BlockBase::Update();

	if ((!mIsDone) && (mDetectWay == GetCollisionDir()))
	{
		std::vector<GameObject*> info = GetCollision()->GetCollisionInfo();

		for (GameObject* object : info)
		{
			if (object->GetTag() == "Player")
			{
				Game::GetInstance().GetPlayer()->SetHp(0);

				Vector2D myPos = mTransform->GetPosition();

				if (mDetectWay == CollisionDir::LEFT)
				{
					mTransform->SetPosition(myPos + TILE_WIDTH * Vector2D::Left);

					GetSpriteRenderer()->SetOpacity(1.f);

					SetTag("End");
				}
				else if (mDetectWay == CollisionDir::UP)
				{
					mTransform->SetPosition(myPos + TILE_HEIGHT * Vector2D::Up);

					GetSpriteRenderer()->SetOpacity(1.f);

					SetTag("End");
				}
				else if (mDetectWay == CollisionDir::RIGHT)
				{
					mTransform->SetPosition(myPos + TILE_WIDTH * Vector2D::Right);

					GetSpriteRenderer()->SetOpacity(1.f);

					SetTag("End");
				}
				else if (mDetectWay == CollisionDir::DOWN)
				{
					mTransform->SetPosition(myPos + TILE_HEIGHT * Vector2D::Down);

					GetSpriteRenderer()->SetOpacity(1.f);

					SetTag("End");
				}

				mIsDone = true;
			}
		}
	}
}