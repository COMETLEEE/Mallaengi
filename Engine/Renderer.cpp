#include "pch.h"
#include "Renderer.h"

Renderer::Renderer(GameObject* object):
	mGameObject(object),
	// 1 : 플레이어 / 2 : 몬스터 / 3: 아이템 / 4 : 블럭, 플랫폼 / 5 ~ : 배경 및 기타 ..?
	mSortOrder(4) // 따로 1, 2, 3 / 5, 6, 7 .. 로 셋팅해주는 경우가 아니라면 4으로 밀어넣습니다.
{

}

Renderer::~Renderer()
{

}

void Renderer::Render()
{
	Graphics::GetInstance().SetTransform(mGameObject->GetTransform()->GetWorldTransformMatrix());

	D2D1_SIZE_F size = { 100.f, 100.f };

	Graphics::GetInstance().DrawRectangle(Vector2D::Zero, size, D2D1::ColorF(1.f, 0.f, 0.f, 1));
}