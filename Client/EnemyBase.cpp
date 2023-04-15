#include "PreCompiledHeader.h"
#include "Player.h"


//Blocks
#include "BlockBase.h"
#include "BreakableBlock.h"
#include "TransBox.h"

// Platforms
#include "Platform.h"
#include "BlockPlatform.h"

// Enemy
#include "EnemyBase.h"

#include "ItemBox.h"

EnemyBase::EnemyBase() :
	mDirVector(Vector2D::Zero),
	mBeforePosition(Vector2D::Zero),
	mCurrentState(EnemyState::Idle),
	mPrevState(EnemyState::Idle),
	mHp(1),
	mVelocity(Vector2D::Zero),
	mGravity(GRAVITY),
	mAnimationClips(std::vector<AnimationClip*>())
{
	// 제일 중요한 태그 설정
	SetTag("Enemy");

	// 생성될 때 이 오브젝트의 필요한 컴포넌트의 준비를 모두 해주어야 합니다.
	AddSpriteRenderer()->SetSortOrder(4); // 아이템이 1이 될 예정 !

	// 이거는 다음에 Sprite Tool의 피격 범위로 만들 예정입니다.
	AddAABBCollision()->SetSize({ ENEMY_WIDTH, ENEMY_HEIGHT });

	Animator* animator = AddAnimator();

	GetTransform()->SetScale(Vector2D(ENEMY_SCALE, ENEMY_SCALE));
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Idle()
{
}

void EnemyBase::Run()
{
}

void EnemyBase::Attack()
{
}

void EnemyBase::Jump()
{
}

void EnemyBase::Die()
{
	
}

void EnemyBase::LoadAnimationProcess()
{
	// 오버라이드해서 각각의 적에게 맞는 애니메이션을 가져오자.
}

void EnemyBase::StateChangeProcess()
{
	if (mPrevState != mCurrentState)
		GetAnimator()->SetAnimationClip(mAnimationClips[static_cast<int>(mCurrentState)]);
}

void EnemyBase::FixedUpdate()
{
	GameObject::FixedUpdate();

	// 0. 업데이트 전 현재 위치를 기억해둡니다.
	mBeforePosition = mTransform->GetPosition();

	// 1-1. 중력 처리 (최대 떨어지는 속도를 컨트롤합니다.)
	if (mVelocity.mY <= MAX_FALLING_SPEED)
	{
		mVelocity.mY = mVelocity.mY + GRAVITY * Timer::GetInstance().GetDeltaTime() / 1000.f;
	}

	// 1. Update 전, PrevState와 PrevStep의 교체를 실시합니다.
	mPrevState = mCurrentState;
	
	// Enemy State에 따른 분류
	switch (mCurrentState)
	{
		case EnemyState::Idle:
		{
			Idle();
			break;
		}

		case EnemyState::Run:
		{
			Run();
			break;
		}

		case EnemyState::Attack:
		{
			Attack();
			break;
		}

		case EnemyState::Jump:
		{
			Jump();
			break;
		}

		case EnemyState::Die:
		{
			Die();
			break;
		}

		default:
			break;
	}

	mTransform->SetPosition(mTransform->GetPosition() + (Timer::GetInstance().GetDeltaTime() / 1000.f) * mVelocity);

	mVelocity.mX = 0.f;

	mIsJumpable = false;
}

void EnemyBase::Update()
{
	GameObject::Update();

	// 1. 이번 프레임에서의 충돌을 확인함
	// 플랫포머 관련 로직을 수행한다. 각 오브젝트 별로 조건이 다름 ..!
	std::vector<GameObject*> collisionInfo = mCollision->GetCollisionInfo();

	for (GameObject* object : collisionInfo)
	{
		// BreakableBlock과 충돌한 경우
		if (object->GetTag() == "BreakableBlock")
		{
			BreakableBlock* breakableBlock = dynamic_cast<BreakableBlock*>(object);

			BreakableBlockCollisionProcess(breakableBlock);
		}
		else if (object->GetTag() == "BlockBase")
		{
			BlockBase* block = dynamic_cast<BlockBase*>(object);

			BlockCollisionProcess(block);
		}

		// Platform
		else if (object->GetTag() == "Platform")
		{
			Platform* platform = dynamic_cast<Platform*>(object);

			PlatformCollisionProcess(platform);
		}
		else if (object->GetTag() == "BlockPlatform")
		{
			BlockPlatform* platform = dynamic_cast<BlockPlatform*>(object);

			BlockPlatformCollisionProcess(platform);
		}

		// Box
		else if (object->GetTag() == "BoxBase")
		{
			BoxBase* box = dynamic_cast<BoxBase*>(object);

			BoxCollisionProcess(box);
		}
		// TransBox과 충돌한 경우
		else if (object->GetTag() == "TransBox")
		{
			TransBox* transBox = dynamic_cast<TransBox*>(object);

			TransBoxCollisionProcess(transBox);
		}
		// ItemBox
		else if (object->GetTag() == "ItemBox")
		{
			ItemBox* itemBox = dynamic_cast<ItemBox*>(object);

			ItemBoxCollisionProcess(itemBox);
		}
	}

	if (mHp <= 0)
		mCurrentState = EnemyState::Die;

	StateChangeProcess();
}


void EnemyBase::BlockCollisionProcess(BlockBase* block)
{
	if (block != nullptr)
	{
		Transform* blockBaseTransform = block->GetTransform();
		// 블럭의 위치
		Vector2D blockBasePos = blockBaseTransform->GetPosition();
		// 블럭의 사이즈
		D2D1_SIZE_F blockBaseSize = block->GetSize();
		// Player의 사이즈
		D2D1_SIZE_F playerSize = dynamic_cast<AABBCollision*>(this->mCollision)->GetSize();

		// -- 어느 방향에서 플레이어와 충돌했는가 + 어떠한 조건의 충돌인지 검사한다.
		float vertTovertTangent = ((blockBaseSize.height / 2) + (playerSize.height * PLAYER_SCALE / 2)) / ((blockBaseSize.width / 2) + (playerSize.width * PLAYER_SCALE / 2));

		Vector2D centerTocenter = this->mTransform->GetPosition() - blockBasePos;

		float curTangent = centerTocenter.mY / centerTocenter.mX;

		Vector2D velo = this->GetVelocity();

		// 플레이어는 블럭의 윗면에 있다.
		// 여기서 더 고려해야할 것이 있다면, 플레이어가 상승 중에는 위치 고정 X ..!
		// 만약, 좌측 면에서 점프 시 .. 어중간하게 강할 때 문제가 될 수 있다.
		if ((centerTocenter.mY < -(TILE_HEIGHT / 2) - (PLAYER_HEIGHT * PLAYER_SCALE / 2) + ADJUST_Y) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 추락 중 또는 플랫폼 위에 있다.
			if (mDirVector.mY >= 0.f)
			{
				// 플레이어가 밟고 있는 밑면이 하나라도 있다는 것이므로 점프 가능하게 바꿔줍니다.
				mIsJumpable = true;

				velo.mY = 0.f;

				// 플레이어 캐릭터의 위치를 블럭의 상단으로 고정해준다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + 0.005 - (blockBaseSize.height / 2) - (playerSize.height * PLAYER_SCALE / 2)));
			}
		}
		// 플레이어는 블럭의 밑면에 있다.
		else if ((centerTocenter.mY >= 0) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 상승 중 플랫폼의 밑면에서 충돌하였다면.
			if (mDirVector.mY < 0.f)
			{
				velo.mY = 0.f;

				// 플레이어 캐릭터의 위치를 블럭의 하단으로 고정해준다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + (blockBaseSize.height / 2) + (playerSize.height * PLAYER_SCALE / 2)));
			}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX >= 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 우측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX + (blockBaseSize.width / 2) + (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 좌측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX - (blockBaseSize.width / 2) - (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void EnemyBase::BreakableBlockCollisionProcess(BreakableBlock* breakableBlock)
{
	if (breakableBlock != nullptr)
	{
		Transform* blockBaseTransform = breakableBlock->GetTransform();
		// 블럭의 위치
		Vector2D blockBasePos = blockBaseTransform->GetPosition();
		// 블럭의 사이즈
		D2D1_SIZE_F blockBaseSize = breakableBlock->GetSize();
		// Player의 사이즈
		D2D1_SIZE_F playerSize = dynamic_cast<AABBCollision*>(this->mCollision)->GetSize();

		// -- 어느 방향에서 플레이어와 충돌했는가 + 어떠한 조건의 충돌인지 검사한다.
		float vertTovertTangent = ((blockBaseSize.height / 2) + (playerSize.height * ENEMY_SCALE / 2)) / ((blockBaseSize.width / 2) + (playerSize.width * ENEMY_SCALE / 2));

		Vector2D centerTocenter = this->mTransform->GetPosition() - blockBasePos;

		float curTangent = centerTocenter.mY / centerTocenter.mX;

		Vector2D velo = this->GetVelocity();

		// 플레이어는 블럭의 윗면에 있다.
		// 여기서 더 고려해야할 것이 있다면, 플레이어가 상승 중에는 위치 고정 X ..!
		// 만약, 좌측 면에서 점프 시 .. 어중간하게 강할 때 문제가 될 수 있다.
		if ((centerTocenter.mY < -(TILE_HEIGHT / 2) - (ENEMY_SCALE * ENEMY_HEIGHT / 2) + ADJUST_Y) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 추락 중 또는 플랫폼 위에 있다.
			if (mDirVector.mY >= 0.f)
			{
				// 플레이어가 밟고 있는 밑면이 하나라도 있다는 것이므로 점프 가능하게 바꿔줍니다.
				mIsJumpable = true;

				velo.mY = 0.f;

				// 플레이어 캐릭터의 위치를 블럭의 상단으로 고정해준다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + 0.005 - (blockBaseSize.height / 2) - (playerSize.height * ENEMY_SCALE / 2)));
			}
		}
		// 플레이어는 블럭의 밑면에 있다.
		else if ((centerTocenter.mY >= 0) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 상승 중 플랫폼의 밑면에서 충돌하였다면.
			if (mDirVector.mY < 0.f)
			{
				velo.mY = 0.f;

				// 플레이어 캐릭터의 위치를 블럭의 하단으로 고정해준다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + (blockBaseSize.height / 2) + (playerSize.height * ENEMY_SCALE / 2)));
			}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX >= 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 우측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX + (blockBaseSize.width / 2) + (playerSize.width * ENEMY_SCALE / 2),
				mTransform->GetPosition().mY));
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 좌측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX - (blockBaseSize.width / 2) - (playerSize.width * ENEMY_SCALE / 2),
				mTransform->GetPosition().mY));
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void EnemyBase::TransBoxCollisionProcess(TransBox* transBox)
{
	if (transBox != nullptr)
	{
		Transform* blockBaseTransform = transBox->GetTransform();
		// 블럭의 위치
		Vector2D blockBasePos = blockBaseTransform->GetPosition();
		// 블럭의 사이즈
		D2D1_SIZE_F blockBaseSize = transBox->GetSize();
		// Player의 사이즈
		D2D1_SIZE_F playerSize = dynamic_cast<AABBCollision*>(this->mCollision)->GetSize();

		// -- 어느 방향에서 플레이어와 충돌했는가 + 어떠한 조건의 충돌인지 검사한다.
		float vertTovertTangent = ((blockBaseSize.height / 2) + (playerSize.height * ENEMY_SCALE / 2)) / ((blockBaseSize.width / 2) + (playerSize.width * ENEMY_SCALE / 2));

		Vector2D centerTocenter = this->mTransform->GetPosition() - blockBasePos;

		float curTangent = centerTocenter.mY / centerTocenter.mX;

		Vector2D velo = this->GetVelocity();

		// 플레이어는 블럭의 윗면에 있다.
		// 여기서 더 고려해야할 것이 있다면, 플레이어가 상승 중에는 위치 고정 X ..!
		if ((centerTocenter.mY < 0) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 해당 프레임이 Jump가 수행된 프레임이면 넘어간다.
			if (((mPrevState == EnemyState::Run) && (mCurrentState == EnemyState::Jump))
				|| ((mPrevState == EnemyState::Idle) && (mCurrentState == EnemyState::Jump)))
				return;
		}
		// 플레이어는 블럭의 밑면에 있다.
		else if ((centerTocenter.mY > 0) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 상승 중 플랫폼의 밑면에서 충돌하였다면.
			if (mDirVector.mY < 0.f)
			{
				transBox->TriggerOn();	// 트리거를 켜준다

				velo.mY = BLOCKING_POWER;

				// 플레이어 캐릭터의 위치를 블럭의 하단으로 고정해준다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + (blockBaseSize.height / 2) + (playerSize.height * ENEMY_SCALE / 2)));
			}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX > 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{

		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{

		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void EnemyBase::ItemBoxCollisionProcess(ItemBox* itemBox)
{
	if (itemBox != nullptr)
	{
		Transform* blockBaseTransform = itemBox->GetTransform();
		// 블럭의 위치
		Vector2D blockBasePos = blockBaseTransform->GetPosition();
		// 블럭의 사이즈
		D2D1_SIZE_F blockBaseSize = itemBox->GetSize();
		// Player의 사이즈
		D2D1_SIZE_F playerSize = dynamic_cast<AABBCollision*>(this->mCollision)->GetSize();

		// -- 어느 방향에서 플레이어와 충돌했는가 + 어떠한 조건의 충돌인지 검사한다.
		float vertTovertTangent = ((blockBaseSize.height / 2) + (playerSize.height * ENEMY_SCALE / 2)) / ((blockBaseSize.width / 2) + (playerSize.width * ENEMY_SCALE / 2));

		Vector2D centerTocenter = this->mTransform->GetPosition() - blockBasePos;

		float curTangent = centerTocenter.mY / centerTocenter.mX;

		Vector2D velo = this->GetVelocity();

		// 플레이어는 블럭의 윗면에 있다.
		// 여기서 더 고려해야할 것이 있다면, 플레이어가 상승 중에는 위치 고정 X ..!
		// 만약, 좌측 면에서 점프 시 .. 어중간하게 강할 때 문제가 될 수 있다.
		if ((centerTocenter.mY < -(TILE_HEIGHT / 2) - (ENEMY_HEIGHT * ENEMY_SCALE / 2) + ADJUST_Y) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 추락 중 또는 플랫폼 위에 있다.
			if (mDirVector.mY >= 0.f)
			{
				// 플레이어가 밟고 있는 밑면이 하나라도 있다는 것이므로 점프 가능하게 바꿔줍니다.
				mIsJumpable = true;

				velo.mY = 0.f;

				// 플레이어 캐릭터의 위치를 블럭의 상단으로 고정해준다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + 0.005 - (blockBaseSize.height / 2) - (playerSize.height * ENEMY_SCALE / 2)));
			}
		}
		// 플레이어는 블럭의 밑면에 있다.
		else if ((centerTocenter.mY >= 0) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 상승 중 플랫폼의 밑면에서 충돌하였다면.
			if (mDirVector.mY < 0.f)
			{
				velo.mY = BLOCKING_POWER;

				itemBox->TriggerOn();	// 트리거를 켜준다

				// 플레이어 캐릭터의 위치를 블럭의 하단으로 고정해준다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + (blockBaseSize.height / 2) + (playerSize.height * ENEMY_SCALE / 2)));
			}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX >= 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 우측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX + (blockBaseSize.width / 2) + (playerSize.width * ENEMY_SCALE / 2),
				mTransform->GetPosition().mY));
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 좌측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX - (blockBaseSize.width / 2) - (playerSize.width * ENEMY_SCALE / 2),
				mTransform->GetPosition().mY));
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void EnemyBase::PlatformCollisionProcess(Platform* platform)
{
	if (platform != nullptr)
	{
		Transform* blockBaseTransform = platform->GetTransform();
		// 블럭의 위치
		Vector2D blockBasePos = blockBaseTransform->GetPosition();
		// 블럭의 사이즈
		D2D1_SIZE_F blockBaseSize = platform->GetSize();
		// Player의 사이즈
		D2D1_SIZE_F playerSize = dynamic_cast<AABBCollision*>(this->mCollision)->GetSize();

		// -- 어느 방향에서 플레이어와 충돌했는가 + 어떠한 조건의 충돌인지 검사한다.
		float vertTovertTangent = ((blockBaseSize.height / 2) + (playerSize.height * ENEMY_SCALE / 2)) / ((blockBaseSize.width / 2) + (playerSize.width * ENEMY_SCALE / 2));

		Vector2D centerTocenter = this->mTransform->GetPosition() - blockBasePos;

		float curTangent = centerTocenter.mY / centerTocenter.mX;

		Vector2D velo = this->GetVelocity();

		// 플레이어는 플랫폼의 윗면에 있다.
		// 여기서 더 고려해야할 것이 있다면, 플레이어가 상승 중에는 위치 고정 X ..!
		// 여기서 맨 처음 수식이 의미하는 바는 플랫폼과 캐릭터가 의미있는 거리 이상 떨어져 있어야만 플랫폼 착지를 실시하도록 강제한 것입니다.
		if ((centerTocenter.mY < -(TILE_HEIGHT / 2) - (ENEMY_HEIGHT * ENEMY_SCALE / 2) + ADJUST_Y) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 해당 프레임이 Jump가 수행된 프레임이면 넘어간다.
			if (((mPrevState == EnemyState::Run) && (mCurrentState == EnemyState::Jump))
				|| ((mPrevState == EnemyState::Idle) && (mCurrentState == EnemyState::Jump)))
				return;

			if ((mDirVector.mY >= 0.f))
			{
				// 플레이어가 밟고 있는 밑면이 하나라도 있다는 것이므로 점프 가능하게 바꿔줍니다.
				mIsJumpable = true;

				velo.mY = 0.f;

				// 플레이어 캐릭터의 위치를 플랫폼의 상단으로 고정해준다. 무조건 상단의 비교값보다 더 작아지므로 착지가 유지됩니다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + 0.005f - (blockBaseSize.height / 2) - (playerSize.height * ENEMY_SCALE / 2)));

				platform->SetCollisionDir(CollisionDir::UP);
			}
		}
		// 플레이어는 블럭의 밑면에 있다.
		else if ((centerTocenter.mY > 0) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			platform->SetCollisionDir(CollisionDir::DOWN);
		}
		// 플레이어는 플랫폼의 오른쪽 면에 있다.
		else if ((centerTocenter.mX > 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			platform->SetCollisionDir(CollisionDir::RIGHT);
		}
		// 플레이어는 플랫폼의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			platform->SetCollisionDir(CollisionDir::LEFT);
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void EnemyBase::BlockPlatformCollisionProcess(BlockPlatform* blockplatform)
{
	if (blockplatform != nullptr)
	{
		Transform* blockBaseTransform = blockplatform->GetTransform();
		// 블럭의 위치
		Vector2D blockBasePos = blockBaseTransform->GetPosition();
		// 블럭의 사이즈
		D2D1_SIZE_F blockBaseSize = blockplatform->GetSize();
		// Player의 사이즈
		D2D1_SIZE_F playerSize = dynamic_cast<AABBCollision*>(this->mCollision)->GetSize();

		// -- 어느 방향에서 플레이어와 충돌했는가 + 어떠한 조건의 충돌인지 검사한다.
		float vertTovertTangent = ((blockBaseSize.height / 2) + (playerSize.height * ENEMY_SCALE / 2)) / ((blockBaseSize.width / 2) + (playerSize.width * ENEMY_SCALE / 2));

		Vector2D centerTocenter = this->mTransform->GetPosition() - blockBasePos;

		float curTangent = centerTocenter.mY / centerTocenter.mX;

		Vector2D velo = this->GetVelocity();

		// 플레이어는 블럭의 윗면에 있다.
		// 여기서 더 고려해야할 것이 있다면, 플레이어가 상승 중에는 위치 고정 X ..!
		// 만약, 좌측 면에서 점프 시 .. 어중간하게 강할 때 문제가 될 수 있다.
		if ((centerTocenter.mY < -(TILE_HEIGHT / 2) - (ENEMY_HEIGHT * ENEMY_SCALE / 2) + ADJUST_Y) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 추락 중 또는 플랫폼 위에 있다.
			if (mDirVector.mY >= 0.f)
			{
				// 플레이어가 밟고 있는 밑면이 하나라도 있다는 것이므로 점프 가능하게 바꿔줍니다.
				mIsJumpable = true;

				velo.mY = 0.f;

				// 플레이어 캐릭터의 위치를 블럭의 상단으로 고정해준다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + 0.005 - (blockBaseSize.height / 2) - (playerSize.height * ENEMY_SCALE / 2)));
			}
		}
		// 플레이어는 블럭의 밑면에 있다.
		else if ((centerTocenter.mY >= 0) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			//// 상승 중 플랫폼의 밑면에서 충돌하였다면.
			//if (mDirVector.mY < 0.f)
			//{
			//	velo.mY = 0.f;

			//	// 플레이어 캐릭터의 위치를 블럭의 하단으로 고정해준다.
			//	mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
			//		blockBasePos.mY + (blockBaseSize.height / 2) + (playerSize.height * PLAYER_SCALE / 2)));
			//}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX >= 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 우측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX + (blockBaseSize.width / 2) + (playerSize.width * ENEMY_SCALE / 2),
				mTransform->GetPosition().mY));
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 좌측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX - (blockBaseSize.width / 2) - (playerSize.width * ENEMY_SCALE / 2),
				mTransform->GetPosition().mY));
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void EnemyBase::BoxCollisionProcess(BoxBase* box)
{
	if (box != nullptr)
	{
		Transform* blockBaseTransform = box->GetTransform();
		// 블럭의 위치
		Vector2D blockBasePos = blockBaseTransform->GetPosition();
		// 블럭의 사이즈
		D2D1_SIZE_F blockBaseSize = box->GetSize();
		// Player의 사이즈
		D2D1_SIZE_F playerSize = dynamic_cast<AABBCollision*>(this->mCollision)->GetSize();

		// -- 어느 방향에서 플레이어와 충돌했는가 + 어떠한 조건의 충돌인지 검사한다.
		float vertTovertTangent = ((blockBaseSize.height / 2) + (playerSize.height * ENEMY_SCALE / 2)) / ((blockBaseSize.width / 2) + (playerSize.width * ENEMY_SCALE / 2));

		Vector2D centerTocenter = this->mTransform->GetPosition() - blockBasePos;

		float curTangent = centerTocenter.mY / centerTocenter.mX;

		Vector2D velo = this->GetVelocity();

		// 플레이어는 블럭의 윗면에 있다.
		// 여기서 더 고려해야할 것이 있다면, 플레이어가 상승 중에는 위치 고정 X ..!
		// 만약, 좌측 면에서 점프 시 .. 어중간하게 강할 때 문제가 될 수 있다.
		if ((centerTocenter.mY < -(TILE_HEIGHT / 2) - (ENEMY_HEIGHT * ENEMY_SCALE / 2) + ADJUST_Y) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 추락 중 또는 플랫폼 위에 있다.
			if (mDirVector.mY >= 0.f)
			{
				// 플레이어가 밟고 있는 밑면이 하나라도 있다는 것이므로 점프 가능하게 바꿔줍니다.
				mIsJumpable = true;

				velo.mY = 0.f;

				// 플레이어 캐릭터의 위치를 블럭의 상단으로 고정해준다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + 0.005 - (blockBaseSize.height / 2) - (playerSize.height * ENEMY_SCALE / 2)));
			}
		}
		// 플레이어는 블럭의 밑면에 있다.
		else if ((centerTocenter.mY >= 0) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 상승 중 플랫폼의 밑면에서 충돌하였다면.
			if (mDirVector.mY < 0.f)
			{
				velo.mY = BLOCKING_POWER;

				// 플레이어 캐릭터의 위치를 블럭의 하단으로 고정해준다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + (blockBaseSize.height / 2) + (playerSize.height * ENEMY_SCALE / 2)));
			}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX >= 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 우측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX + (blockBaseSize.width / 2) + (playerSize.width * ENEMY_SCALE / 2),
				mTransform->GetPosition().mY));
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 좌측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX - (blockBaseSize.width / 2) - (playerSize.width * ENEMY_SCALE / 2),
				mTransform->GetPosition().mY));
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}