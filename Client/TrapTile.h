#pragma once

#include "BlockBase.h"

/// <summary>
/// 
/// </summary>
class TrapTile : public BlockBase
{
public :
	TrapTile();
	virtual ~TrapTile();

private:

	bool mTrigger;

public:
	virtual void Update() override;
};