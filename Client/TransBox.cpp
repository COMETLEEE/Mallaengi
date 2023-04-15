#include "PreCompiledHeader.h"
#include "TransBox.h"

TransBox::TransBox()
{
	// 태그를 TransBox 으로 설정한다.
	SetTag("TransBox");
}

TransBox::~TransBox()
{
	
}

void TransBox::TriggerEvent()
{
	GetSpriteRenderer()->SetOpacity(1.f);

	SoundManager::GetInstance()->Play(500031);

	SetTag("BoxBase");
}