#include "PreCompiledHeader.h"
#include "Watch.h"

#include "Player.h"

Watch::Watch():
mGamePlayer(Game::GetInstance().GetPlayer()),
mNumbers(std::vector<GameObject*>(5))
{
	D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

	for (int i = 0 ; i < 5 ; i++)
	{
		mNumbers[i] = new GameObject();

		mNumbers[i]->SetTag("UI");

		mNumbers[i]->AddSpriteRenderer()->SetSortOrder(1);

		mNumbers[i]->GetTransform()->SetPosition(Vector2D(size.width - 35.f * (5 - i), 108.f));

		Game::GetInstance().GetCurrentScene()->AddGameObject(mNumbers[i]);
	}

	// WATCH_TIME_ONE
	mNumbers[2]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_COLON"));
}

Watch::~Watch()
{
}

void Watch::LateUpdate()
{
	GameObject::LateUpdate();

	float playtime = mGamePlayer->GetStagePlayTime();

	int minute = static_cast<int>(playtime / 60.f);

	int second = static_cast<int>(playtime - minute * 60.f);

	std::string min = std::to_string(minute);

	std::string sec = std::to_string(second);

	if (min.length() == 1)
		min = "0" + min;

	if (sec.length() == 1)
		sec = "0" + sec;

	for (int i = 0 ; i < 5 ; i++)
	{
		if (i == 2)		// COLON
			continue;

		if (i < 2)
		{
			if (min[i] == '0')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_ZERO"));
			else if (min[i] == '1')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_ONE"));
			else if (min[i] == '2')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_TWO"));
			else if (min[i] == '3')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_THREE"));
			else if (min[i] == '4')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_FOUR"));
			else if (min[i] == '5')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_FIVE"));
			else if (min[i] == '6')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_SIX"));
			else if (min[i] == '7')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_SEVEN"));
			else if (min[i] == '8')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_EIGHT"));
			else if (min[i] == '9')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_NINE"));
		}
		else if (i >= 3)
		{
			if (sec[i - 3] == '0')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_ZERO"));
			else if (sec[i - 3] == '1')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_ONE"));
			else if (sec[i - 3] == '2')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_TWO"));
			else if (sec[i - 3] == '3')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_THREE"));
			else if (sec[i - 3] == '4')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_FOUR"));
			else if (sec[i - 3] == '5')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_FIVE"));
			else if (sec[i - 3] == '6')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_SIX"));
			else if (sec[i - 3] == '7')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_SEVEN"));
			else if (sec[i - 3] == '8')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_EIGHT"));
			else if (sec[i - 3] == '9')
				mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("WATCH_TIME_NINE"));
		}
	}
}