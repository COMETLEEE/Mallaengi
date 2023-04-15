#include "PreCompiledHeader.h"
#include "OneWayMob.h"

OneWayMob::OneWayMob(std::string type, float moveSpeed, Vector2D Dir) :
	EnemyBase(),
	mMoveSpeed(moveSpeed),
	mGamePlayer(Game::GetInstance().GetPlayer()),
mType(type)
{
	mAnimationClips = std::vector<AnimationClip*>(3);

	LoadAnimationProcess();

	mDirrection = Dir;

	if (mType == "Hamburger")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_BURGER_IDLE"));
	else if (mType == "SandBag")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_SANDBAG_IDLE"));
	else if (mType == "Dum")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_DUM_IDLE"));
	else if (mType == "NiddleDown")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("TRAP_NIDDLE_DUM_DOWN"));
	else if (mType == "Down")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("TRAP_DUM_DOWN"));
	else if (mType == "Face")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FACE_IDLE"));
	else if (mType == "Fur")
		GetAnimator()->SetAnimationClip(Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FUR_IDLE"));
}

OneWayMob::~OneWayMob()
{

}

void OneWayMob::Idle()
{
	EnemyBase::Idle();

	Vector2D playerPos = mGamePlayer->GetTransform()->GetPosition();

	Vector2D myPos = mTransform->GetPosition();

	if (mDirrection.mX == -1)
	{
		if ((myPos.mX - playerPos.mX) <= SEARCH_DIST)
		{
			mCurrentState = EnemyState::Run;

			mTransform->SetScale(Vector2D(static_cast<float>(mDirrection.mX) * ENEMY_SCALE, ENEMY_SCALE));
		}
	}
	else if (mDirrection.mX == 1)
	{
		if ((playerPos.mX - myPos.mX) <= SEARCH_DIST)
		{
			mCurrentState = EnemyState::Run;

			mTransform->SetScale(Vector2D(static_cast<float>(mDirrection.mX) * ENEMY_SCALE, ENEMY_SCALE));
		}
	}
}

void OneWayMob::Run()
{
	EnemyBase::Run();

	mVelocity.mX = mDirrection.mX * mMoveSpeed;
}

void OneWayMob::Die()
{
	EnemyBase::Die();
	SoundManager::GetInstance()->Play(500028);
	// Time을 새면서 투명해지자 ..
	GetSpriteRenderer()->SetOpacity(GetSpriteRenderer()->GetOpacity() - 0.017f);

	if (GetSpriteRenderer()->GetOpacity() <= 0.f)
		Game::GetInstance().GetCurrentScene()->ReserveDestroy(this);
}

void OneWayMob::LoadAnimationProcess()
{
	// 각각의 타입에 맞는 Animation을 재생한다.
	if (mType == "Hamburger")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_BURGER_IDLE");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_BURGER_RUN");
		mAnimationClips[static_cast<int>(EnemyState::Die)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_BURGER_DIE");
	}
	else if (mType == "SandBag")
	{
		// 샌드백 ^^
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_SANDBAG_IDLE");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_SANDBAG_RUN");
		mAnimationClips[static_cast<int>(EnemyState::Die)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_SANDBAG_DIE");
	}
	else if (mType == "Dum")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_DUM_IDLE");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_DUM_RUN");
		mAnimationClips[static_cast<int>(EnemyState::Die)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_DUM_DIE");
	}
	else if (mType == "NiddleDown")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("TRAP_NIDDLE_DUM_DOWN");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("TRAP_NIDDLE_DUM_DOWN");
	}
	else if (mType == "Down")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("TRAP_DUM_DOWN");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("TRAP_DUM_DOWN");
	}
	else if (mType == "Face")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FACE_IDLE");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FACE_RUN");
		mAnimationClips[static_cast<int>(EnemyState::Die)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FACE_DIE");
	}
	else if (mType == "Fur")
	{
		mAnimationClips[static_cast<int>(EnemyState::Idle)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FUR_IDLE");
		mAnimationClips[static_cast<int>(EnemyState::Run)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FUR_RUN");
		mAnimationClips[static_cast<int>(EnemyState::Die)] = Game::GetInstance().GetResource()->GetAnimationClip("ENEMY_FUR_DIE");
	}
}