#include "pch.h"
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(GameObject* gameObject)
	: Renderer(gameObject),										// 부모 클래스의 생성자 지정 호출
	mOpacity(1.f),
	mSprite(nullptr)
{

}

SpriteRenderer::~SpriteRenderer()
{
	//if (mSprite != nullptr)
	//	delete mSprite;
}

void SpriteRenderer::SetSprite(Sprite* sprite)
{
	//if (mSprite != nullptr && mSprite->mSpriteSheetIndex > 10000)
	//{
	//	delete mSprite;
	//}

	mSprite = sprite;
}

void SpriteRenderer::Render()
{
	if (mSprite == nullptr)
		return;

	// Tag가 UI이면 트랜스폼 자기꺼로 (화면 상에 배치되어 있는 것으로) 하면 됨
	if (mGameObject->GetTag() == "UI")
		Graphics::GetInstance().SetTransformForUI(mGameObject->GetTransform()->GetWorldTransformMatrix());
	else
		// 출력하고 싶은 스프라이트의 출력 위치를 설정한다
		Graphics::GetInstance().SetTransform(mGameObject->GetTransform()->GetWorldTransformMatrix());

	// 지금 선택된 스프라이트를 출력한다
	Graphics::GetInstance().DrawSprite(mSprite, Vector2D::Zero, mOpacity);
}

void SpriteRenderer::Release()
{
	if (mSprite != nullptr && mSprite->mSpriteSheetIndex > 10000)
		delete mSprite;
}