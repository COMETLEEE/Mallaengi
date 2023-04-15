#pragma once
#include "EnemyBase.h"
#include "FreeEnemy.h"

/**
 * \brief : 떨어지는 덤벨. EnemyBase를 상속받지만 죽지 않는 .. 그런 것 ..?
 *
 * 2022. 02. 23. Comet
 */
class FallingDum : public FreeEnemy
{
public:
	FallingDum(std::string type, int isFalling = -1);
	virtual ~FallingDum();

public:

	virtual void FixedUpdate() override;
	virtual void Update() override;
};