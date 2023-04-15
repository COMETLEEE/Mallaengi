#include "PreCompiledHeader.h"
#include "BodyScale.h"

#include "Player.h"
#include "UIDecoObject.h"

BodyScale::BodyScale():
mGamePlayer(Game::GetInstance().GetPlayer()),
mNumbers(std::vector<GameObject*>())
{
	D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

	for (int i = 0; i < 3; i++)
	{
		GameObject* number = new UIDecoObject();

		number->GetTransform()->SetPosition(Vector2D(size.width / 2 - 40.f + 40.f * i, 100.f));

		number->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_ZERO"));

		number->GetSpriteRenderer()->SetSortOrder(2);

		Game::GetInstance().GetCurrentScene()->AddGameObject(number);

		mNumbers.push_back(number);
	}

	SetTag("UI");

	mTransform->SetPosition(Vector2D(size.width / 2, 100.f));

	AddSpriteRenderer()->SetSortOrder(3);

	GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("UI_BODYSCALE"));
}

BodyScale::~BodyScale()
{
}

void BodyScale::LateUpdate()
{
	GameObject::LateUpdate();

	std::string bodyWeight = std::to_string(static_cast<int>(mGamePlayer->GetBodyWeight()));

	std::string zero = "";

	for (int i = 0 ; i < 3 - bodyWeight.length() ; i++)
		zero += '0';

	bodyWeight = zero + bodyWeight;

	// 리플렉션 마렵다
	for (int i = 0 ; i < 3 ; i++)
	{
		if (bodyWeight[i] == '0')
			mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_ZERO"));
		else if (bodyWeight[i] == '1')
			mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_ONE"));
		else if (bodyWeight[i] == '2')
			mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_TWO"));
		else if (bodyWeight[i] == '3')
			mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_THREE"));
		else if (bodyWeight[i] == '4')
			mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_FOUR"));
		else if (bodyWeight[i] == '5')
			mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_FIVE"));
		else if (bodyWeight[i] == '6')
			mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_SIX"));
		else if (bodyWeight[i] == '7')
			mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_SEVEN"));
		else if (bodyWeight[i] == '8')
			mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_EIGHT"));
		else if (bodyWeight[i] == '9')
			mNumbers[i]->GetSpriteRenderer()->SetSprite(Game::GetInstance().GetResource()->GetSprite("SCALE_NUMBERS_NINE"));
	}
}