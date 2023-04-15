#include "PreCompiledHeader.h"
#include "BreakableBlock.h"


BlockFragment::BlockFragment(Vector2D pos)
	: mDuration(5000.0f)
	, mGravity(30.0f)
	, mEffectSpeed(500.0f)
{
	mTransform->SetPosition(pos);
}

BlockFragment::~BlockFragment()
{
}

void BlockFragment::Update()
{
	// 델타 타임을 가져와서 지속 시간을 줄인다.
	mDuration -= Timer::GetInstance().GetDeltaTime();

	// 파편 객체를 이동방향과 중력을 적용시켜서 이동시킨다.
	mTransform->SetPosition(mTransform->GetPosition() + Timer::GetInstance().GetDeltaTime() / 1000 * mEffectSpeed * mDirection);
	mTransform->SetPosition(mTransform->GetPosition() + Timer::GetInstance().GetDeltaTime() / 1000 * mGravity * Vector2D::Down);
	
	// 중력가속도를 적용한다.
	mGravity *= 1 + 8.8f * Timer::GetInstance().GetDeltaTime() / 1000;

	if (mDuration < 0.0f)
	{
		// 지속 시간이 끝나면 해제
		Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);
	}
}

void BlockFragment::SetDirection(Vector2D direction)
{
	mDirection = direction;
}

BreakableBlock::BreakableBlock()
{
	mSize = { TILE_WIDTH, TILE_HEIGHT };

	// 블록은 AABBCollision으로 작동한다.
	mAABBCollision = AddAABBCollision();

	AddSpriteRenderer();

	// 태그를 브레이커블 블록으로 설정한다.
	SetTag("BreakableBlock");
}

BreakableBlock::~BreakableBlock()
{

}

void BreakableBlock::FixedUpdate()
{
	BlockBase::FixedUpdate();
}

void BreakableBlock::Update()
{
	BlockBase::Update();
}

/// <summary>
/// 블록이 파괴될 때 호출되는 함수
/// 
/// 4방향으로 파편 나가는 이펙트 연출을 한다.
/// </summary>
void BreakableBlock::BreakBlock()
{
	BlockFragment* fragment[4];

	// 파편을 각각 현재 위치로부터 4방향의 대각선 방향으로 보낸다.
	// 그에 따라 알맞는 스프라이트 이미지를 잡아준다.
	for (int i = 0; i < 4; i++)
	{
		fragment[i] = new BlockFragment(this->GetTransform()->GetPosition());
		fragment[i]->AddSpriteRenderer()->SetSprite(new Sprite(*this->GetSpriteRenderer()->GetSprite()));
		fragment[i]->GetSpriteRenderer()->GetSprite()->mPosInSheet -= Vector2D(TILE_WIDTH * (2 - i % 2) + 1, 0);
		Game::GetInstance().GetCurrentScene()->AddGameObject(fragment[i]);
	}

	fragment[0]->SetDirection((Vector2D::Right + Vector2D::Up).Normalize());
	fragment[1]->SetDirection((Vector2D::Left + Vector2D::Up).Normalize());
	fragment[2]->SetDirection((Vector2D::Left + Vector2D::Down).Normalize());
	fragment[3]->SetDirection((Vector2D::Right + Vector2D::Down).Normalize());

	// 파편을 생성하고나면 원본 객체는 해제한다.
	Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);
	SoundManager::GetInstance()->Play(500030);
	
}