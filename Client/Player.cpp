#include "PreCompiledHeader.h"

// Blocks
#include "BlockBase.h"
#include "BreakableBlock.h"

// Platforms
#include "Platform.h"
#include "BlockPlatform.h"

// Box
#include "TransBox.h"
#include "ItemBox.h"

// Player
#include "Player.h"

// Enemy
#include "EnemyBase.h"

// Effect
#include "FadeOutObject.h"
#include "FreeEnemy.h"
#include "RunEffect.h"
#include "LandingEffect.h"
#include "WeightNumber.h"

Player::Player() :
	mDirVector(Vector2D::Zero),
	mBeforePosition(Vector2D::Zero),
	mIsJumpable(false),
	mInvincible(false),
	mCurrentState(PlayerState::Idle),
	mPrevState(PlayerState::Idle),
	mCurrentStep(PlayerStep::Two),
	mPrevStep(PlayerStep::Two),
	mLife(100),							// 시작 목숨 수
	mIsFirstDieLoop(false),
	mHp(1),
	mBodyWeight(105.f),				// 시작 몸무게
	mPrevWeight(105.f),
	mVelocity(Vector2D::Zero),
	mGravity(GRAVITY),
	// MaxWalkSpeed와 JumpPower는 레벨 디자인에 맞는 수식으로 계산을 할 필요가 있습니다.
	// 아니면 단계별로 두기
	mJumpPower(JUMP_POWER* (static_cast<int>(mCurrentStep) + 1)),
	mMaxWalkSpeed(MOVE_SPEED* (static_cast<int>(mCurrentStep) + 1)),
	mJumpPressedTime(0.1f),
	mIsJumpKeyPressed(false),
	mAnimationClips(std::vector<std::vector<AnimationClip*>>(PLAYER_TOTAL_STEP + 1, std::vector<AnimationClip*>(PLAYER_TOTAL_STATE))),
	mRunEffect(nullptr),
	mLandingEffect(nullptr),
	mAcculmulTime(0.f)
{
	// 생성될 때 이 오브젝트의 필요한 컴포넌트의 준비를 모두 해주어야 합니다.
	AddSpriteRenderer()->SetSortOrder(4);

	// 이거는 다음에 Sprite Tool의 피격 범위로 만들 예정입니다.
	AddAABBCollision()->SetSize({ PLAYER_WIDTH, PLAYER_HEIGHT });

	Animator* animator = AddAnimator();

	LoadAnimationProcess();

	animator->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_TWO_IDLE"));

	GetTransform()->SetPosition(GetTransform()->GetPosition() + Vector2D(100.f, 100.f));

	GetTransform()->SetScale(Vector2D(PLAYER_SCALE, PLAYER_SCALE));

	// 제일 중요한 태그 설정
	SetTag("Player");
}

Player::~Player()
{
}

void Player::Idle()
{
	if (Input::GetInstance().GetKeyState(VK_LEFT) == KEYSTATE::HOLD)
	{
		mVelocity.mX = -mMaxWalkSpeed;

		mTransform->SetScale(Vector2D(-PLAYER_SCALE, PLAYER_SCALE));

		mCurrentState = PlayerState::Run;
	}
	else if (Input::GetInstance().GetKeyState(VK_RIGHT) == KEYSTATE::HOLD)
	{
		mVelocity.mX = mMaxWalkSpeed;

		mTransform->SetScale(Vector2D(PLAYER_SCALE, PLAYER_SCALE));

		mCurrentState = PlayerState::Run;
	}
	else if ((mIsJumpable) && (Input::GetInstance().GetKeyState(VK_SPACE) == KEYSTATE::DOWN))
	{
		mIsJumpKeyPressed = true;

		mIsJumpKeyPressed = true;

		mVelocity.mY = -mJumpPower * (1 + mJumpPressedTime * 2);

		mJumpPressedTime = 0.1f;

		mCurrentState = PlayerState::Jump;

		mIsJumpKeyPressed = false;

		SoundManager::GetInstance()->Play(500012);

		mIsJumpable = false;
	}

	return;
}

void Player::Run()
{
	if ((Input::GetInstance().GetKeyState(VK_LEFT) == KEYSTATE::UP) ||
		(Input::GetInstance().GetKeyState(VK_LEFT) == KEYSTATE::NONE) ||
		(Input::GetInstance().GetKeyState(VK_RIGHT) == KEYSTATE::UP) ||
		(Input::GetInstance().GetKeyState(VK_RIGHT) == KEYSTATE::NONE))
	{
		mCurrentState = PlayerState::Idle;
	}

	// 입력에 따른 속도 변경 (Walk State / FSM으로 들어갈 예정입니다.)
	if (Input::GetInstance().GetKeyState(VK_LEFT) == KEYSTATE::HOLD)
	{
		mVelocity.mX = -mMaxWalkSpeed;

		mTransform->SetScale(Vector2D(-PLAYER_SCALE, PLAYER_SCALE));

		mCurrentState = PlayerState::Run;
		if (SoundManager::GetInstance()->Playing(500011) != true)
		{
			SoundManager::GetInstance()->Play(500011);
		}

		// 플레이어 이동시에 출력되는 이펙트
		if (mRunEffect == nullptr)
		{
			mRunEffect = new RunEffect(this, Vector2D::Left);
			Game::GetInstance().GetCurrentScene()->AddGameObject(mRunEffect);
		}
		else
		{
			mRunEffect->SetDirection(Vector2D::Left);
		}
	}
	else if (Input::GetInstance().GetKeyState(VK_RIGHT) == KEYSTATE::HOLD)
	{
		mVelocity.mX = mMaxWalkSpeed;

		mTransform->SetScale(Vector2D(PLAYER_SCALE, PLAYER_SCALE));

		mCurrentState = PlayerState::Run;
		if (SoundManager::GetInstance()->Playing(500011) != true)
		{
			SoundManager::GetInstance()->Play(500011);
		}

		// 플레이어 이동시에 출력되는 이펙트
		if (mRunEffect == nullptr)
		{
			mRunEffect = new RunEffect(this, Vector2D::Right);
			Game::GetInstance().GetCurrentScene()->AddGameObject(mRunEffect);
		}
		else
		{
			mRunEffect->SetDirection(Vector2D::Right);
		}
	}

	if ((mIsJumpable) && (Input::GetInstance().GetKeyState(VK_SPACE) == KEYSTATE::DOWN))
	{
		mVelocity.mY = -mJumpPower * (1 + mJumpPressedTime * 2);

		mJumpPressedTime = 0.1f;

		SoundManager::GetInstance()->Play(500012);

		mCurrentState = PlayerState::Jump;

		mIsJumpable = false;
	}

	return;
}

void Player::Jump()
{
	// 입력에 따른 속도 변경, 점프 상태에서도 움직임이 가능하다 ..?
	if (Input::GetInstance().GetKeyState(VK_LEFT) == KEYSTATE::HOLD)
	{
		mVelocity.mX = -mMaxWalkSpeed;

		mTransform->SetScale(Vector2D(-PLAYER_SCALE, PLAYER_SCALE));

	}
	else if (Input::GetInstance().GetKeyState(VK_RIGHT) == KEYSTATE::HOLD)
	{

		mVelocity.mX = mMaxWalkSpeed;

		mTransform->SetScale(Vector2D(PLAYER_SCALE, PLAYER_SCALE));
	}

	// 다시 점프가 가능해졌다는 것은 하단의 플랫폼을 밟았다는 것, 따라서 Idle로 Transition합니다.
	if (mIsJumpable)
	{
		if (mLandingEffect == nullptr)
		{
			mLandingEffect = new LandingEffect(this);
			Game::GetInstance().GetCurrentScene()->AddGameObject(mLandingEffect);
		}

		mCurrentState = PlayerState::Idle;
	}

	return;
}

void Player::Die()
{
	//Die sound

	// 플레이어가 죽게 되었을 때의 Process를 여기서 진행하게 됩니다.

	// 목숨을 하나 줄이고, 다시 시작하던지 ..? 그런 느낌으로 진행하게 될 것 같습니다.

	// 죽으면 페이드 아웃 진행

	// 1. 죽으면 움직이지 않기
	mVelocity = Vector2D(0.f, 0.f);

	if (!mIsFirstDieLoop)
	{
		mIsFirstDieLoop = true;
		SoundManager::GetInstance()->Play(500017);

		mLife -= 1;

		// TODO : 현재 플레이 중인 스테이지를 기억해야한다. 그리고 로드할 때 세이브된 위치, 몸무게로 다시 시작할 수 있도록 작성 필요
		std::string name = Game::GetInstance().GetCurrentScene()->GetSceneName();

		FadeOutObject* fadeOut = new FadeOutObject(name + "DieScene");

		Game::GetInstance().GetCurrentScene()->AddGameObject(fadeOut);
	}

	static float timer = 0;

	timer += Timer::GetInstance().GetDeltaTime() / 1000.f;

	if (timer >= FADE_TIME)
	{
		timer = 0;

		mIsFirstDieLoop = false;

		mCurrentState = PlayerState::Idle;
	}

	return;
}

void Player::Trans()
{
	static float timer = 0;

	timer += Timer::GetInstance().GetDeltaTime() / 1000.f;

	if (timer >= TRANS_TIME)
	{
		mCurrentState = PlayerState::Idle;

		timer = 0;

		// 트랜스가 끝나면 !
		GetAnimator()->SetAnimationClip(mAnimationClips[static_cast<int>(mCurrentStep)][static_cast<int>(mCurrentState)]);

		//몸무게 증가,감소 변화 할 때 나는 효과음


		/*mMaxWalkSpeed = MOVE_SPEED * (static_cast<int>(mCurrentStep) + 1);
		mJumpPower = JUMP_POWER * (static_cast<int>(mCurrentStep) + 1);*/
	}
}

void Player::LoadAnimationProcess()
{
	// 플레이어 단계 변경에 따른 내부 로직을 깔끔하게 쓰기 위해서 플레이어가 자기 자신의 행동 애니메이션을
	// 갖고 있도록 하겠습니다.
	mAnimationClips[0][0] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_THREE_IDLE");
	mAnimationClips[0][1] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_THREE_RUN");
	mAnimationClips[0][2] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_THREE_JUMP");
	mAnimationClips[0][3] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_THREE_DIE");

	mAnimationClips[1][0] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_TWO_IDLE");
	mAnimationClips[1][1] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_TWO_RUN");
	mAnimationClips[1][2] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_TWO_JUMP");
	mAnimationClips[1][3] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_TWO_DIE");

	mAnimationClips[2][0] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_ONE_IDLE");
	mAnimationClips[2][1] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_ONE_RUN");
	mAnimationClips[2][2] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_ONE_JUMP");
	mAnimationClips[2][3] = Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_ONE_DIE");

	// Trans !!
	mAnimationClips[3][0] = Game::GetInstance().GetResource()->GetAnimationClip("THREE_TO_TWO");
	mAnimationClips[3][1] = Game::GetInstance().GetResource()->GetAnimationClip("TWO_TO_THREE");
	mAnimationClips[3][2] = Game::GetInstance().GetResource()->GetAnimationClip("TWO_TO_ONE");
	mAnimationClips[3][3] = Game::GetInstance().GetResource()->GetAnimationClip("ONE_TO_TWO");
}

void Player::StateChangeProcess()
{
	// 만약, 상태가 변경되었다면 PlayerStep, CurrentState에 해당하는 Animation으로 교체합니다.

	if (mCurrentState == PlayerState::Trans)
		return;

	if (mPrevState != mCurrentState)
		GetAnimator()->SetAnimationClip(mAnimationClips[static_cast<int>(mCurrentStep)][static_cast<int>(mCurrentState)]);
}

void Player::StepChangeProcess()
{
	if ((mCurrentState == PlayerState::Die) || (mCurrentState == PlayerState::Jump) || (!mIsJumpable))
		return;

	if (mBodyWeight < 100.f)
		mCurrentStep = PlayerStep::One;
	else if ((100.f <= mBodyWeight) && (mBodyWeight < 120.f))
		mCurrentStep = PlayerStep::Two;
	else if ((120.f <= mBodyWeight) && (mBodyWeight < 140.f))
		mCurrentStep = PlayerStep::Three;
	else if ((140.f <= mBodyWeight))			// 140kg 넘어가면 기획 의도에 맞게 죽음 이벤트를 실시하면 된다.
	{
		// Die 일단 막아 놓겠습니다.
		mCurrentState = PlayerState::Die;

		mHp = 0;
	}

	if (mPrevStep != mCurrentStep)
	{
		mCurrentState = PlayerState::Trans;

		// 우측만 볼 수 있다.
		mTransform->SetScale(Vector2D(PLAYER_SCALE, PLAYER_SCALE));

		if ((mPrevStep == PlayerStep::Three) && (mCurrentStep == PlayerStep::Two))
		{
			SoundManager::GetInstance()->Play(500020);
			GetAnimator()->SetAnimationClip(mAnimationClips[3][0]);
		}
		else if ((mPrevStep == PlayerStep::Two) && (mCurrentStep == PlayerStep::Three))
		{
			SoundManager::GetInstance()->Play(500019);
			GetAnimator()->SetAnimationClip(mAnimationClips[3][1]);
		}
		else if ((mPrevStep == PlayerStep::Two) && (mCurrentStep == PlayerStep::One))
		{
			SoundManager::GetInstance()->Play(500020);
			GetAnimator()->SetAnimationClip(mAnimationClips[3][2]);
		}
		else
		{
			SoundManager::GetInstance()->Play(500019);
			GetAnimator()->SetAnimationClip(mAnimationClips[3][3]);
		}
	}
}

void Player::InitPlayer()
{
	mDirVector = Vector2D::Zero;
	mBeforePosition = Vector2D::Zero;
	mIsJumpable = false;
	mInvincible = false;
	mCurrentState = PlayerState::Idle;
	mPrevState = PlayerState::Idle;
	mCurrentStep = PlayerStep::Two;
	mPrevStep = PlayerStep::Two;
	mLife = 100;							// 시작 목숨 수
	mIsFirstDieLoop = false;
	mHp = 1;
	mBodyWeight = 105.f;				// 시작 몸무게
	mPrevWeight = mBodyWeight;
	mVelocity = Vector2D::Zero;

	// MaxWalkSpeed와 JumpPower는 레벨 디자인에 맞는 수식으로 계산을 할 필요가 있습니다.
	// 아니면 단계별로 두기
	mJumpPower = JUMP_POWER * (static_cast<int>(mCurrentStep) + 1);
	mMaxWalkSpeed = MOVE_SPEED * (static_cast<int>(mCurrentStep) + 1);
	mJumpPressedTime = 0.1f;
	mIsJumpKeyPressed = false;

	mRunEffect = nullptr;
	mLandingEffect = nullptr;

	// 이거는 다음에 Sprite Tool의 피격 범위로 만들 예정입니다.
	AddAABBCollision()->SetSize({ PLAYER_WIDTH, PLAYER_HEIGHT });

	Animator* animator = GetAnimator();

	animator->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("PLAYER_TWO_IDLE"));

	GetTransform()->SetPosition(GetTransform()->GetPosition() + Vector2D(100.f, 100.f));

	GetTransform()->SetScale(Vector2D(PLAYER_SCALE, PLAYER_SCALE));
}

void Player::FixedUpdate()
{
	GameObject::FixedUpdate();

	//단계별 이동속도 점프력 컨트롤
	if (mCurrentStep == PlayerStep::One)
	{
		mMaxWalkSpeed = MOVE_SPEED + 150.f;
		mJumpPower = JUMP_POWER + 150.f;
	}
	else if (mCurrentStep == PlayerStep::Two)
	{
		mMaxWalkSpeed = MOVE_SPEED + 100.f;
		mJumpPower = JUMP_POWER + 100.f;
	}
	else if (mCurrentStep == PlayerStep::Three)
	{
		mMaxWalkSpeed = MOVE_SPEED;
		mJumpPower = JUMP_POWER;
	}

	//// 속도 컨트롤러
	//mMaxWalkSpeed = MOVE_SPEED * (static_cast<int>(mCurrentStep) + 1);
	//mJumpPower = JUMP_POWER * (static_cast<int>(mCurrentStep) + 1);

	// 0. 업데이트 전 현재 위치를 기억해둡니다.
	mBeforePosition = mTransform->GetPosition();

	// 1-1. 중력 처리 (최대 떨어지는 속도를 컨트롤합니다.)
	if (mVelocity.mY <= MAX_FALLING_SPEED)
	{
		mVelocity.mY = mVelocity.mY + mGravity * Timer::GetInstance().GetDeltaTime() / 1000.f;
	}

	// ---------------------------- Player FSM ----------------------------
	// 1. Update 전, PrevState와 PrevStep의 교체를 실시합니다.
	mPrevState = mCurrentState;
	mPrevStep = mCurrentStep;

	// Player State에 따른 분류
	switch (mCurrentState)
	{
	case PlayerState::Idle:
	{
		Idle();
		break;
	}

	case PlayerState::Run:
	{
		Run();
		break;
	}

	case PlayerState::Jump:
	{
		Jump();
		break;
	}

	case PlayerState::Die:
	{
		Die();
		break;
	}

	case PlayerState::Trans:
	{
		Trans();
		break;
	}

	default:
	{
		break;
	}
	}

	// 매 프레임마다 꺼준다. Update에서 바닥이 있다고 평가가 되었을 때만 점프할 수 있기를 바라기 때문이다.
	mIsJumpable = false;

	// 1. 현재 속도에 따른 이동 처리
	mTransform->SetPosition(mTransform->GetPosition() + (Timer::GetInstance().GetDeltaTime() / 1000.f) * mVelocity);

	mVelocity.mX = 0.f;
}

void Player::Update()
{
	

	GameObject::Update();

	// 시간 시스템 업데이트
	TimeProcess();

	// 테스트 코드
#ifdef _DEBUG || DEBUG
	if (Input::GetInstance().GetKeyState(VK_F1) == KEYSTATE::DOWN)
		mBodyWeight += 1.0f;
	else if (Input::GetInstance().GetKeyState(VK_F2) == KEYSTATE::DOWN)
		mBodyWeight -= 1.0f;
	else if (Input::GetInstance().GetKeyState(VK_F3) == KEYSTATE::DOWN)
		mInvincible = !mInvincible;
#endif

	// Hp 변수가 0 이하이면, Die Process로 진입한다.
	if (mHp <= 0)
		mCurrentState = PlayerState::Die;

	if (abs(mPrevWeight - mBodyWeight) >= 1.0f)
	{
		int sign = 1;

		if (mPrevWeight <= mBodyWeight)
			sign = 1;
		else
			sign = -1;

		while (abs(mPrevWeight - mBodyWeight) >= 1.0f)
		{
			if (abs(mPrevWeight - mBodyWeight) >= 10.0f)
			{
				Game::GetInstance().GetCurrentScene()->AddGameObject(new WeightNumber(GetTransform()->GetPosition(), sign * 10));

				mPrevWeight += sign * 10.0f;
			}
			else if (abs(mPrevWeight - mBodyWeight) >= 5.0f)
			{
				Game::GetInstance().GetCurrentScene()->AddGameObject(new WeightNumber(GetTransform()->GetPosition(), sign * 5));

				mPrevWeight += sign * 5.0f;
			}
			else if (abs(mPrevWeight - mBodyWeight) >= 3.0f)
			{
				Game::GetInstance().GetCurrentScene()->AddGameObject(new WeightNumber(GetTransform()->GetPosition(), sign * 3));

				mPrevWeight += sign * 3.0f;
			}
			else
			{
				Game::GetInstance().GetCurrentScene()->AddGameObject(new WeightNumber(GetTransform()->GetPosition(), sign * 1));

				mPrevWeight += sign * 1.0f;
			}
		}
	}

	// 각 씬 별로 특수한 프로세스들을 진행합니다.
	IntroSceneProcess();

	StageProcess();

	// 이동 방향 벡터를 최신화합니다. 이 벡터를 통해서 캐릭터가 어떤 움직임에서 충돌하는지 파악합니다.
	// 이동이 없으면 mDirVector == Vector2D::Zero / 조금이라고 있으면 방향을 갖습니다.
	GetTransform()->GetPosition() == mBeforePosition ? mDirVector = Vector2D::Zero
		: mDirVector = (GetTransform()->GetPosition() - mBeforePosition).Normalize();

	// 1. 이번 프레임에서의 충돌을 확인함
	// 플랫포머 관련 로직을 수행한다. 각 오브젝트 별로 조건이 다름 ..!
	std::vector<GameObject*> collisionInfo = mCollision->GetCollisionInfo();

	for (GameObject* object : collisionInfo)
	{
		// Block
		if (object->GetTag() == "BlockBase")
		{
			BlockBase* block = dynamic_cast<BlockBase*>(object);

			BlockCollisionProcess(block);
		}
		// 머가리로 찍으면 깨지는 블락
		else if (object->GetTag() == "BreakableBlock")
		{
			BreakableBlock* breakableBlock = dynamic_cast<BreakableBlock*>(object);

			BreakableBlockCollisionProcess(breakableBlock);
		}
		// Platform
		else if (object->GetTag() == "Platform")
		{
			Platform* platform = dynamic_cast<Platform*>(object);

			PlatformCollisionProcess(platform);
		}
		// BlockPlatform
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

		// Enemy
		else if (object->GetTag() == "Enemy")
		{
			EnemyBase* enemy = dynamic_cast<EnemyBase*>(object);

			EnemyCollsionProcess(enemy);
		}
	}

	// 몸무게 체크 중, 사망 모션이 나올 수 있으므로 먼저 체크합니다.
	StepChangeProcess();

	StateChangeProcess();
}

void Player::BlockCollisionProcess(BlockBase* block)
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

				block->SetCollisionDir(CollisionDir::UP);
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

				block->SetCollisionDir(CollisionDir::DOWN);
			}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX >= 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 우측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX + (blockBaseSize.width / 2) + (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));

			block->SetCollisionDir(CollisionDir::RIGHT);
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 좌측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX - (blockBaseSize.width / 2) - (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));

			block->SetCollisionDir(CollisionDir::LEFT);
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void Player::BreakableBlockCollisionProcess(BreakableBlock* breakableBlock)
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

				breakableBlock->SetCollisionDir(CollisionDir::UP);
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

				breakableBlock->BreakBlock();

				breakableBlock->SetCollisionDir(CollisionDir::DOWN);
			}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX >= 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 우측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX + (blockBaseSize.width / 2) + (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));

			breakableBlock->SetCollisionDir(CollisionDir::RIGHT);
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 좌측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX - (blockBaseSize.width / 2) - (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));

			breakableBlock->SetCollisionDir(CollisionDir::LEFT);
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void Player::PlatformCollisionProcess(Platform* platform)
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
		float vertTovertTangent = ((blockBaseSize.height / 2) + (playerSize.height * PLAYER_SCALE / 2)) / ((blockBaseSize.width / 2) + (playerSize.width * PLAYER_SCALE / 2));

		Vector2D centerTocenter = this->mTransform->GetPosition() - blockBasePos;

		float curTangent = centerTocenter.mY / centerTocenter.mX;

		Vector2D velo = this->GetVelocity();

		// 플레이어는 플랫폼의 윗면에 있다.
		// 여기서 더 고려해야할 것이 있다면, 플레이어가 상승 중에는 위치 고정 X ..!
		// 여기서 맨 처음 수식이 의미하는 바는 플랫폼과 캐릭터가 의미있는 거리 이상 떨어져 있어야만 플랫폼 착지를 실시하도록 강제한 것입니다.
		if ((centerTocenter.mY < -(TILE_HEIGHT / 2) - (PLAYER_HEIGHT * PLAYER_SCALE / 2) + ADJUST_Y) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 해당 프레임이 Jump가 수행된 프레임이면 넘어간다.
			if (((mPrevState == PlayerState::Run) && (mCurrentState == PlayerState::Jump))
				|| ((mPrevState == PlayerState::Idle) && (mCurrentState == PlayerState::Jump)))
				return;

			if ((mDirVector.mY >= 0.f))
			{
				// 플레이어가 밟고 있는 밑면이 하나라도 있다는 것이므로 점프 가능하게 바꿔줍니다.
				mIsJumpable = true;

				velo.mY = 0.f;

				// 플레이어 캐릭터의 위치를 플랫폼의 상단으로 고정해준다. 무조건 상단의 비교값보다 더 작아지므로 착지가 유지됩니다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + 0.005f - (blockBaseSize.height / 2) - (playerSize.height * PLAYER_SCALE / 2)));

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
void Player::BlockPlatformCollisionProcess(BlockPlatform* blockplatform)
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

				blockplatform->SetCollisionDir(CollisionDir::UP);
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
			blockplatform->SetCollisionDir(CollisionDir::DOWN);

		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX >= 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 우측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX + (blockBaseSize.width / 2) + (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));

			blockplatform->SetCollisionDir(CollisionDir::RIGHT);
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 좌측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX - (blockBaseSize.width / 2) - (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));

			blockplatform->SetCollisionDir(CollisionDir::LEFT);
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void Player::BoxCollisionProcess(BoxBase* box)
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

				box->SetCollisionDir(CollisionDir::UP);
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
					blockBasePos.mY + (blockBaseSize.height / 2) + (playerSize.height * PLAYER_SCALE / 2)));

				box->SetCollisionDir(CollisionDir::DOWN);
			}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX >= 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 우측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX + (blockBaseSize.width / 2) + (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));

			box->SetCollisionDir(CollisionDir::RIGHT);
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 좌측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX - (blockBaseSize.width / 2) - (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));

			box->SetCollisionDir(CollisionDir::LEFT);
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void Player::TransBoxCollisionProcess(TransBox* transBox)
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
		float vertTovertTangent = ((blockBaseSize.height / 2) + (playerSize.height * PLAYER_SCALE / 2)) / ((blockBaseSize.width / 2) + (playerSize.width * PLAYER_SCALE / 2));

		Vector2D centerTocenter = this->mTransform->GetPosition() - blockBasePos;

		float curTangent = centerTocenter.mY / centerTocenter.mX;

		Vector2D velo = this->GetVelocity();

		// 플레이어는 블럭의 윗면에 있다.
		// 여기서 더 고려해야할 것이 있다면, 플레이어가 상승 중에는 위치 고정 X ..!
		if ((centerTocenter.mY < 0) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			// 해당 프레임이 Jump가 수행된 프레임이면 넘어간다.
			if (((mPrevState == PlayerState::Run) && (mCurrentState == PlayerState::Jump))
				|| ((mPrevState == PlayerState::Idle) && (mCurrentState == PlayerState::Jump)))
				return;

			transBox->SetCollisionDir(CollisionDir::UP);
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
					blockBasePos.mY + (blockBaseSize.height / 2) + (playerSize.height * PLAYER_SCALE / 2)));

				transBox->SetCollisionDir(CollisionDir::DOWN);
			}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX > 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			transBox->SetCollisionDir(CollisionDir::RIGHT);
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			transBox->SetCollisionDir(CollisionDir::LEFT);
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void Player::ItemBoxCollisionProcess(ItemBox* itemBox)
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

				itemBox->SetCollisionDir(CollisionDir::UP);
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
					blockBasePos.mY + (blockBaseSize.height / 2) + (playerSize.height * PLAYER_SCALE / 2)));

				itemBox->SetCollisionDir(CollisionDir::DOWN);
			}
		}
		// 플레이어는 블럭의 오른쪽 면에 있다.
		else if ((centerTocenter.mX >= 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 우측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX + (blockBaseSize.width / 2) + (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));

			itemBox->SetCollisionDir(CollisionDir::RIGHT);
		}
		// 플레이어는 블럭의 좌측 면에 있다.
		else if ((centerTocenter.mX < 0) && ((curTangent < vertTovertTangent) || (curTangent > -vertTovertTangent)))
		{
			// velo.mX = 0.f;

			// 플레이어 캐릭터의 위치를 블럭의 좌측으로 고정해준다.
			mTransform->SetPosition(Vector2D(blockBasePos.mX - (blockBaseSize.width / 2) - (playerSize.width * PLAYER_SCALE / 2),
				mTransform->GetPosition().mY));

			itemBox->SetCollisionDir(CollisionDir::LEFT);
		}

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

void Player::EnemyCollsionProcess(EnemyBase* enemy)
{
	if (enemy != nullptr)
	{
		if (enemy->GetCurrentState() == EnemyState::Die)
			return;

		FreeEnemy* freeEnemy = dynamic_cast<FreeEnemy*>(enemy);

		if ((freeEnemy != nullptr) && ((freeEnemy->GetType() == "Down") || (freeEnemy->GetType() == "NiddleDown")))
			return;

		Transform* blockBaseTransform = enemy->GetTransform();

		// 적의 위치
		Vector2D blockBasePos = blockBaseTransform->GetPosition();

		// 적의 사이즈
		D2D1_SIZE_F blockBaseSize = dynamic_cast<AABBCollision*>(enemy->GetCollision())->GetSize();
		// Player의 사이즈
		D2D1_SIZE_F playerSize = dynamic_cast<AABBCollision*>(this->mCollision)->GetSize();

		// -- 어느 방향에서 플레이어와 충돌했는가 + 어떠한 조건의 충돌인지 검사한다.
		float vertTovertTangent = ((blockBaseSize.height / 2) + (playerSize.height * PLAYER_SCALE / 2)) / ((blockBaseSize.width / 2) + (playerSize.width * PLAYER_SCALE / 2));

		Vector2D centerTocenter = this->mTransform->GetPosition() - blockBasePos;

		float curTangent = centerTocenter.mY / centerTocenter.mX;

		Vector2D velo = this->GetVelocity();

		// 플레이어는 플랫폼의 윗면에 있다.
		// 여기서 더 고려해야할 것이 있다면, 플레이어가 상승 중에는 위치 고정 X ..!
		// 여기서 맨 처음 수식이 의미하는 바는 플랫폼과 캐릭터가 의미있는 거리 이상 떨어져 있어야만 플랫폼 착지를 실시하도록 강제한 것입니다.
		if ((centerTocenter.mY < -(blockBaseSize.height / 2) - (PLAYER_HEIGHT * PLAYER_SCALE / 2) + ADJUST_Y) && ((curTangent >= vertTovertTangent) || (curTangent <= -vertTovertTangent)))
		{
			if ((mDirVector.mY >= 0.f))
			{
				// 적 밟으면 공중으로 살짝 Up ?
				velo.mY = -1000.f;

				// 플레이어 캐릭터의 위치를 플랫폼의 상단으로 고정해준다. 무조건 상단의 비교값보다 더 작아지므로 착지가 유지됩니다.
				mTransform->SetPosition(Vector2D(mTransform->GetPosition().mX,
					blockBasePos.mY + 0.005f - (blockBaseSize.height / 2) - (playerSize.height * PLAYER_SCALE / 2)));

				enemy->SetHp(0);
			}
		}
		else
			SetHp(0);

		// 변환된 속도를 지정해준다.
		this->SetVelocity(velo);
	}
}

// 인트로 씬에서는 이동을 잠금해야함. 따라서 이 프로세스로 막는다.
void Player::IntroSceneProcess()
{
	if (Game::GetInstance().GetCurrentScene()->GetSceneName() != "Intro")
		return;

	Vector2D playerPos = mTransform->GetPosition();

	D2D1_SIZE_F size = Graphics::GetInstance().GetScreenSize();

	if (playerPos.mX < 0.0f)
		mTransform->SetPosition(Vector2D(0.0f, playerPos.mY));
	else if (playerPos.mX > 1920.0f / CAMERA_ZOOM)
		mTransform->SetPosition(Vector2D(1920.0f / CAMERA_ZOOM, playerPos.mY));
}

void Player::StageProcess()
{
	// 1. 각 스테이지별 낙사 조건
	if (mTransform->GetPosition().mY >= 3000.f)
		SetHp(0);
}

void Player::TimeProcess()
{
	std::string sceneName = Game::GetInstance().GetCurrentScene()->GetSceneName();

	if ((sceneName == "Intro") || (sceneName == "StageThreeOne") || (sceneName == "StageThreeTwo") || (sceneName == "StageThreeThree") ||
		(sceneName == "StageThreeFour") || (sceneName == "StageThreeFive"))
		return;

	if (mCurrentState == PlayerState::Trans)
		return;

	float delta = Timer::GetInstance().GetDeltaTime() / 1000.f;

	mStagePlayTime += delta;

	mAcculmulTime += delta;

	if (mAcculmulTime >= 10.f)
	{
		PlusBodyWeight(GAIN_PER_SEC);

		mAcculmulTime = 0.f;
	}
}