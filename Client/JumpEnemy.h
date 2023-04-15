#pragma once
#include "FreeEnemy.h"

/**
 * \brief : 점프하면서 왔다갔다 하게 해달래
 *
 * 2022. 02. 22. Comet
 */
class JumpEnemy : public FreeEnemy
{
public:
	JumpEnemy();
	virtual ~JumpEnemy();

public:
	virtual void Update() override;
};