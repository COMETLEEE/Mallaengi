#include "PreCompiledHeader.h"
#include "DumbellDown.h"

#include "Player.h"
#include "FallingDum.h"

DumbellDown::DumbellDown(std::string type):
mTrigger(false),
mReserve(nullptr),
mGamePlayer(Game::GetInstance().GetPlayer())
{
	if (type == "NiddleDown")
	{
		mReserve = new FallingDum("NiddleDown", -1);
	}
	else if (type == "Down")
	{
		mReserve = new FallingDum("Down", -1);
	}
}

DumbellDown::~DumbellDown()
{
}

void DumbellDown::Update()
{
	GameObject::Update();

	if (mTrigger)
		Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);

	if (!mTrigger)
	{
		Vector2D myPos = mTransform->GetPosition();

		Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

		if (abs(myPos.mX - playerPos.mX) <= TILE_WIDTH / 2 + PLAYER_SCALE * PLAYER_WIDTH / 2 + 30.f)
		{
			mReserve->GetTransform()->SetPosition(mTransform->GetPosition() + Vector2D(200.f, -200.f));

			Game::GetInstance().GetCurrentScene()->AddGameObject(mReserve);

			mReserve = nullptr;

			mTrigger = true;
		}
	}
}

void DumbellDown::Release()
{
	if (mReserve != nullptr)
		delete mReserve;
}